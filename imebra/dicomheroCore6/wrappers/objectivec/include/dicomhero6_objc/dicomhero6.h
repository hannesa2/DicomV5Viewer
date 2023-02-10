/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#ifndef __APPLE__
#ifndef NS_ENUM
#define NS_ENUM(_type, _name) enum _name : _type
#endif
#endif

#if !__has_feature(objc_arc)
    static_assert(false, "The library can be compiled only with ARC enabled");
#endif

#import "dicomhero_acse.h"
#import "dicomhero_baseStreamInput.h"
#import "dicomhero_baseStreamOutput.h"
#import "dicomhero_colorTransformsFactory.h"
#import "dicomhero_codecFactory.h"
#import "dicomhero_dataset.h"
#import "dicomhero_dateAge.h"
#import "dicomhero_patientName.h"
#import "dicomhero_dicomDictionary.h"
#import "dicomhero_dicomDir.h"
#import "dicomhero_dimse.h"
#import "dicomhero_drawBitmap.h"
#import "dicomhero_exceptions.h"
#import "dicomhero_fileStreamInput.h"
#import "dicomhero_fileStreamOutput.h"
#import "dicomhero_image.h"
#import "dicomhero_lut.h"
#import "dicomhero_memoryPool.h"
#import "dicomhero_memoryStreamInput.h"
#import "dicomhero_memoryStreamOutput.h"
#import "dicomhero_modalityVOILUT.h"
#import "dicomhero_overlay.h"
#import "dicomhero_pipe.h"
#import "dicomhero_readingDataHandler.h"
#import "dicomhero_readingDataHandlerNumeric.h"
#import "dicomhero_readMemory.h"
#import "dicomhero_readWriteMemory.h"
#import "dicomhero_streamReader.h"
#import "dicomhero_streamWriter.h"
#import "dicomhero_tag.h"
#import "dicomhero_tagId.h"
#import "dicomhero_tcpAddress.h"
#import "dicomhero_tcpListener.h"
#import "dicomhero_tcpStream.h"
#import "dicomhero_transform.h"
#import "dicomhero_transformHighBit.h"
#import "dicomhero_transformsChain.h"
#import "dicomhero_VOILUT.h"
#import "dicomhero_writingDataHandler.h"
#import "dicomhero_writingDataHandlerNumeric.h"
#import "dicomhero_baseUidGenerator.h"
#import "dicomhero_uidGeneratorFactory.h"
#import "dicomhero_randomUidGenerator.h"
#import "dicomhero_serialNumberUidGenerator.h"
#import "dicomhero_VOIDescription.h"
#import "tagsEnumeration.h"
#import "uidsEnumeration.h"

