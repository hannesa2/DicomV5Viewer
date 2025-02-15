/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_tagId.h"

#include "dicomhero_implementation_macros.h"

#include <dicomhero6/tagId.h>

///
/// \brief Specifies an age, in days, weeks, months or years.
///
///////////////////////////////////////////////////////////////////////////////
@implementation DicomheroTagId

-(id)init
{
    reset_dicomhero_object_holder(TagId);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(TagId, new dicomhero::TagId());
    }
    return self;
}


-(id)initWithId:(DicomheroTagEnum)tagId
{
    reset_dicomhero_object_holder(TagId);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(TagId, new dicomhero::TagId((dicomhero::tagId_t)tagId));
    }
    return self;
}


-(id)initWithGroup:(unsigned short)groupId tag:(unsigned short)tagId
{
    reset_dicomhero_object_holder(TagId);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(TagId, new dicomhero::TagId(groupId, tagId));
    }
    return self;

}

-(id)initWithGroup:(unsigned short)groupId groupOrder:(unsigned int)groupOrder tag:(unsigned short)tagId
{
    reset_dicomhero_object_holder(TagId);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(TagId, new dicomhero::TagId(groupId, groupOrder, tagId));
    }
    return self;

}

-(void)dealloc
{
    delete_dicomhero_object_holder(TagId);
}

-(unsigned short) groupId
{
    return get_dicomhero_object_holder(TagId)->getGroupId();
}

-(unsigned int) groupOrder
{
    return get_dicomhero_object_holder(TagId)->getGroupOrder();
}

-(unsigned short) tagId
{
    return get_dicomhero_object_holder(TagId)->getTagId();
}

@end

