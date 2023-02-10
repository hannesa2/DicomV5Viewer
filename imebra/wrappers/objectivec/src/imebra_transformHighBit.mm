/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "../include/imebraobjc/imebra_transformHighBit.h"

#include "imebra_implementation_macros.h"

#include <imebra/transformHighBit.h>
@implementation ImebraTransformHighBit

-(id)init
{
    reset_imebra_object_holder(Transform);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(Transform, new imebra::TransformHighBit());
    }
    return self;
}

@end


