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
#import "../include/imebraobjc/imebra_dateAge.h"
#include "imebra_implementation_macros.h"
#include <imebra/age.h>
#include <imebra/date.h>

@implementation ImebraAge

-(void)dealloc
{
    delete_imebra_object_holder(Age);
}

-(id)initWithImebraAge:define_imebra_parameter(Age)
{
    reset_imebra_object_holder(Age);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(Age, get_imebra_parameter(Age));
    }
    else
    {
        delete get_imebra_parameter(Age);
    }
    return self;
}

-(id)initWithAge:(unsigned int)initialAge units:(ImebraAgeUnit)initialUnits
{
    reset_imebra_object_holder(Age);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(Age, new imebra::Age(initialAge, (imebra::ageUnit_t)initialUnits));
    }
    return self;
}

-(double)years
{
    return get_imebra_object_holder(Age)->getYears();
}

-(unsigned int)age
{
    return get_imebra_object_holder(Age)->getAgeValue();
}

-(ImebraAgeUnit)units
{
    return (ImebraAgeUnit)(get_imebra_object_holder(Age)->getAgeUnits());
}

@end


@implementation ImebraDate

-(void)dealloc
{
    delete_imebra_object_holder(Date);
}

-(id)initWithImebraDate:define_imebra_parameter(Date)
{
    reset_imebra_object_holder(Date);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(Date, get_imebra_parameter(Date));
    }
    else
    {
        delete get_imebra_parameter(Date);
    }
    return self;
}

-(id)initWithYear:(unsigned int)initialYear
                                month:(unsigned int)initialMonth
                                day:(unsigned int)initialDay
                                hour:(unsigned int)initialHour
                                minutes:(unsigned int)initialMinutes
                                seconds:(unsigned int)initialSeconds
                                nanoseconds:(unsigned int)initialNanoseconds
                                offsetHours:(int)initialOffsetHours
                                offsetMinutes:(int)initialOffsetMinutes
{
    reset_imebra_object_holder(Date);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(Date,
                                 new imebra::Date(
                                     initialYear,
                                     initialMonth,
                                     initialDay,
                                     initialHour,
                                     initialMinutes,
                                     initialSeconds,
                                     initialNanoseconds,
                                     initialOffsetHours,
                                     initialOffsetMinutes));
    }
    return self;
}

-(unsigned int)year
{
    return get_imebra_object_holder(Date)->getYear();
}

-(unsigned int)month
{
    return get_imebra_object_holder(Date)->getMonth();
}

-(unsigned int)day
{
    return get_imebra_object_holder(Date)->getDay();
}

-(unsigned int)hour
{
    return get_imebra_object_holder(Date)->getHour();
}

-(unsigned int)minutes
{
    return get_imebra_object_holder(Date)->getMinutes();
}

-(unsigned int)seconds
{
    return get_imebra_object_holder(Date)->getSeconds();
}

-(unsigned int)nanoseconds
{
    return get_imebra_object_holder(Date)->getNanoseconds();
}

-(int)offsetHours
{
    return get_imebra_object_holder(Date)->getOffsetHours();
}

-(int)offsetMinutes
{
    return get_imebra_object_holder(Date)->getOffsetMinutes();
}

@end
