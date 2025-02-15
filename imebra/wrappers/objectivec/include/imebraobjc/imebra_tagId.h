/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcTagId__INCLUDED_)
#define imebraObjcTagId__INCLUDED_

#import <Foundation/Foundation.h>
#import "tagsEnumeration.h"
#include "imebra_macros.h"


///
/// \brief Represents a Dicom tag's identification.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraTagId: NSObject

{
    @public
    define_imebra_object_holder(TagId);
}

    -(id)init;

    /// \brief Initializer.
    ///
    /// \param groupId    the group id
    /// \param tagId      the tag id
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithGroup:(unsigned short)groupId tag:(unsigned short)tagId;

    /// \brief Initializer.
    ///
    /// \param id an enumeration representing a tag group and id
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithId:(ImebraTagEnum)tagId;

    /// \brief Initializer.
    ///
    /// \param groupId    the group id
    /// \param groupOrder old DICOM files may have several groups with the same id.
    ///                   This parameter specifies which of the groups with the
    ///                   same id must be taken into consideration
    /// \param tagId      the tag id
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithGroup:(unsigned short)groupId groupOrder:(unsigned int)groupOrder tag:(unsigned short)tagId;

    -(void)dealloc;

    /// \brief Retrieve the group id.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) unsigned short groupId;

    /// \brief Return the group order. Old DICOM files may have several groups
    ///        with the same id. This value specifies which of the groups with the
    ///        same id has been taken into consideration.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) unsigned int groupOrder;

    /// \brief Retrieve the tag id.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) unsigned short tagId;

@end


#endif // imebraObjcTagId__INCLUDED_
