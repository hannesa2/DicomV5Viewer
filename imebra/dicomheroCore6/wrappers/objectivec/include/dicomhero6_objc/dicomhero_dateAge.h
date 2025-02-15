/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcDateAge__INCLUDED_)
#define dicomheroObjcDateAge__INCLUDED_

#import <Foundation/Foundation.h>
#include "dicomhero_macros.h"

/// \enum DicomheroAgeUnit
/// \brief Used by DicomheroAge::setAge() and DicomheroAge::getAge() to specify the
///        unit of the age value.
///
///////////////////////////////////////////////////////////////////////////////
typedef NS_ENUM(char, DicomheroAgeUnit)
{
    DicomheroAgeUnitDays = (char)'D',   ///< Days
    DicomheroAgeUnitWeeks = (char)'W',  ///< Weeks
    DicomheroAgeUnitMonths = (char)'M', ///< Months
    DicomheroAgeUnitYears = (char)'Y'   ///< Years
};

///
/// \brief Specifies an age, in days, weeks, months or years.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroAge: NSObject

{
    @public
    define_dicomhero_object_holder(Age);
}

    -(id)initWithDicomheroAge:define_dicomhero_parameter(Age);

    -(void)dealloc;


    /// \brief Constructor.
    ///
    /// \param initialAge the initial age to assign to the object, in days, weeks,
    ///                   months or years, depending on the parameter initialUnits
    /// \param initialUnits the units of the value in initialAge
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithAge:(unsigned int)initialAge units:(DicomheroAgeUnit)initialUnits;

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
    @property (readonly) DicomheroAgeUnit units;

@end


@interface DicomheroDate: NSObject

{
    @public
    define_dicomhero_object_holder(Date);
}

    -(void)dealloc;

    -(id)initWithDicomheroDate:define_dicomhero_parameter(Date);

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

#endif // dicomheroObjcDateAge__INCLUDED_
