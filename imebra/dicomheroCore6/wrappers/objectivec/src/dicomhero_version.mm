/*
Copyright 2005 - 2022 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import <Foundation/Foundation.h>
#import "../include/dicomhero6_objc/dicomhero_version.h"
#include <dicomhero6/getVersion.h>
#include "dicomhero_strings.h"

@implementation DicomheroVersion

+(NSString*) DicomheroGetVersion
{
    return dicomhero::stringToNSString(dicomhero::Version::getVersion());
}

@end



