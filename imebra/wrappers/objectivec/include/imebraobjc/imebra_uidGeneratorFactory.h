/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcUidGeneratorFactory__INCLUDED_)
#define imebraObjcUidGeneratorFactory__INCLUDED_

#import <Foundation/Foundation.h>

@class ImebraBaseUIDGenerator;

///
/// \brief ImebraUIDGeneratorFactory manages a global collection of
///        DICOM UID generators.
///
/// In order to generate different UIDs, the UID generators maintain an
/// internal state that must be preserved between UID generations.
/// Ideally, UID generators should be allocated when the application starts
/// and should be reused every time a new UID is needed.
///
/// ImebraUIDGeneratorFactory helps with the reuse of the allocated
/// generators.
///
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraUIDGeneratorFactory: NSObject


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
    +(void)registerUIDGenerator:(NSString*)name generator:(ImebraBaseUIDGenerator*)pGenerator error:(NSError**)pError;

    /// \brief Retrieved a registered UID generator.
    ///
    /// \throws ImebraNonRegisteredUIDGenerator if the requested UID generator was
    ///         not register via registerUIDGenerator().
    ///
    /// \param name the name of the generator to retrieve
    /// \return the requested UID generator
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(ImebraBaseUIDGenerator*)getUIDGenerator:(NSString*)name error:(NSError**)pError;

    /// \brief Retrieve the first UID generator registered in the factory.
    ///
    /// \throws ImebraNonRegisteredUIDGenerator if no UID generator was not
    ///         register via registerUIDGenerator().
    ///
    /// \return the first registered UID generator
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(ImebraBaseUIDGenerator*)getDefaultUIDGenerator:(NSError**)pError;

@end

#endif // imebraObjcUidGeneratorFactory__INCLUDED_


