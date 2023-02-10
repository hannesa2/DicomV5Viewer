/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import <Foundation/NSString.h>
#import "../include/imebraobjc/imebra_patientName.h"
#include "imebra_strings.h"
#include "imebra_implementation_macros.h"

#include <imebra/patientName.h>

@implementation ImebraPatientName

-(void)dealloc
{
    delete_imebra_object_holder(PatientName);
}

-(id)initWithImebraPatientName:define_imebra_parameter(PatientName)
{
    reset_imebra_object_holder(PatientName);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(PatientName, get_imebra_parameter(PatientName));
    }
    else
    {
        delete get_imebra_parameter(PatientName);
    }
    return self;
}

-(id)initWithAlphabeticRepresentation:(NSString*)alphabeticRepresentation
                    ideographicRepresentation:(NSString*)ideographicRepresentation
                    phoneticRepresentation:(NSString*)phoneticRepresentation
{
    reset_imebra_object_holder(PatientName);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(PatientName, new imebra::PatientName(
                                 imebra::NSStringToString(alphabeticRepresentation),
                                 imebra::NSStringToString(ideographicRepresentation),
                                 imebra::NSStringToString(phoneticRepresentation)));
    }
    return self;
}

-(NSString*)alphabeticRepresentation
{
    return imebra::stringToNSString(get_imebra_object_holder(PatientName)->getAlphabeticRepresentation());
}

-(NSString*)ideographicRepresentation
{
    return imebra::stringToNSString(get_imebra_object_holder(PatientName)->getIdeographicRepresentation());
}

-(NSString*)phoneticcRepresentation
{
    return imebra::stringToNSString(get_imebra_object_holder(PatientName)->getPhoneticRepresentation());
}

@end

