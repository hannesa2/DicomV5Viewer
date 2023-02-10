/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcDicomDir__INCLUDED_)
#define imebraObjcDicomDir__INCLUDED_

#import <Foundation/Foundation.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSString.h>
#include "imebra_macros.h"

@class ImebraDataSet;
@class ImebraMutableDataSet;


///
/// \brief Represents a single DICOMDIR entry.
///
/// Each entry can be followed by a sibling entry (on the same depth level)
/// and/or can point to its first child entry (one level deeper).
///
/// Each ImebraDicomDirEntry object manages a ImebraDataSet which is used to
/// store the entry's data. The ImebraDataSet objects managed by
/// ImebraDicomDirEntry objects are inserted as sequence items into the
/// ImebraDicomDir's dataSet.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraDicomDirEntry: NSObject

{
    @public
    define_imebra_object_holder(DicomDirEntry);
}

    -(id)initWithImebraDicomDirEntry:define_imebra_parameter(DicomDirEntry);

    -(void)dealloc;

    /// \brief Return the ImebraDataSet managed by the ImebraDicomDirEntry object.
    ///
    /// \return the ImebraDataSet managed by the ImebraDicomDirEntry object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraDataSet*)getEntryDataSet;

    /// \brief Return the next sibling entry (on the same depth level).
    ///
    /// If the next ImebraDicomDirEntry is missing (this is the last entry) then
    /// return a null pointer.
    ///
    /// \return the next sibling ImebraDicomDirEntry object, or a null pointer if
    ///         the next sibling does not exist
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraDicomDirEntry*)getNextEntry;

    /// \brief Return the first child entry (one level deeper).
    ///
    /// If the first child ImebraDicomDirEntry is missing then return a null
    /// pointer.
    ///
    /// \return the first child ImebraDicomDirEntry object, or a null pointer if
    ///         there aren't any children
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraDicomDirEntry*)getFirstChildEntry;

    /// \brief Returns the parts that form the name of the file referenced by the
    ///        ImebraDicomDirEntry object.
    ///
    /// \return a NSArray of NSString objects that form the name of the file
    ///         referenced by the ImebraDicomDirEntry object. The last item in the
    ///         array is the file name, while the preceding items contain the
    ///         folders names.
    ///         For instance, the parts "folder0", "folder1", "fileName"
    ///         represent the path "folder0/folder1/fileName"
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(NSArray*)getFileParts:(NSError**)pError;

    -(NSString*)getTypeString:(NSError**)pError;

@end


///
/// \brief Represents a single DICOMDIR entry.
///
/// Each entry can be followed by a sibling entry (on the same depth level)
/// and/or can point to its first child entry (one level deeper).
///
/// Each ImebraDicomDirEntry object manages a ImebraDataSet which is used to
/// store the entry's data. The ImebraDataSet objects managed by
/// ImebraDicomDirEntry objects are inserted as sequence items into the
/// ImebraDicomDir's dataSet.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraMutableDicomDirEntry: ImebraDicomDirEntry

   /// \brief Return the ImebraMutableDataSet managed by the
   ///        ImebraMutableDicomDirEntry object.
   ///
   /// \return the ImebraMutableDataSet managed by the
   ///         ImebraMutableDicomDirEntry object
   ///
   ///////////////////////////////////////////////////////////////////////////////
   -(ImebraMutableDataSet*)getEntryDataSet;

/// \brief Set the next sibling entry (one the same depth level).
    ///
    /// \param nextEntry the next sibling ImebraDicomDirEntry object
    /// \param pError    set to a NSError derived class in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)setNextEntry:(ImebraDicomDirEntry*)pNextEntry error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Set the first child entry (one level deeper).
    ///
    /// \param firstChildEntry the first child ImebraDicomDirEntry object
    /// \param pError          set to a NSError derived class in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)setFirstChildEntry:(ImebraDicomDirEntry*)pFirstChildEntry error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Set the parts that form the name of the file referenced by the
    ///        DicomDirEntry object.
    ///
    /// \param fileParts  a NSArray of NSString objects that form the name of the
    ///                   file referenced by the ImebraDicomDirEntry object.
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
/// In order to work ImebraDicomDir needs a ImebraDataSet, which embeds
/// the DICOMDIR's entries.
///
/// If the ImebraDicomDir's content is modified then the method updateDataSet()
/// has to be called to obtain a dataset that can be stored as a DICOMDIR
/// file.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraDicomDir: NSObject

{
    @public
    define_imebra_object_holder(DicomDir);
}

    -(id)initWithImebraDicomDir:define_imebra_parameter(DicomDir);

    /// \brief Construct an ImebraDicomDir from an ImebraDataSet object.
    ///
    /// \param pDataSet the ImebraDataSet created from reading a DICOMDIR file
    /// \param pError   set to an NSError derived class in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithDataSet:(ImebraDataSet*)pDataSet error:(NSError**)pError;

    -(void)dealloc;

    /// \brief Retrieve the first ImebraDicomDir's root entry.
    ///
    /// If the root entry is missing then return a null pointer.
    ///
    /// \param pError     set to a NSError derived class in case of error
    /// \return the root ImebraDicomDirEntry or a null pointer if the root
    ///         ImebraDicomDirEntry does noot exist
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraDicomDirEntry*)getFirstRootEntry:(NSError**)pError;

@end


///
/// \brief Represents a DICOMDIR structure.
///
/// In order to work ImebraDicomDir needs a ImebraDataSet, which embeds
/// the DICOMDIR's entries.
///
/// If the ImebraDicomDir's content is modified then the method updateDataSet()
/// has to be called to obtain a dataset that can be stored as a DICOMDIR
/// file.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraMutableDicomDir: ImebraDicomDir

    /// \brief Construct an empty DicomDir.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)init;

    /// \brief Return a new ImebraDicomDirEntry record for the DICOMDIR.
    ///
    /// \param recordType the type of the new entry
    /// \param pError     set to a NSError derived class in case of error
    /// \return a new ImebraDicomDirEntry object that can be inserted into the
    ///         ImebraDicomDir object or one of its children ImebraDicomDirEntry
    ///         entries.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraMutableDicomDirEntry*)getNewEntry:(NSString*)recordType error:(NSError**)pError;

    /// \brief Set the specified entry as the first ImebraDicomDir's root record.
    ///
    /// \param firstEntryRecord the DicomDirEntry object to set as the first root
    ///                         entry
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)setFirstRootEntry:(ImebraDicomDirEntry*)firstEntryRecord error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief This method has to be called to update the managed DataSet after
    ///        the ImebraDicomDir's content has been updated.
    ///
    /// It is not necessary to call updateDataSet() after every ImebraDicomDir
    /// update, just call it when the updated ImebraDataSet object is needed.
    ///
    /// \return the updated managed ImebraDataSet object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraDataSet*)updateDataSet:(NSError**)pError;

@end

#endif // imebraObjcDicomDir__INCLUDED_
