// dicomdirItems.cpp
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <imebra/imebra.h>

using namespace imebra;

///////////////////////////////////////////////////////////
//
// Convert a string to XML entities that can be safely
//  embedded in a XML file
//
///////////////////////////////////////////////////////////
std::wstring xmlEntities(std::wstring value)
{
	std::wostringstream outputStream;
	for(std::wstring::iterator scanValue(value.begin()); scanValue != value.end(); ++scanValue)
	{
		switch(*scanValue)
		{
		case L'"':
			outputStream << L"&quot;";
			break;
		case L'&':
			outputStream << L"&amp;";
			break;
		case L'\'':
			outputStream << L"&apos;";
			break;
		case L'<':
			outputStream << L"&lt;";
			break;
		case '>':
			outputStream << L"&gt;";
			break;
		default:
			if(*scanValue < 33)
			{
				outputStream << L"&#" << (int)(*scanValue) << L";";
				break;
			}
			outputStream << *scanValue;
		}
	}

	return outputStream.str();
}


///////////////////////////////////////////////////////////
//
// Output a tag from the dataset in an XML tag
//
///////////////////////////////////////////////////////////
void outputTag(const DataSet& dataSet, std::uint16_t group, std::uint16_t tag, std::wostream* pOutputStream, std::wstring tagName, std::uint16_t id = 0)
{
    try
    {
        ReadingDataHandler tagHandler = dataSet.getReadingDataHandler(TagId(group, tag), 0);

        *pOutputStream << L"<" << tagName;
        if(id != 0)
        {
            *pOutputStream << L" tagid=\"" << id << L"\" ";
        }
        *pOutputStream << L">";

        for(size_t scanValues(0); scanValues!= tagHandler.getSize(); ++scanValues)
        {
            if(scanValues != 0)
            {
                *pOutputStream << L"\\";
            }
            *pOutputStream << xmlEntities(tagHandler.getUnicodeString(scanValues));
        }

        *pOutputStream << L"</" << tagName << L">\n";

    }
    catch(MissingDataElementError&)
    {
        *pOutputStream << L"<" << tagName << L" />\n";
    }
}


///////////////////////////////////////////////////////////
//
// Scan all the sibling records (and their children) of
//  the specified one
//
///////////////////////////////////////////////////////////
void scanChildren(const DicomDirEntry& record, std::wostream* pOutputStream)
{
    do
	{
        DataSet recordDataSet = record.getEntryDataSet();

		// Output the file parts
        outputTag(recordDataSet, 0x4, 0x1500, pOutputStream, L"file");

		// Output the class UID
        outputTag(recordDataSet, 0x4, 0x1510, pOutputStream, L"class");

		// Output the instance UID
        outputTag(recordDataSet, 0x4, 0x1511, pOutputStream, L"instance");

		// Output the transfer syntax
        outputTag(recordDataSet, 0x4, 0x1512, pOutputStream, L"transfer");

		// Output the groups (everything but group 2 and 4)
        tagsIds_t tags = recordDataSet.getTags();
        std::uint16_t previousGroup = 0;
        for(tagsIds_t::const_iterator scanTags(tags.begin()), endTags(tags.end()); scanTags != endTags; ++scanTags)
        {
            std::uint16_t groupId = (*scanTags).getGroupId();
            std::uint16_t tagId = (*scanTags).getTagId();
            if(groupId == 2 || groupId == 4)
            {
                continue;
            }
            if(groupId != previousGroup)
            {
                previousGroup = groupId;
                if(previousGroup != 0)
                {
                    *pOutputStream << L"</group>" << std::endl;
                }
                *pOutputStream << L"<group groupid=\"" << groupId << L"\">" << std::endl;
            }
            outputTag(recordDataSet, groupId, tagId, pOutputStream, L"tag", tagId);
        }
        if(previousGroup != 0)
        {
            *pOutputStream << L"</group>" << std::endl;
        }

		// Output the child records
        if(record.hasChildren())
        {
            (*pOutputStream) << L"<children>\n";
            scanChildren(record.getFirstChildEntry(), pOutputStream);
            (*pOutputStream) << L"</children>\n";
        }
		(*pOutputStream) << L"</record>\n";

	}
    while(record.hasNextEntry());
}


///////////////////////////////////////////////////////////
//
// Entry point
//
///////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{


	// Output the help if the parameters have not been
	//  specified
	if(argc < 2)
	{
        std::wstring version(L"1.0.0.1");
        std::wcout << L"dicomdirItems version " << version << L"\n";
		std::wcout << L"Usage: dicomdirItems dicomdirFileName outputFileName\n";
		std::wcout << L" dicomdirFileName = name of the DICOMDIR file\n";
		return 1;
	}

    // Open the file containing the dicom directory
    DataSet loadedDataSet = CodecFactory::load(argv[1], 2048);

	// Now create a dicomdir object
    DicomDir directory(loadedDataSet);

	try
	{
		std::wcout << L"<dicomdir>";
        if(directory.hasRootEntry())
        {
            scanChildren(directory.getFirstRootEntry(), &(std::wcout));
        }
		std::wcout << L"</dicomdir>";
		return 0;
	}
	catch(...)
	{
        std::cout << ExceptionsManager::getExceptionTrace();
		return 1;
	}
}

