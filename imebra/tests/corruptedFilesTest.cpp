#include <imebra/imebra.h>
#include "testsSettings.h"
#include <iostream>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <dirent.h>
#endif
#include <gtest/gtest.h>

namespace imebra
{

namespace tests
{

TEST(corruptedFilesTest, corruptedFilesTest)
{
    ::tests::settings& settings = ::tests::settings::getSettings();

    std::string folder = settings.get("--corruptedFilesFolder");
    if(folder.empty())
    {
        return;
    }

#ifdef _WIN32
    WIN32_FIND_DATA findFileData;
    std::string filter(folder);
    filter += "\\*";

    std::cout << "Processing corrupted files in folder " << filter << std::endl;

    HANDLE hFind(FindFirstFile(filter.c_str(), &findFileData));
    if(hFind == INVALID_HANDLE_VALUE)
    {
        return;
    }

    try
    {
        do
        {
            const std::string fileName(findFileData.cFileName);
            if(fileName.at(0) == '.')
            {
                continue;
            }
            std::ostringstream fullName;
            fullName << folder << "\\" << fileName;

            std::cout << "Processing corrupted file " << fullName.str() << std::endl;

            DataSet dataset = imebra::CodecFactory::load(fullName.str(), 2048);

            ASSERT_THROW(dataset.getImage(0), imebra::CodecError);
        }
        while (FindNextFile(hFind, &findFileData) != 0);
    }
    catch(...)
    {
        FindClose(hFind);
        throw;
    }

#else
    DIR * dir = opendir(folder.c_str());
    if(dir == 0)
    {
        std::cout << folder << " not found" << std::endl;
        ASSERT_FALSE(true);
    }

    for(dirent* dirEntry = readdir(dir); dirEntry != 0; dirEntry = readdir(dir))
    {
        const std::string fileName(dirEntry->d_name);
        if(fileName.at(0) == '.')
        {
            continue;
        }
        std::ostringstream fullName;
        fullName << folder << "/" << fileName;

        std::cout << "Processing corrupted file " << fullName.str() << std::endl;

        DataSet dataset = imebra::CodecFactory::load(fullName.str(), 2048);

        ASSERT_THROW(dataset.getImage(0), imebra::CodecError);
    }
#endif
}

}

}


