/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_tagId.h"

#include "imebra_implementation_macros.h"

#include <imebra/tagId.h>

///
/// \brief Specifies an age, in days, weeks, months or years.
///
///////////////////////////////////////////////////////////////////////////////
@implementation ImebraTagId

-(id)init
{
    reset_imebra_object_holder(TagId);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(TagId, new imebra::TagId());
    }
    return self;
}


-(id)initWithId:(ImebraTagEnum)tagId
{
    reset_imebra_object_holder(TagId);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(TagId, new imebra::TagId((imebra::tagId_t)tagId));
    }
    return self;
}


-(id)initWithGroup:(unsigned short)groupId tag:(unsigned short)tagId
{
    reset_imebra_object_holder(TagId);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(TagId, new imebra::TagId(groupId, tagId));
    }
    return self;

}

-(id)initWithGroup:(unsigned short)groupId groupOrder:(unsigned int)groupOrder tag:(unsigned short)tagId
{
    reset_imebra_object_holder(TagId);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(TagId, new imebra::TagId(groupId, groupOrder, tagId));
    }
    return self;

}

-(void)dealloc
{
    delete_imebra_object_holder(TagId);
}

-(unsigned short) groupId
{
    return get_imebra_object_holder(TagId)->getGroupId();
}

-(unsigned int) groupOrder
{
    return get_imebra_object_holder(TagId)->getGroupOrder();
}

-(unsigned short) tagId
{
    return get_imebra_object_holder(TagId)->getTagId();
}

@end

