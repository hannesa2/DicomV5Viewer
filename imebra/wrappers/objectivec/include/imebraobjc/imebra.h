/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#ifndef __APPLE__
#ifndef NS_ENUM
#define NS_ENUM(_type, _name) enum _name : _type
#endif
#endif

#if !__has_feature(objc_arc)
    static_assert(false, "The library can be compiled only with ARC enabled");
#endif

#import "imebra_acse.h"
#import "imebra_baseStreamInput.h"
#import "imebra_baseStreamOutput.h"
#import "imebra_colorTransformsFactory.h"
#import "imebra_codecFactory.h"
#import "imebra_dataset.h"
#import "imebra_dateAge.h"
#import "imebra_dicomDictionary.h"
#import "imebra_dicomDir.h"
#import "imebra_dimse.h"
#import "imebra_drawBitmap.h"
#import "imebra_exceptions.h"
#import "imebra_fileStreamInput.h"
#import "imebra_fileStreamOutput.h"
#import "imebra_image.h"
#import "imebra_lut.h"
#import "imebra_memoryPool.h"
#import "imebra_memoryStreamInput.h"
#import "imebra_memoryStreamOutput.h"
#import "imebra_modalityVOILUT.h"
#import "imebra_overlay.h"
#import "imebra_pipe.h"
#import "imebra_readingDataHandler.h"
#import "imebra_readingDataHandlerNumeric.h"
#import "imebra_readMemory.h"
#import "imebra_readWriteMemory.h"
#import "imebra_streamReader.h"
#import "imebra_streamWriter.h"
#import "imebra_tag.h"
#import "imebra_tagId.h"
#import "imebra_tcpAddress.h"
#import "imebra_tcpListener.h"
#import "imebra_tcpStream.h"
#import "imebra_transform.h"
#import "imebra_transformHighBit.h"
#import "imebra_transformsChain.h"
#import "imebra_VOILUT.h"
#import "imebra_writingDataHandler.h"
#import "imebra_writingDataHandlerNumeric.h"
#import "imebra_baseUidGenerator.h"
#import "imebra_uidGeneratorFactory.h"
#import "imebra_randomUidGenerator.h"
#import "imebra_serialNumberUidGenerator.h"
#import "imebra_VOIDescription.h"
#import "tagsEnumeration.h"
#import "uidsEnumeration.h"

