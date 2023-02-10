/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_uidGeneratorFactory.h"
#import "../include/imebraobjc/imebra_baseUidGenerator.h"
#include "imebra_implementation_macros.h"
#include "imebra_strings.h"
#include "imebra_nserror.h"
#include <imebra/uidGeneratorFactory.h>
#include <imebra/baseUidGenerator.h>

#import <Foundation/Foundation.h>

@implementation ImebraUIDGeneratorFactory

+(void)registerUIDGenerator:(NSString*)name generator:(ImebraBaseUIDGenerator*)pGenerator error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START()

    imebra::UIDGeneratorFactory::registerUIDGenerator(
                imebra::NSStringToString(name),
                *get_other_imebra_object_holder(pGenerator, BaseUIDGenerator));

    OBJC_IMEBRA_FUNCTION_END()
}

+(ImebraBaseUIDGenerator*)getUIDGenerator:(NSString*)name error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START()

    std::unique_ptr<imebra::BaseUIDGenerator> pGenerator(new imebra::BaseUIDGenerator(imebra::UIDGeneratorFactory::getUIDGenerator(imebra::NSStringToString(name))));
    return [[ImebraBaseUIDGenerator alloc] initWithImebraBaseUidGenerator:pGenerator.release()];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

+(ImebraBaseUIDGenerator*)getDefaultUIDGenerator:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START()

    std::unique_ptr<imebra::BaseUIDGenerator> pGenerator(new imebra::BaseUIDGenerator(imebra::UIDGeneratorFactory::getDefaultUIDGenerator()));
    return [[ImebraBaseUIDGenerator alloc] initWithImebraBaseUidGenerator:pGenerator.release()];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

@end



