/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement 
 that your application must also be GPL), you may purchase a commercial 
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file configuration.h
    \brief Declaration of the basic data types and of the platform flags
	        (Posix or Windows)

*/

#include <cstdint>

#ifndef MAXIMUM_IMAGE_WIDTH
    #define MAXIMUM_IMAGE_WIDTH 4096
#endif
#ifndef MAXIMUM_IMAGE_HEIGHT
    #define MAXIMUM_IMAGE_HEIGHT 4096
#endif
#ifndef MAXIMUM_PDU_SIZE
    #define MAXIMUM_PDU_SIZE 32768
#endif

#if !defined(DICOMHERO_WINDOWS) && !defined(DICOMHERO_POSIX)

#if defined(_WIN32)
#define DICOMHERO_WINDOWS 1
#endif

#ifndef DICOMHERO_WINDOWS
#define DICOMHERO_POSIX 1
#endif

#endif

#if !defined(DICOMHERO_USE_ICONV) && !defined(DICOMHERO_USE_ICU) && !defined(DICOMHERO_USE_WINDOWS_CHARSET) && !defined(DICOMHERO_USE_JAVA)

#if defined(DICOMHERO_WINDOWS)
    #define DICOMHERO_USE_WINDOWS_CHARSET
#else
    #define DICOMHERO_USE_ICONV
#endif
#endif

