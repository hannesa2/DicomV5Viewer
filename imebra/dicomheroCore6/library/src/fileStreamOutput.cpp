/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file fileStreamOutput.cpp
    \brief Implementation of the file output stream class.

*/

#include "../include/dicomhero6/fileStreamOutput.h"
#include "../implementation/fileStreamImpl.h"

namespace dicomhero
{

FileStreamOutput::FileStreamOutput(const std::wstring& name): BaseStreamOutput(std::make_shared<implementation::fileStreamOutput>(name))
{
}

FileStreamOutput::FileStreamOutput(const std::string& name): BaseStreamOutput(std::make_shared<implementation::fileStreamOutput>(name))
{
}

FileStreamOutput::FileStreamOutput(const FileStreamOutput& source): BaseStreamOutput(source)
{
}

FileStreamOutput::~FileStreamOutput()
{
}

}
