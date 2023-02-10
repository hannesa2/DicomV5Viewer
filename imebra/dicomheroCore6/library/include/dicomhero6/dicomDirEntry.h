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
    \brief Declaration of the class DicomDirEntry
        structure (DicomDir and DirectoryRecord)

*/

#if !defined(imebraDicomDirEntry__INCLUDED_)
#define imebraDicomDirEntry__INCLUDED_

#include <memory>
#include <string>
#include "definitions.h"

namespace dicomhero
{

namespace implementation
{
    class directoryRecord;
}

class DataSet;

///
/// \brief Represents a single immutable DICOMDIR entry.
///
/// Each entry can be followed by a sibling entry (on the same depth level)
/// or can point to its first child entry (one level deeper).
///
/// Each DicomDirEntry object manages a DataSet which is used to store the
/// entry's data. The DataSet objects managed by DicomDirEntry objects are
/// inserted as sequence items into the DicomDir's DataSet.
///
///////////////////////////////////////////////////////////////////////////////
class DICOMHERO_API DicomDirEntry
{

    friend class DicomDir;

public:

    ///
    /// \brief Copy constructor.
    ///
    /// \param source source DICOMDIR entry
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DicomDirEntry(const DicomDirEntry& source);

    DicomDirEntry& operator=(const DicomDirEntry& source) = delete;

    virtual ~DicomDirEntry();

    /// \brief Return the DataSet managed by the DicomDirEntry object.
    ///
    /// \return the DataSet managed by the DicomDirEntry object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataSet getEntryDataSet() const;

    bool hasNextEntry() const;

    /// \brief Return the next sibling entry (on the same depth level).
    ///
    /// If the next DicomDirEntry is missing (this is the last entry) then
    /// return a null pointer.
    ///
    /// \return the next sibling DicomDirEntry object, or a null pointer if the
    ///         next sibling DicomDirEntry does not exist
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DicomDirEntry getNextEntry() const;

    bool hasChildren() const;

    /// \brief Return the first child entry (one level deeper).
    ///
    /// If the first child DicomDirEntry is missing then return a null pointer.
    ///
    /// \return the first child DicomDirEntry object, or a null pointer if there
    ///         aren't any children
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DicomDirEntry getFirstChildEntry() const;

    /// \brief Returns the parts that form the name of the file referenced by the
    ///        DicomDirEntry object.
    ///
    /// \return a list of strings that form the name of the file referenced by the
    ///         DicomDirEntry object. The last item in the list is the file name,
    ///         while the preceding items contain the folders names.
    ///         For instance, on Linux the parts "folder0", "folder1", "fileName"
    ///         represent the path "folder0/folder1/fileName"
    ///
    ///////////////////////////////////////////////////////////////////////////////
    fileParts_t getFileParts() const;

    std::string getTypeString() const;

    /// \brief Return the DataSet managed by the DicomDirEntry object.
    ///
    /// \return the DataSet managed by the DicomDirEntry object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DataSet getEntryDataSet();

    /// \brief Set the next sibling entry (one the same depth level).
    ///
    /// \param nextEntry the next sibling DicomDirEntry object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void setNextEntry(const DicomDirEntry& nextEntry);

    /// \brief Set the first child entry (one level deeper).
    ///
    /// \param firstChildEntry the first child DicomDirEntry object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void setFirstChildEntry(const DicomDirEntry& firstChildEntry);

    /// \brief Set the parts that form the name of the file referenced by the
    ///        DicomDirEntry object.
    ///
    /// \param fileParts  a list of strings that form the name of the file
    ///                   referenced by the DicomDirEntry object. The last item
    ///                   in the list is the file name, while the preceding items
    ///                   contain the folders names.
    ///                   For instance, on Linux the parts "folder0", "folder1",
    ///                   "fileName" represent the path "folder0/folder1/fileName"
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void setFileParts(const fileParts_t& fileParts);



#ifndef SWIG
protected:
    explicit DicomDirEntry(const std::shared_ptr<dicomhero::implementation::directoryRecord>& pDirectoryRecord);

private:
    friend const std::shared_ptr<implementation::directoryRecord>& getDicomDirEntryImplementation(const DicomDirEntry& dicomDirEntry);
    std::shared_ptr<dicomhero::implementation::directoryRecord> m_pDirectoryRecord;
#endif
};


/// \deprecated
///
///////////////////////////////////////////////////////////////////////////////
using MutableDicomDirEntry = DicomDirEntry;

}

#endif // !defined(imebraDicomDirEntry__INCLUDED_)
