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

#include "../include/dicomhero6/dicomDir.h"
#include "../include/dicomhero6/dataSet.h"
#include "../include/dicomhero6/dicomDirEntry.h"
#include "../implementation/dicomDirImpl.h"
#include "../implementation/exceptionImpl.h"
#include "../include/dicomhero6/exceptions.h"

namespace dicomhero
{

DicomDir::DicomDir(): DicomDir(std::make_shared<dicomhero::implementation::dicomDir>())
{
}

DicomDir::DicomDir(const DataSet& fromDataSet): m_pDicomDir(std::make_shared<dicomhero::implementation::dicomDir>(getDataSetImplementation(fromDataSet)))
{
}

DicomDir::DicomDir(const DicomDir& source): m_pDicomDir(getDicomDirImplementation(source))
{
}

const std::shared_ptr<implementation::dicomDir>& getDicomDirImplementation(const DicomDir& dicomDir)
{
    return dicomDir.m_pDicomDir;
}

DicomDir::DicomDir(const std::shared_ptr<implementation::dicomDir>& pDicomDir): m_pDicomDir(pDicomDir)
{
}

DicomDir::~DicomDir()
{
}

bool DicomDir::hasRootEntry() const
{
    std::shared_ptr<implementation::directoryRecord> pRootRecord(m_pDicomDir->getFirstRootRecord());
    return pRootRecord != 0;
}

DicomDirEntry DicomDir::getFirstRootEntry() const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::directoryRecord> pRootRecord(m_pDicomDir->getFirstRootRecord());
    if(pRootRecord == 0)
    {
        throw DicomDirNoEntryError("Missing root entry");
    }
    return DicomDirEntry(pRootRecord);

    DICOMHERO_FUNCTION_END_LOG();
}

DicomDirEntry DicomDir::getNewEntry(const std::string& recordType)
{
    DICOMHERO_FUNCTION_START();

    return DicomDirEntry(getDicomDirImplementation(*this)->getNewRecord(recordType));

    DICOMHERO_FUNCTION_END_LOG();
}

void DicomDir::setFirstRootEntry(const DicomDirEntry& firstEntryRecord)
{
    DICOMHERO_FUNCTION_START();

    getDicomDirImplementation(*this)->setFirstRootRecord(getDicomDirEntryImplementation(firstEntryRecord));

    DICOMHERO_FUNCTION_END_LOG();
}

DataSet DicomDir::updateDataSet()
{
    DICOMHERO_FUNCTION_START();

    return DataSet(getDicomDirImplementation(*this)->buildDataSet());

    DICOMHERO_FUNCTION_END_LOG();
}

}
