/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file dicomDir.cpp
    \brief Implementation of the classes that parse/create a DICOMDIR
        structure (DicomDir and DicomDirEntry).

*/

#include "../include/dicomhero6/dicomDirEntry.h"
#include "../include/dicomhero6/dataSet.h"
#include "../implementation/dicomDirImpl.h"
#include "../implementation/exceptionImpl.h"
#include "../include/dicomhero6/exceptions.h"

namespace dicomhero
{

DicomDirEntry::DicomDirEntry(const DicomDirEntry &source): m_pDirectoryRecord(getDicomDirEntryImplementation(source))
{
}

DicomDirEntry::DicomDirEntry(const std::shared_ptr<dicomhero::implementation::directoryRecord>& pDirectoryRecord): m_pDirectoryRecord(pDirectoryRecord)
{
}

const std::shared_ptr<implementation::directoryRecord>& getDicomDirEntryImplementation(const DicomDirEntry& dicomDirEntry)
{
    return dicomDirEntry.m_pDirectoryRecord;
}

DicomDirEntry::~DicomDirEntry()
{
}

DataSet DicomDirEntry::getEntryDataSet() const
{
    DICOMHERO_FUNCTION_START();

    return DataSet(m_pDirectoryRecord->getRecordDataSet());

    DICOMHERO_FUNCTION_END_LOG();
}

bool DicomDirEntry::hasNextEntry() const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::directoryRecord> pNextEntry(m_pDirectoryRecord->getNextRecord());
    return pNextEntry != 0;

    DICOMHERO_FUNCTION_END_LOG();
}

DicomDirEntry DicomDirEntry::getNextEntry() const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::directoryRecord> pNextEntry(m_pDirectoryRecord->getNextRecord());
    if(pNextEntry == 0)
    {
        throw DicomDirNoEntryError("Missing sibling entry");;
    }
    return DicomDirEntry(pNextEntry);

    DICOMHERO_FUNCTION_END_LOG();
}

bool DicomDirEntry::hasChildren() const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::directoryRecord> pChildEntry(m_pDirectoryRecord->getFirstChildRecord());
    return pChildEntry != 0;

    DICOMHERO_FUNCTION_END_LOG();
}

DicomDirEntry DicomDirEntry::getFirstChildEntry() const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::directoryRecord> pChildEntry(m_pDirectoryRecord->getFirstChildRecord());
    if(pChildEntry == 0)
    {
        throw DicomDirNoEntryError("There isn't any child entry");
    }
    return DicomDirEntry(pChildEntry);

    DICOMHERO_FUNCTION_END_LOG();
}

fileParts_t DicomDirEntry::getFileParts() const
{
    DICOMHERO_FUNCTION_START();

    return m_pDirectoryRecord->getFileParts();

    DICOMHERO_FUNCTION_END_LOG();
}

std::string DicomDirEntry::getTypeString() const
{
    DICOMHERO_FUNCTION_START();

    return m_pDirectoryRecord->getTypeString();

    DICOMHERO_FUNCTION_END_LOG();
}

DataSet DicomDirEntry::getEntryDataSet()
{
    DICOMHERO_FUNCTION_START();

    return DataSet(getDicomDirEntryImplementation(*this)->getRecordDataSet());

    DICOMHERO_FUNCTION_END_LOG();

}

void DicomDirEntry::setNextEntry(const DicomDirEntry& nextEntry)
{
    DICOMHERO_FUNCTION_START();

    getDicomDirEntryImplementation(*this)->setNextRecord(getDicomDirEntryImplementation(nextEntry));

    DICOMHERO_FUNCTION_END_LOG();
}

void DicomDirEntry::setFirstChildEntry(const DicomDirEntry& firstChildEntry)
{
    DICOMHERO_FUNCTION_START();

    getDicomDirEntryImplementation(*this)->setFirstChildRecord(getDicomDirEntryImplementation(firstChildEntry));

    DICOMHERO_FUNCTION_END_LOG();
}

void DicomDirEntry::setFileParts(const fileParts_t& fileParts)
{
    DICOMHERO_FUNCTION_START();

    getDicomDirEntryImplementation(*this)->setFileParts(fileParts);

    DICOMHERO_FUNCTION_END_LOG();
}

}
