/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcDateAge__INCLUDED_)
#define imebraObjcDateAge__INCLUDED_

#import <Foundation/Foundation.h>
#include "imebra_macros.h"

/// \enum ImebraAgeUnit
/// \brief Used by ImebraAge::setAge() and ImebraAge::getAge() to specify the
///        unit of the age value.
///
///////////////////////////////////////////////////////////////////////////////
typedef NS_ENUM(char, ImebraAgeUnit)
{
    ImebraAgeUnitDays = (char)'D',   ///< Days
    ImebraAgeUnitWeeks = (char)'W',  ///< Weeks
    ImebraAgeUnitMonths = (char)'M', ///< Months
    ImebraAgeUnitYears = (char)'Y'   ///< Years
};

///
/// \brief Specifies an age, in days, weeks, months or years.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraAge: NSObject

{
    @public
    define_imebra_object_holder(Age);
}

    -(id)initWithImebraAge:define_imebra_parameter(Age);

    -(void)dealloc;


    /// \brief Constructor.
    ///
    /// \param initialAge the initial age to assign to the object, in days, weeks,
    ///                   months or years, depending on the parameter initialUnits
    /// \param initialUnits the units of the value in initialAge
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithAge:(unsigned int)initialAge units:(ImebraAgeUnit)initialUnits;

    /// \brief Return the age in years.
    ///
    /// \return the stored age converted to years.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) double years;

    /// \brief Return the age in the units returned by the property units.
    ///
    /// \return the stored age, speficied using the stored units.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) unsigned int age;

    /// \brief Return the age's units.
    ///
    /// \return the age's units
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) ImebraAgeUnit units;

@end


@interface ImebraDate: NSObject

{
    @public
    define_imebra_object_holder(Date);
}

    -(void)dealloc;

    -(id)initWithImebraDate:define_imebra_parameter(Date);

    /// \brief Constructor.
    ///
    /// Initialize the Date structure with the specified values.
    ///
    /// \param initialYear    year (0 = unused)
    /// \param initialMonth   month (1...12, 0 = unused)
    /// \param initialDay     day of the month (1...31, 0 = unused)
    /// \param initialHour    hour (0...23)
    /// \param initialMinutes minutes (0...59)
    /// \param initialSeconds seconds (0...59)
    /// \param initialNanoseconds nanoseconds
    /// \param initialOffsetHours   hours offset from UTC
    /// \param initialOffsetMinutes minutes offset from UTC
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithYear:(unsigned int)initialYear
                                    month:(unsigned int)initialMonth
                                    day:(unsigned int)initialDay
                                    hour:(unsigned int)initialHour
                                    minutes:(unsigned int)initialMinutes
                                    seconds:(unsigned int)initialSeconds
                                    nanoseconds:(unsigned int)initialNanoseconds
                                    offsetHours:(int)initialOffsetHours
                                    offsetMinutes:(int)initialOffsetMinutes;

    @property (readonly) unsigned int year;         ///< Year (0 = unused)
    @property (readonly) unsigned int month;        ///< Month (1...12, 0 = unused)
    @property (readonly) unsigned int day;          ///< Day (1...12, 0 = unused)
    @property (readonly) unsigned int hour;         ///< Hours
    @property (readonly) unsigned int minutes;      ///< Minutes
    @property (readonly) unsigned int seconds;      ///< Seconds
    @property (readonly) unsigned int nanoseconds;  ///< Nanoseconds
    @property (readonly) int offsetHours;           ///< Offset hours from UTC
    @property (readonly) int offsetMinutes;         ///< Offset minutes from UTC

@end

#endif // imebraObjcDateAge__INCLUDED_
