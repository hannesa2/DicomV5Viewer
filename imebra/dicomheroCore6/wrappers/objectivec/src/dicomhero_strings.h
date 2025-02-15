/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcStrings__INCLUDED_)
#define dicomheroObjcStrings__INCLUDED_

#import <Foundation/Foundation.h>
#include <string>

namespace dicomhero
{

/**
 * @brief Convert an NSString to a std::string accepted by dicomhero.
 *
 * @param str an NSString
 * @return a UTF-8 encoded std::string
 */
std::string NSStringToString ( NSString* str );


/**
 * @brief Convert a UTF-8 encoded std::string to an NSString.
 *
 * @param str a UTF-8 encoded std::string
 * @return a NSString
 */
NSString* stringToNSString ( const std::string& str );


/**
 * @brief Convert a UTF-32 encoded std::wstring to an NSString.
 *
 * @param str a UTF-32 encoded std::wstring
 * @return a NSString
 */
NSString* stringToNSString ( const std::wstring& str );


} // namespace dicomhero

#endif // dicomheroObjcStrings__INCLUDED_
