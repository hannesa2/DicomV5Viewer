/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcSerialNumberUidGenerator__INCLUDED_)
#define imebraObjcSerialNumberUidGenerator__INCLUDED_

#import <Foundation/Foundation.h>
#import "imebra_baseUidGenerator.h"
#include "imebra_macros.h"

///
/// \brief An UID generator that uses the model serial number to create unique
///        UIDs.
///
/// The uniqueness of the generated UIDs is guaranteed by the fact that
/// the machine serial number is correctly set.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraSerialNumberUIDGenerator: ImebraBaseUIDGenerator

    /// \brief Constructor.
    ///
    /// \param root the     root UID assigned to the company
    /// \param departmentId department ID (assigned by the company)
    /// \param modelId      model ID (assigned by the department)
    /// \param serialNumber the model serial number (assigned by the department)
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithRoot:(NSString*)root departmentId:(unsigned int)departmentId modelId:(unsigned int)modelId serialNumber:(unsigned int)serialNumber;

@end

#endif // imebraObjcSerialNumberUidGenerator__INCLUDED_
