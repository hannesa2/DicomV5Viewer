/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcUidGeneratorFactory__INCLUDED_)
#define dicomheroObjcUidGeneratorFactory__INCLUDED_

#import <Foundation/Foundation.h>

@class DicomheroBaseUIDGenerator;

///
/// \brief DicomheroUIDGeneratorFactory manages a global collection of
///        DICOM UID generators.
///
/// In order to generate different UIDs, the UID generators maintain an
/// internal state that must be preserved between UID generations.
/// Ideally, UID generators should be allocated when the application starts
/// and should be reused every time a new UID is needed.
///
/// DicomheroUIDGeneratorFactory helps with the reuse of the allocated
/// generators.
///
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroUIDGeneratorFactory: NSObject


    /// \brief Register an UID generator.
    ///
    /// UID generators should be registered when the application starts.
    ///
    /// Registered UID generators can be retrieved using getUIDGenerator()
    /// or getDefaultUIDGenerator().
    ///
    /// \param name         the name under which the UID generator is registered
    /// \param pGGenerator  the UID generator to register
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(void)registerUIDGenerator:(NSString*)name generator:(DicomheroBaseUIDGenerator*)pGenerator error:(NSError**)pError;

    /// \brief Retrieved a registered UID generator.
    ///
    /// \throws DicomheroNonRegisteredUIDGenerator if the requested UID generator was
    ///         not register via registerUIDGenerator().
    ///
    /// \param name the name of the generator to retrieve
    /// \return the requested UID generator
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(DicomheroBaseUIDGenerator*)getUIDGenerator:(NSString*)name error:(NSError**)pError;

    /// \brief Retrieve the first UID generator registered in the factory.
    ///
    /// \throws DicomheroNonRegisteredUIDGenerator if no UID generator was not
    ///         register via registerUIDGenerator().
    ///
    /// \return the first registered UID generator
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(DicomheroBaseUIDGenerator*)getDefaultUIDGenerator:(NSError**)pError;

@end

#endif // dicomheroObjcUidGeneratorFactory__INCLUDED_


