/*
$fileHeader$
*/

#include <iostream>


#include <dicomhero6/dicomhero.h>
#include <sstream>

#if defined(WIN32) || defined(WIN64)
#include <process.h>
#else
#include <spawn.h>
#include <sys/wait.h>
#endif

#include <memory>
#include <list>

using namespace dicomhero;

int findArgument(const char* argument, int argc, char* argv[])
{
    for(int scanArg(0); scanArg != argc; ++scanArg)
    {
        if(std::string(argv[scanArg]) == argument)
        {
            return scanArg;
        }
    }
    return -1;
}


void outputDatasetTags(const DataSet& dataset, const std::wstring& prefix)
{
    tagsIds_t tags = dataset.getTags();

    // Output all the tags
    for(tagsIds_t::const_iterator scanTags(tags.begin()), endTags(tags.end());
        scanTags != endTags;
        ++scanTags)
    {
        try
        {
            std::wstring tagName = DicomDictionary::getUnicodeTagDescription(*scanTags);
            std::wcout << prefix << L"Tag " << (*scanTags).getGroupId() << L"," << (*scanTags).getTagId() << L" (" << tagName << L")" << std::endl;
        }
        catch(const DictionaryUnknownTagError&)
        {
            std::wcout << prefix << L"Tag " << (*scanTags).getGroupId() << L"," << (*scanTags).getTagId() << L" (Unknown tag)" << std::endl;
        }

        Tag tag(dataset.getTag(*scanTags));

        for(size_t itemId(0); ; ++itemId)
        {
            try
            {
                DataSet sequence = tag.getSequenceItem(itemId);
                std::wcout << prefix << L"  SEQUENCE " << itemId << std::endl;
                outputDatasetTags(sequence, prefix + L"    ");
            }
            catch(const MissingDataElementError&)
            {
                break;
            }
        }

        for(size_t bufferId(0); bufferId != tag.getBuffersCount(); ++bufferId)
        {
            ReadingDataHandler handler = tag.getReadingDataHandler(bufferId);
            if(handler.getDataType() != tagVR_t::OW && handler.getDataType() != tagVR_t::OB)
            {
                for(size_t scanHandler(0); scanHandler != handler.getSize(); ++scanHandler)
                {
                    std::wcout << prefix << L"  buffer " << bufferId << L", position "<< scanHandler << ":" << handler.getUnicodeString(scanHandler) << std::endl;
                }
            }
            else
            {
                std::wcout << prefix << L"  Not shown: size " << handler.getSize() << " elements" << std::endl;
            }

        }
    }
}


int main(int argc, char* argv[])
{
    std::wstring version(dicomhero::Version::getVersionW());
    std::wcout << L"dicom2jpeg version " << version << std::endl;

    CodecFactory::setMaximumImageSize(8000, 8000);

    try
    {

        if(argc < 2)
        {
            std::wcout << L"Usage: dicom2jpeg dicomFileName jpegFileName [-ffmpeg FFMPEGPATH FFMPEGOPT]" << std::endl;
            std::wcout << L"dicomFileName        = name of the dicom file" << std::endl;
            std::wcout << L"jpegFileName         = name of the output jpeg file" << std::endl;
            std::wcout << L"-ffmpeg FFMPEGPATH   = launches FFMPEG after generating the jpeg images." << std::endl;
            std::wcout << L" FFMPEGPATH is the path to FFMPEG" << std::endl;
            std::wcout << L" FFMPEGOPT are the options for ffmpeg" << std::endl;
            std::wcout << L" The input images and the frame rate are added automatically to the options" << std::endl;
            return 1;
        }


        // Check for the -ffmpeg flag
        int ffmpegFlag(findArgument("-ffmpeg", argc, argv));
        size_t framesCount(0);

        DataSet loadedDataSet = CodecFactory::load(argv[1], 2048);

        outputDatasetTags(loadedDataSet, L"");

        if(argc < 3)
        {
            return 0;
        }

        // Separate the extension from the file name
        std::string outputFileName(argv[2]);
        std::string extension;
        size_t dotPos(outputFileName.rfind('.'));
        if(dotPos != outputFileName.npos)
        {
            extension = outputFileName.substr(dotPos);
            outputFileName.erase(dotPos);
        }
        else
        {
            extension = ".jpg";
        }

        try
        {
            // Build the transforms chain
            /////////////////////////////
            TransformsChain chain;
            std::uint32_t width(0);
            std::uint32_t height(0);

            {
                // Get the first image. We use it in case there isn't any presentation VOI/LUT
                //  and we have to calculate the optimal one
                //////////////////////////////////////////////////////////////////////////////
                Image dataSetImage = loadedDataSet.getImageApplyModalityTransform(0);
                width = dataSetImage.getWidth();
                height = dataSetImage.getHeight();

                if(ColorTransformsFactory::isMonochrome(dataSetImage.getColorSpace()))
                {
                    vois_t vois = loadedDataSet.getVOIs();
                    if(!vois.empty())
                    {
                        chain.addTransform(VOILUT(vois.front()));
                    }
                    else
                    {
                        // Now find the optimal VOILUT
                        //////////////////////////////
                        VOIDescription voiDescription = VOILUT::getOptimalVOI(dataSetImage, 0, 0, width, height);
                        chain.addTransform(VOILUT(voiDescription));
                    }
                }

                // Get the colorspace of the transformation output
                //////////////////////////////////////////////////
                std::string initialColorSpace;
                if(chain.isEmpty())
                {
                    initialColorSpace = dataSetImage.getColorSpace();
                }
                else
                {
                    Image startImage = chain.allocateOutputImage(dataSetImage, 1, 1);
                    initialColorSpace = startImage.getColorSpace();
                }

                // Color transform to YCrCb
                ///////////////////////////
                if(initialColorSpace != "YBR_FULL")
                {
                    Transform colorTransform = ColorTransformsFactory::getTransform(initialColorSpace, "YBR_FULL");
                    if(!colorTransform.isEmpty())
                    {
                        chain.addTransform(colorTransform);
                    }
                }

                // Tell the chain transform to allocate the output image:
                // if it has an high-bit different from 7 then we need to add
                //  a TransformHighBit.
                /////////////////////////////////////////////////////////////
                Image testImage = chain.allocateOutputImage(dataSetImage, 1, 1);
                if(testImage.getHighBit() != 7)
                {
                    chain.addTransform(TransformHighBit());
                }
            }

            // Allocate the image used to build the jpeg file
            /////////////////////////////////////////////////
            Image rgb8Image(width, height, bitDepth_t::depthU8, "YBR_FULL", 7);

            // Scan through the frames
            //////////////////////////
            for(std::uint32_t frameNumber(0); ; ++frameNumber)
            {
                Image dataSetImage = loadedDataSet.getImageApplyModalityTransform(frameNumber);

                Image* pFinalImage = &dataSetImage;

                if(!chain.isEmpty())
                {
                    chain.runTransform(dataSetImage, 0, 0, width, height, rgb8Image, 0, 0);
                    pFinalImage = &rgb8Image;
                }

                // Open a stream for the jpeg
                /////////////////////////////
                std::ostringstream jpegFileName;
                jpegFileName << outputFileName;
                if(frameNumber != 0 || ffmpegFlag >= 0)
                {
                    jpegFileName << "_" << frameNumber;
                }
                jpegFileName << extension;

                FileStreamOutput writeJpeg(jpegFileName.str());
                StreamWriter writer(writeJpeg);

                const std::string jpegTransferSyntax("1.2.840.10008.1.2.4.50");
                CodecFactory::saveImage(writer, *pFinalImage, jpegTransferSyntax, imageQuality_t::veryHigh, 8, false, false, true, false);

                ++framesCount;
            }
        }
        catch(const DataSetImageDoesntExistError&)
        {
            // Ignore this exception. It is thrown when we reach the
            //  end of the images list
            //exceptionsManager::getMessage();
        }

        // All the images have been generated.
        // Should we launch FFMPEG?
        if(ffmpegFlag >= 0 && framesCount != 0)
        {
            // List of arguments to be passed to ffmpeg
            typedef std::list<std::string> tOptionsList;
            tOptionsList options;

            // The first argument is the application's name
            options.push_back(argv[ffmpegFlag + 1]);

            // Calculate the frames per second from the available tags
            double framesPerSecond(0);
            double frameTime(loadedDataSet.getDouble(TagId(tagId_t::FrameTime_0018_1063), 0, 0));
            if(frameTime > 0.1)
            {
                framesPerSecond = 1000 / frameTime;
            }
            if(framesPerSecond < 0.1)
            {
                framesPerSecond = loadedDataSet.getUnsignedLong(TagId(tagId_t::CineRate_0018_0040), 0, 0);
            }
            if(framesPerSecond < 0.1)
            {
                framesPerSecond = loadedDataSet.getUnsignedLong(TagId(tagId_t::RecommendedDisplayFrameRate_0008_2144), 0, 0);
            }

            // Add the ffmpeg argument for the frames per second
            if(framesPerSecond > 0.1)
            {
                options.push_back("-r");
                std::ostringstream frameRate;
                frameRate << framesPerSecond;
                options.push_back(frameRate.str());
            }

            // Add the ffmpeg argument for the input files
            options.push_back("-i");
            options.push_back(outputFileName + "_%d" + extension);

            // Add the ffmpeg argument for the number of frames
            options.push_back("-dframes");
            std::ostringstream frameCount;
            frameCount << (unsigned long)framesCount;
            options.push_back(frameCount.str());

            // Add the arguments specified when dicom2jpeg was launched
            for(int copyArguments(ffmpegFlag + 2); copyArguments < argc; ++copyArguments)
            {
                options.push_back(argv[copyArguments]);
            }

            // Build the arguments array
            std::unique_ptr<const char*> ffArgv(new const char*[options.size() + 1]);
            size_t insertPosition(0);
            for(tOptionsList::iterator scanOptions(options.begin()); scanOptions != options.end(); ++scanOptions, ++insertPosition)
            {
                ffArgv.get()[insertPosition] = (*scanOptions).c_str();
            }
            ffArgv.get()[options.size()] = 0;

            // Launch ffmpeg
#if defined(WIN32) || defined(WIN64)
            return (int)_spawnvp(_P_WAIT , argv[ffmpegFlag + 1], ffArgv.get());
#else
            char *environment[] = {0};

            pid_t process_id;
            posix_spawnp (&process_id, argv[ffmpegFlag + 1],
                    0, 0, (char* const*)ffArgv.get(), (char* const*)environment);
            wait(0);
#endif

        }

        return 0;

    }
    catch(const std::exception& e)
    {
        DataSet convertMessage;
        convertMessage.setString(TagId(10, 10), ExceptionsManager::getExceptionTrace(), tagVR_t::LT);
        std::wcout << std::endl << "Error: " << std::endl << convertMessage.getUnicodeString(TagId(10, 10), 0) << std::endl;
        return 1;
    }
}

