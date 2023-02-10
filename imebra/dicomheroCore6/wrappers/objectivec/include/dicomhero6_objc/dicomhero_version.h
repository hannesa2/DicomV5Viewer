/*
Copyright 2005 - 2022 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroVersion__INCLUDED_)
#define dicomheroVersion__INCLUDED_

#import <Foundation/Foundation.h>

///
/// \brief Return information about the library's version.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroVersion: NSObject

    +(NSString*) DicomheroGetVersion;

@end

#endif // dicomheroVersion__INCLUDED_
