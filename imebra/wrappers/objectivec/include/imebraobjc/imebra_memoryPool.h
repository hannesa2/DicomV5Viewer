/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcMemoryPool__INCLUDED_)
#define imebraObjcMemoryPool__INCLUDED_

#import <Foundation/Foundation.h>

@interface ImebraMemoryPool : NSObject

/// \brief Release all the unused memory regions.
///
///////////////////////////////////////////////////////////////////////////////
+(void) flush;

/// \brief Return the total size of the memory that has been released but not
///        yet freed.
///
/// \return the total size of the memory released but not yet freed
///
///////////////////////////////////////////////////////////////////////////////
+(unsigned int) getUnusedMemorySize;

/// \brief Set the maximum size of the kept unused memory.
///
/// \param minMemoryBlockSize  if a memory region is smaller than this size
///                            then when it is released it is deleted
///                            immediately, otherwise it is kept in the memory
///                            pool
/// \param maxMemoryPoolSize   the maximum size of the sum of all the unused
///                            memory regions. When the total size of the
///                            unused memory regions is greater than this
///                            parameter then the oldest memory regions are
///                            deleted permanently
///
///////////////////////////////////////////////////////////////////////////////
+(void) setMemoryPoolSize:(unsigned int)minMemoryBlockSize maxSize:(unsigned int)maxMemoryPoolSize;

@end

#endif // imebraObjcMemoryPool__INCLUDED_


