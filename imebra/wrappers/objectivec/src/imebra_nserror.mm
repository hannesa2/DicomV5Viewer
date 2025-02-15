/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "imebra_nserror.h"
#include "imebra_strings.h"

#include <imebra/exceptions.h>

namespace imebra
{

void setNSError(const std::runtime_error& error, NSError** pError, Class errorClass)
{
    if(pError)
    {
        std::string stackTrace(imebra::ExceptionsManager::getExceptionTrace());
        int errorCode(0);
        try
        {
            throw error;
        }
        catch(const std::runtime_error& )
        {
            errorCode = 1;
        }
        NSMutableDictionary* details = [NSMutableDictionary dictionary];
        [details setValue:imebra::stringToNSString(stackTrace) forKey:NSUnderlyingErrorKey];
        *pError = [errorClass errorWithDomain:@"imebra" code:errorCode userInfo: details];
    }
}

} // namespace imebra
