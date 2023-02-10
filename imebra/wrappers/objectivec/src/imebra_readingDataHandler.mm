/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_readingDataHandler.h"
#import "../include/imebraobjc/imebra_dateAge.h"
#import "../include/imebraobjc/imebra_patientName.h"

#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"
#include "imebra_strings.h"

#include <imebra/readingDataHandler.h>
#include <imebra/date.h>
#include <imebra/age.h>
#include <imebra/patientName.h>

@implementation ImebraReadingDataHandler

-(id)initWithImebraReadingDataHandler:define_imebra_parameter(ReadingDataHandler)
{
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(ReadingDataHandler, get_imebra_parameter(ReadingDataHandler));
    }
    else
    {
        delete get_imebra_parameter(ReadingDataHandler);
    }
    return self;

}

-(void)dealloc
{
    delete_imebra_object_holder(ReadingDataHandler);
}

-(unsigned int) size
{
    return (unsigned int)get_imebra_object_holder(ReadingDataHandler)->getSize();
}

-(signed long long) getInt64:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(ReadingDataHandler)->getInt64(index);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(signed int) getInt32:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(ReadingDataHandler)->getInt32(index);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(signed int) getSignedLong:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(ReadingDataHandler)->getInt32(index);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(signed short) getInt16:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(ReadingDataHandler)->getInt16(index);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(signed char) getInt8:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(ReadingDataHandler)->getInt8(index);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned long long) getUint64:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(ReadingDataHandler)->getUint64(index);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned int) getUint32:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(ReadingDataHandler)->getUint32(index);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned int) getUnsignedLong:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(ReadingDataHandler)->getUint32(index);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned short) getUint16:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(ReadingDataHandler)->getUint16(index);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned char) getUint8:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(ReadingDataHandler)->getUint8(index);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(double) getDouble:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(ReadingDataHandler)->getDouble(index);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0.0f);
}

-(float) getFloat:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(ReadingDataHandler)->getFloat(index);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0.0f);
}

-(NSString*) getString:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return imebra::stringToNSString(get_imebra_object_holder(ReadingDataHandler)->getString(index));

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraDate*) getDate:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    const imebra::Date date(get_imebra_object_holder(ReadingDataHandler)->getDate(index));
    return [[ImebraDate alloc] initWithImebraDate: new imebra::Date(date)];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraAge*) getAge:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    const imebra::Age age(get_imebra_object_holder(ReadingDataHandler)->getAge(index));
    return [[ImebraAge alloc] initWithImebraAge: new imebra::Age(age)];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraPatientName*) getPatientName:(unsigned int)index error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    const imebra::PatientName patientName(get_imebra_object_holder(ReadingDataHandler)->getPatientName(index));
    return [[ImebraPatientName alloc] initWithImebraPatientName: new imebra::PatientName(patientName)];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}


@end


