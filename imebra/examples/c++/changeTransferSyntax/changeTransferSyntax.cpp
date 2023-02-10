/*

Imebra 5.3.3.0 changeset 2c706290

Imebra: a C++ Dicom library

Copyright (c) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016
by Paolo Brandoli/Binarno s.p.

All rights reserved.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 2 as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

-------------------

If you want to use Imebra commercially then you have to buy the commercial
license available at http://imebra.com

After you buy the commercial license then you can use Imebra according
to the terms described in the Imebra Commercial License.
A copy of the Imebra Commercial License is available at http://imebra.com.

Imebra is available at http://imebra.com

The author can be contacted by email at info@binarno.com or by mail at
the following address:
Binarno s.p., Paolo Brandoli
Rakuseva 14
1000 Ljubljana
Slovenia



*/

#include <iostream>


#include <imebra/imebra.h>
#include <sstream>

#if defined(WIN32) || defined(WIN64)
#include <process.h>
#else
#include <spawn.h>
#include <sys/wait.h>
#endif

#include <memory>
#include <list>

using namespace imebra;

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

void CopyGroups(const DataSet& source, MutableDataSet& destination)
{
    tagsIds_t tags(source.getTags());

    for(tagsIds_t::const_iterator scanTags(tags.begin()), endTags(tags.end()); scanTags != endTags; ++scanTags)
    {
        if((*scanTags).getGroupId() == 0x7fe0)
        {
            continue;
        }
        try
        {
            destination.getTag(*scanTags);
        }
        catch(const MissingDataElementError&)
        {
            Tag sourceTag = source.getTag(*scanTags);
            MutableTag destTag = destination.getTagCreate(*scanTags, sourceTag.getDataType());

            try
            {
                for(size_t buffer(0); ; ++buffer)
                {
                    try
                    {
                        DataSet sequence = sourceTag.getSequenceItem(buffer);
                        MutableDataSet destSequence = destination.appendSequenceItem(*scanTags);
                        CopyGroups(sequence, destSequence);
                    }
                    catch(const MissingDataElementError&)
                    {
                        ReadingDataHandler sourceHandler = sourceTag.getReadingDataHandler(buffer);
                        WritingDataHandler destHandler = destTag.getWritingDataHandler(buffer);
                        destHandler.setSize(sourceHandler.getSize());
                        for(size_t item(0); item != sourceHandler.getSize(); ++item)
                        {
                            destHandler.setUnicodeString(item, sourceHandler.getUnicodeString(item));
                        }
                    }
                }
            }
            catch(const MissingDataElementError&)
            {

            }
        }
    }
}

int main(int argc, char* argv[])
{
    std::string version("1.0.0.1");
    std::cout << "changeTransferSyntax version " << version << std::endl;

    try
    {
        std::string inputFileName;
        std::string outputFileName;
        std::string transferSyntax;
        std::uint32_t maxHighBit;

        if(argc == 4)
        {
            inputFileName = argv[1];
            outputFileName = argv[2];

            const char* transferSyntaxAllowedValues[]=
            {
                "1.2.840.10008.1.2.1", // Explicit VR little endian
                "1.2.840.10008.1.2.2", // Explicit VR big endian
                "1.2.840.10008.1.2.5", // RLE compression
                "1.2.840.10008.1.2.4.50", // Jpeg baseline (8 bits lossy)
                "1.2.840.10008.1.2.4.51", // Jpeg extended (12 bits lossy)
                "1.2.840.10008.1.2.4.57" // Jpeg lossless NH
            };

            const std::uint32_t maxHighBitValues[]=
            {
                31,
                31,
                31,
                7,
                11,
                15
            };

            std::istringstream convertTransferSyntax(argv[3]);
            int transferSyntaxValue(-1);
            convertTransferSyntax >> transferSyntaxValue;
            if(transferSyntaxValue >= 0 && (size_t)transferSyntaxValue < sizeof(transferSyntaxAllowedValues)/sizeof(char*))
            {
                transferSyntax = transferSyntaxAllowedValues[transferSyntaxValue];
                maxHighBit = maxHighBitValues[transferSyntaxValue];
            }
        }

        if(inputFileName.empty() || outputFileName.empty() || transferSyntax.empty())
        {
                    std::cout << "Usage: changeTransferSyntax inputFileName outputFileName newTransferSyntax" << std::endl;
                    std::cout << "newTransferSyntax values: 0 = Explicit VR little endian" << std::endl;
                    std::cout << "                          1 = Explicit VR big endian" << std::endl;
                    std::cout << "                          2 = RLE compression" << std::endl;
                    std::cout << "                          3 = Jpeg baseline (8 bits lossy)" << std::endl;
                    std::cout << "                          4 = Jpeg extended (12 bits lossy)" << std::endl;
                    std::cout << "                          5 = Jpeg lossless NH" << std::endl;
                    return 1;
        }

        DataSet loadedDataSet = CodecFactory::load(inputFileName, 2048);


        // Now we create a new dataset and copy the tags and images from the loaded dataset
        MutableDataSet newDataSet(transferSyntax);

        // Copy the images first
        try
        {
            for(size_t scanImages(0);; ++scanImages)
            {
                Image copyImage = loadedDataSet.getImage(scanImages);
                if(copyImage.getHighBit() > maxHighBit)
                {
                    std::cout << "WARNING: image has highBit=" << copyImage.getHighBit() <<
                                 " but the selected transfer syntax support highBit<=" <<
                                 maxHighBit << std::endl;
                }
                newDataSet.setImage(scanImages, copyImage, imageQuality_t::high);
            }
        }
        catch(const DataSetImageDoesntExistError&)
        {
            // Ignore this
        }

        CopyGroups(loadedDataSet, newDataSet);

        CodecFactory::save(newDataSet, outputFileName, codecType_t::dicom);

    }
    catch(...)
    {
        std::cout << ExceptionsManager::getExceptionTrace();
        return 1;
    }
}

