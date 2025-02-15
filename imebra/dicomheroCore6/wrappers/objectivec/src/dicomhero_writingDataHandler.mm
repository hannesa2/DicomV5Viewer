/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_writingDataHandler.h"
#import "../include/dicomhero6_objc/dicomhero_dateAge.h"
#import "../include/dicomhero6_objc/dicomhero_patientName.h"

#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"
#include "dicomhero_strings.h"

#include <dicomhero6/writingDataHandler.h>

@implementation DicomheroWritingDataHandler

-(id)initWithDicomheroWritingDataHandler:define_dicomhero_parameter(WritingDataHandler)
{
    reset_dicomhero_object_holder(WritingDataHandler);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(WritingDataHandler, get_dicomhero_parameter(WritingDataHandler));
    }
    else
    {
        delete get_dicomhero_parameter(WritingDataHandler);
    }
    return self;
}

-(void)dealloc
{
    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        delete_dicomhero_object_holder(WritingDataHandler);
    }
}

-(unsigned int)size
{
    return (unsigned int)get_dicomhero_object_holder(WritingDataHandler)->getSize();
}

-(void)setSize:(unsigned int)size
{
    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        get_dicomhero_object_holder(WritingDataHandler)->setSize(size);
    }
}

-(void) setInt64:(unsigned int)index newValue:(signed long long)value error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
      get_dicomhero_object_holder(WritingDataHandler)->setInt64(index, value);
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) setInt32:(unsigned int)index newValue:(signed int)value error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        get_dicomhero_object_holder(WritingDataHandler)->setInt32(index, value);
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) setSignedLong:(unsigned int)index newValue:(signed int)value error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        get_dicomhero_object_holder(WritingDataHandler)->setInt32(index, value);
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) setInt16:(unsigned int)index newValue:(signed short)value error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        get_dicomhero_object_holder(WritingDataHandler)->setInt16(index, value);
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) setInt8:(unsigned int)index newValue:(signed char)value error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        get_dicomhero_object_holder(WritingDataHandler)->setInt8(index, value);
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) setUint64:(unsigned int)index newValue:(unsigned long long)value error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        get_dicomhero_object_holder(WritingDataHandler)->setUint64(index, value);
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) setUint32:(unsigned int)index newValue:(unsigned int)value error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        get_dicomhero_object_holder(WritingDataHandler)->setUint32(index, value);
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) setUnsignedLong:(unsigned int)index newValue:(unsigned int)value error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        get_dicomhero_object_holder(WritingDataHandler)->setUint32(index, value);
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) setUint16:(unsigned int)index newValue:(unsigned short)value error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        get_dicomhero_object_holder(WritingDataHandler)->setUint16(index, value);
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) setUint8:(unsigned int)index newValue:(unsigned char)value error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        get_dicomhero_object_holder(WritingDataHandler)->setUint8(index, value);
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) setDouble:(unsigned int)index newValue:(double)value error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        get_dicomhero_object_holder(WritingDataHandler)->setDouble(index, value);
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) setFloat:(unsigned int)index newValue:(float)value error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        get_dicomhero_object_holder(WritingDataHandler)->setFloat(index, value);
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) setString:(unsigned int)index newValue:(NSString*)value error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        get_dicomhero_object_holder(WritingDataHandler)->setString(index, dicomhero::NSStringToString(value));
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) setDate:(unsigned int)index newValue:(DicomheroDate*)value error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        get_dicomhero_object_holder(WritingDataHandler)->setDate(index, *get_other_dicomhero_object_holder(value, Date));
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) setAge:(unsigned int)index newValue:(DicomheroAge*)value error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        get_dicomhero_object_holder(WritingDataHandler)->setAge(index, *get_other_dicomhero_object_holder(value, Age));
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) setPatientName:(unsigned int)index newValue:(DicomheroPatientName*)value error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        get_dicomhero_object_holder(WritingDataHandler)->setPatientName(index, *get_other_dicomhero_object_holder(value, PatientName));
    }

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) commit
{
    if(get_dicomhero_object_holder(WritingDataHandler) != nullptr)
    {
        delete_dicomhero_object_holder(WritingDataHandler);
        set_dicomhero_object_holder(WritingDataHandler, nullptr);
    }
}

@end

