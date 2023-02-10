/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file dicomDir.h
    \brief Declaration of the class DicomDir.

*/

#if !defined(imebraDicomDir__INCLUDED_)
#define imebraDicomDir__INCLUDED_

#include <memory>
#include <string>
#include "definitions.h"

namespace dicomhero
{

namespace implementation
{
    class dicomDir;
}

class DataSet;
class DicomDirEntry;

///
/// \brief Represents a DICOMDIR structure.
///
/// In order to work DicomDir needs a DataSet, which embeds the DicomDir's
/// entries.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DicomDir
{

public:
    /// \brief Construct an empty DicomDir.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DicomDir();

    /// \brief Construct a DicomDir from a DataSet object.
    ///
    /// \param fromDataSet the DataSet created from reading a DICOMDIR file
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit DicomDir(const DataSet& fromDataSet);

    ///
    /// \brief Copy constructor.
    ///
    /// \param source source DICOMDIR
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DicomDir(const DicomDir& source);

    DicomDir& operator=(const DicomDir& source) = delete;

    /// \brief Destructor.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~DicomDir();

    /// \brief Return a new DicomDirEntry record and insert it into the DicomDir's
    ///        DataSet.
    ///
    /// \param recordType the type of the new entry
    /// \return a new DicomDirEntry object that can be inserted into the DicomDir
    ///         object or one of its children DicomDirEntry entries.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DicomDirEntry getNewEntry(const std::string& recordType);

    ///
    /// \brief Returns true if the DICOMDIR has a root entry.
    ///
    /// \return true if the DICOMDIR has a root entry, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////////
    bool hasRootEntry() const;

    /// \brief Set the specified entry as the first DicomDir's root record.
    ///
    /// After the DicomDir's content has been modified it is necessary to call
    /// updateDataSet() before the DataSet managed by DicomDir can be used.
    ///
    /// \param firstEntryRecord the DicomDirEntry object to set as the first root
    ///                         entry
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void setFirstRootEntry(const DicomDirEntry& firstEntryRecord);

    /// \brief This method has to be called to update the managed DataSet after
    ///        the DicomDir's content has been updated.
    ///
    /// It is not necessary to call updateDataSet() after every DicomDir update,
    /// just call it when the updated DataSet object is needed.
    ///
    /// \return the updated managed DataSet object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataSet updateDataSet();

    /// \brief Retrieve the first DicomDir's root entry.
    ///
    /// If the root entry is missing then return a null pointer.
    ///
    /// \return the root DicomDirEntry or a null pointer if the root
    ///         DicomDirEntry does noot exist
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DicomDirEntry getFirstRootEntry() const;

#ifndef SWIG
protected:
    explicit DicomDir(const std::shared_ptr<implementation::dicomDir>& pDicomDir);

private:
    friend const std::shared_ptr<implementation::dicomDir>& getDicomDirImplementation(const DicomDir& dicomDir);
    std::shared_ptr<dicomhero::implementation::dicomDir> m_pDicomDir;
#endif
};


/// \deprecated
///
///////////////////////////////////////////////////////////////////////////////
using MutableDicomDir = DicomDir;

}

#endif // !defined(imebraDicomDir__INCLUDED_)
