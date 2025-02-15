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
#import "../include/dicomhero6_objc/dicomhero_patientName.h"
#include "dicomhero_strings.h"
#include "dicomhero_implementation_macros.h"

#include <dicomhero6/patientName.h>

@implementation DicomheroPatientName

-(void)dealloc
{
    delete_dicomhero_object_holder(PatientName);
}

-(id)initWithDicomheroPatientName:define_dicomhero_parameter(PatientName)
{
    reset_dicomhero_object_holder(PatientName);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(PatientName, get_dicomhero_parameter(PatientName));
    }
    else
    {
        delete get_dicomhero_parameter(PatientName);
    }
    return self;
}

-(id)initWithAlphabeticRepresentation:(NSString*)alphabeticRepresentation
                    ideographicRepresentation:(NSString*)ideographicRepresentation
                    phoneticRepresentation:(NSString*)phoneticRepresentation
{
    reset_dicomhero_object_holder(PatientName);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(PatientName, new dicomhero::PatientName(
                                 dicomhero::NSStringToString(alphabeticRepresentation),
                                 dicomhero::NSStringToString(ideographicRepresentation),
                                 dicomhero::NSStringToString(phoneticRepresentation)));
    }
    return self;
}

-(NSString*)alphabeticRepresentation
{
    return dicomhero::stringToNSString(get_dicomhero_object_holder(PatientName)->getAlphabeticRepresentation());
}

-(NSString*)ideographicRepresentation
{
    return dicomhero::stringToNSString(get_dicomhero_object_holder(PatientName)->getIdeographicRepresentation());
}

-(NSString*)phoneticRepresentation
{
    return dicomhero::stringToNSString(get_dicomhero_object_holder(PatientName)->getPhoneticRepresentation());
}

@end

