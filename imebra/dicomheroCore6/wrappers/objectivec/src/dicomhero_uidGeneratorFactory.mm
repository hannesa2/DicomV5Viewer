/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_uidGeneratorFactory.h"
#import "../include/dicomhero6_objc/dicomhero_baseUidGenerator.h"
#include "dicomhero_implementation_macros.h"
#include "dicomhero_strings.h"
#include "dicomhero_nserror.h"
#include <dicomhero6/uidGeneratorFactory.h>
#include <dicomhero6/baseUidGenerator.h>

#import <Foundation/Foundation.h>

@implementation DicomheroUIDGeneratorFactory

+(void)registerUIDGenerator:(NSString*)name generator:(DicomheroBaseUIDGenerator*)pGenerator error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START()

    dicomhero::UIDGeneratorFactory::registerUIDGenerator(
                dicomhero::NSStringToString(name),
                *get_other_dicomhero_object_holder(pGenerator, BaseUIDGenerator));

    OBJC_DICOMHERO_FUNCTION_END()
}

+(DicomheroBaseUIDGenerator*)getUIDGenerator:(NSString*)name error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START()

    std::unique_ptr<dicomhero::BaseUIDGenerator> pGenerator(new dicomhero::BaseUIDGenerator(dicomhero::UIDGeneratorFactory::getUIDGenerator(dicomhero::NSStringToString(name))));
    return [[DicomheroBaseUIDGenerator alloc] initWithDicomheroBaseUidGenerator:pGenerator.release()];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

+(DicomheroBaseUIDGenerator*)getDefaultUIDGenerator:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START()

    std::unique_ptr<dicomhero::BaseUIDGenerator> pGenerator(new dicomhero::BaseUIDGenerator(dicomhero::UIDGeneratorFactory::getDefaultUIDGenerator()));
    return [[DicomheroBaseUIDGenerator alloc] initWithDicomheroBaseUidGenerator:pGenerator.release()];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

@end



