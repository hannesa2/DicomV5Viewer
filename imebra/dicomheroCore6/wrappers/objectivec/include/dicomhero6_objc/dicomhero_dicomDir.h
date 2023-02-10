/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcDicomDir__INCLUDED_)
#define dicomheroObjcDicomDir__INCLUDED_

#import <Foundation/Foundation.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSString.h>
#include "dicomhero_macros.h"

@class DicomheroDataSet;


///
/// \brief Represents a single DICOMDIR entry.
///
/// Each entry can be followed by a sibling entry (on the same depth level)
/// and/or can point to its first child entry (one level deeper).
///
/// Each DicomheroDicomDirEntry object manages a DicomheroDataSet which is used to
/// store the entry's data. The DicomheroDataSet objects managed by
/// DicomheroDicomDirEntry objects are inserted as sequence items into the
/// DicomheroDicomDir's dataSet.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroDicomDirEntry: NSObject

{
    @public
    define_dicomhero_object_holder(DicomDirEntry);
}

    -(id)initWithDicomheroDicomDirEntry:define_dicomhero_parameter(DicomDirEntry);

    -(void)dealloc;

    /// \brief Return the DicomheroDataSet managed by the DicomheroDicomDirEntry object.
    ///
    /// \return the DicomheroDataSet managed by the DicomheroDicomDirEntry object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(DicomheroDataSet*)getEntryDataSet;

    /// \brief Return the next sibling entry (on the same depth level).
    ///
    /// If the next DicomheroDicomDirEntry is missing (this is the last entry) then
    /// return a null pointer.
    ///
    /// \return the next sibling DicomheroDicomDirEntry object, or a null pointer if
    ///         the next sibling does not exist
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(DicomheroDicomDirEntry*)getNextEntry;

    /// \brief Return the first child entry (one level deeper).
    ///
    /// If the first child DicomheroDicomDirEntry is missing then return a null
    /// pointer.
    ///
    /// \return the first child DicomheroDicomDirEntry object, or a null pointer if
    ///         there aren't any children
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(DicomheroDicomDirEntry*)getFirstChildEntry;

    /// \brief Returns the parts that form the name of the file referenced by the
    ///        DicomheroDicomDirEntry object.
    ///
    /// \return a NSArray of NSString objects that form the name of the file
    ///         referenced by the DicomheroDicomDirEntry object. The last item in the
    ///         array is the file name, while the preceding items contain the
    ///         folders names.
    ///         For instance, the parts "folder0", "folder1", "fileName"
    ///         represent the path "folder0/folder1/fileName"
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(NSArray*)getFileParts:(NSError**)pError;

    -(NSString*)getTypeString:(NSError**)pError;

    /// \brief Set the next sibling entry (one the same depth level).
    ///
    /// \param nextEntry the next sibling DicomheroDicomDirEntry object
    /// \param pError    set to a NSError derived class in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)setNextEntry:(DicomheroDicomDirEntry*)pNextEntry error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Set the first child entry (one level deeper).
    ///
    /// \param firstChildEntry the first child DicomheroDicomDirEntry object
    /// \param pError          set to a NSError derived class in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)setFirstChildEntry:(DicomheroDicomDirEntry*)pFirstChildEntry error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Set the parts that form the name of the file referenced by the
    ///        DicomDirEntry object.
    ///
    /// \param fileParts  a NSArray of NSString objects that form the name of the
    ///                   file referenced by the DicomheroDicomDirEntry object.
    ///                   The last item in the list is the file name, while the
    ///                   preceding items contain the folders names.
    ///                   For instance, the parts "folder0", "folder1",
    ///                   "fileName" represent the path "folder0/folder1/fileName"
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)setFileParts:(NSArray*)pFileParts error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

@end



///
/// \brief Represents a DICOMDIR structure.
///
/// In order to work DicomheroDicomDir needs a DicomheroDataSet, which embeds
/// the DICOMDIR's entries.
///
/// If the DicomheroDicomDir's content is modified then the method updateDataSet()
/// has to be called to obtain a dataset that can be stored as a DICOMDIR
/// file.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroDicomDir: NSObject

{
    @public
    define_dicomhero_object_holder(DicomDir);
}

    /// \brief Construct an empty DicomDir.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)init;

    -(id)initWithDicomheroDicomDir:define_dicomhero_parameter(DicomDir);

    /// \brief Construct an DicomheroDicomDir from an DicomheroDataSet object.
    ///
    /// \param pDataSet the DicomheroDataSet created from reading a DICOMDIR file
    /// \param pError   set to an NSError derived class in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithDataSet:(DicomheroDataSet*)pDataSet error:(NSError**)pError;

    -(void)dealloc;

    /// \brief Retrieve the first DicomheroDicomDir's root entry.
    ///
    /// If the root entry is missing then return a null pointer.
    ///
    /// \param pError     set to a NSError derived class in case of error
    /// \return the root DicomheroDicomDirEntry or a null pointer if the root
    ///         DicomheroDicomDirEntry does noot exist
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(DicomheroDicomDirEntry*)getFirstRootEntry:(NSError**)pError;

    /// \brief Return a new DicomheroDicomDirEntry record for the DICOMDIR.
    ///
    /// \param recordType the type of the new entry
    /// \param pError     set to a NSError derived class in case of error
    /// \return a new DicomheroDicomDirEntry object that can be inserted into the
    ///         DicomheroDicomDir object or one of its children DicomheroDicomDirEntry
    ///         entries.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(DicomheroDicomDirEntry*)getNewEntry:(NSString*)recordType error:(NSError**)pError;

    /// \brief Set the specified entry as the first DicomheroDicomDir's root record.
    ///
    /// \param firstEntryRecord the DicomDirEntry object to set as the first root
    ///                         entry
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)setFirstRootEntry:(DicomheroDicomDirEntry*)firstEntryRecord error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief This method has to be called to update the managed DataSet after
    ///        the DicomheroDicomDir's content has been updated.
    ///
    /// It is not necessary to call updateDataSet() after every DicomheroDicomDir
    /// update, just call it when the updated DicomheroDataSet object is needed.
    ///
    /// \return the updated managed DicomheroDataSet object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(DicomheroDataSet*)updateDataSet:(NSError**)pError;

@end

#endif // dicomheroObjcDicomDir__INCLUDED_
