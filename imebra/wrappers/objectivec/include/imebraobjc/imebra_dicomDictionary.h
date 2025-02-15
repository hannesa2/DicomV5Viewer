/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcDicomDictionary__INCLUDED_)
#define imebraObjcDicomDictionary__INCLUDED_

#import <Foundation/Foundation.h>

#import "imebra_dataset.h"

@class ImebraTagId;

///
/// \brief Provides information about the tag's description and their default
///        data type (VR).
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraDicomDictionary: NSObject

    /// \brief Retrieve a tag's description.
    ///
    /// @param tagId     the tag's id
    /// @param pError    set to NSError derived class in case of error
    /// @return          the tag's description
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(NSString*)getTagDescription:(ImebraTagId*)tagId error:(NSError**)pError;

    /// \brief Retrieve a tag's minimum multiplicity value (the minimum number of
    ///        values that should be stored in the tag).
    ///
    /// @param tagId     the tag's id
    /// @param pError    set to NSError derived class in case of error
    /// @return          the minimum multiplicity value
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(unsigned int)getMultiplicityMin:(ImebraTagId*)tagId error:(NSError**)pError;

    /// \brief Retrieve a tag's maximum multiplicity value (the maximum number of
    ///        values that should be stored in the tag, 0=unlimited).
    ///
    /// @param tagId     the tag's id
    /// @param pError    set to NSError derived class in case of error
    /// @return          the maximum multiplicity value (0=unlimited)
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(unsigned int)getMultiplicityMax:(ImebraTagId*)tagId error:(NSError**)pError;

    /// \brief Retrieve a tag's step multiplicity value.
    ///
    /// @param tagId     the tag's id
    /// @param pError    set to NSError derived class in case of error
    /// @return          the step multiplicity value
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(unsigned int)getMultiplicityStep:(ImebraTagId*)tagId error:(NSError**)pError;

    /// \brief Retrieve a tag's default data type.
    ///
    /// @param tagId        the tag's id
    /// @param pError    set to NSError derived class in case of error
    /// @return          The tag's data type
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(ImebraTagType)getTagType:(ImebraTagId*)tagId error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    /// \brief Return the size (in bytes) of the data type's elements
    ///
    /// @param dataType the data type for which the information is required
    /// @return the size of a single element, in bytes. 0 means that there isn't
    ///         a fixed size for the element
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(unsigned int)getWordSize:(ImebraTagType)dataType;

    /// \brief Return the maximum size of the tags with the specified data type.
    ///
    /// @param dataType the data type for which the information is required
    /// @return         the maximum tag's size in bytes
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(unsigned int)getMaxSize:(ImebraTagType)dataType;

@end

#endif // imebraObjcDicomDictionary__INCLUDED_
