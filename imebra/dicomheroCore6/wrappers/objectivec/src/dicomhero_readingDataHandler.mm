/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_readingDataHandler.h"
#import "../include/dicomhero6_objc/dicomhero_dateAge.h"
#import "../include/dicomhero6_objc/dicomhero_patientName.h"

#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"
#include "dicomhero_strings.h"

#include <dicomhero6/readingDataHandler.h>
#include <dicomhero6/date.h>
#include <dicomhero6/age.h>
#include <dicomhero6/patientName.h>

@implementation DicomheroReadingDataHandler

-(id)initWithDicomheroReadingDataHandler:define_dicomhero_parameter(ReadingDataHandler)
{
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(ReadingDataHandler, get_dicomhero_parameter(ReadingDataHandler));
    }
    else
    {
        delete get_dicomhero_parameter(ReadingDataHandler);
    }
    return self;

}

-(void)dealloc
{
    delete_dicomhero_object_holder(ReadingDataHandler);
}

-(unsigned int) size
{
    return (unsigned int)get_dicomhero_object_holder(ReadingDataHandler)->getSize();
}

-(signed long long) getInt64:(unsigned int)index error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(ReadingDataHandler)->getInt64(index);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(signed int) getInt32:(unsigned int)index error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(ReadingDataHandler)->getInt32(index);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(signed int) getSignedLong:(unsigned int)index error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(ReadingDataHandler)->getInt32(index);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(signed short) getInt16:(unsigned int)index error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(ReadingDataHandler)->getInt16(index);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(signed char) getInt8:(unsigned int)index error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(ReadingDataHandler)->getInt8(index);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned long long) getUint64:(unsigned int)index error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(ReadingDataHandler)->getUint64(index);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned int) getUint32:(unsigned int)index error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(ReadingDataHandler)->getUint32(index);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned int) getUnsignedLong:(unsigned int)index error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(ReadingDataHandler)->getUint32(index);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned short) getUint16:(unsigned int)index error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(ReadingDataHandler)->getUint16(index);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned char) getUint8:(unsigned int)index error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(ReadingDataHandler)->getUint8(index);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(double) getDouble:(unsigned int)index error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(ReadingDataHandler)->getDouble(index);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0.0f);
}

-(float) getFloat:(unsigned int)index error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(ReadingDataHandler)->getFloat(index);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0.0f);
}

-(NSString*) getString:(unsigned int)index error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return dicomhero::stringToNSString(get_dicomhero_object_holder(ReadingDataHandler)->getString(index));

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroDate*) getDate:(unsigned int)index error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    const dicomhero::Date date(get_dicomhero_object_holder(ReadingDataHandler)->getDate(index));
    return [[DicomheroDate alloc] initWithDicomheroDate: new dicomhero::Date(date)];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroAge*) getAge:(unsigned int)index error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    const dicomhero::Age age(get_dicomhero_object_holder(ReadingDataHandler)->getAge(index));
    return [[DicomheroAge alloc] initWithDicomheroAge: new dicomhero::Age(age)];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroPatientName*) getPatientName:(unsigned int)index error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    const dicomhero::PatientName patientName(get_dicomhero_object_holder(ReadingDataHandler)->getPatientName(index));
    return [[DicomheroPatientName alloc] initWithDicomheroPatientName: new dicomhero::PatientName(patientName)];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


@end


