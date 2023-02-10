/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file logging.h
    \brief Defines the classes and the macros used to handle logging.

*/

#if !defined(CImbxLogging_F1BAF067_21DE_466b_AEA1_6CC4F006FAFA__INCLUDED_)
#define CImbxLogging_F1BAF067_21DE_466b_AEA1_6CC4F006FAFA__INCLUDED_

#include "../include/dicomhero6/definitions.h"
#include "configurationImpl.h"
#include <iostream>
#include <sstream>
#include <string>


// Logging levels
#define DICOMHERO_LOG_LEVEL_DISABLED_VALUE 0
#define DICOMHERO_LOG_LEVEL_FATAL_VALUE    1
#define DICOMHERO_LOG_LEVEL_ERROR_VALUE    2
#define DICOMHERO_LOG_LEVEL_WARNING_VALUE  3
#define DICOMHERO_LOG_LEVEL_INFO_VALUE     4
#define DICOMHERO_LOG_LEVEL_DEBUG_DEBUG    5
#define DICOMHERO_LOG_LEVEL_TRACE_VALUE    6

// Define DICOMHERO_LOG_LEVEL to one of the previous values
// to enable logging
#if !defined(DICOMHERO_LOG_LEVEL)

#if defined(DICOMHERO_LOG_LEVEL_TRACE)
#define DICOMHERO_LOG_LEVEL DICOMHERO_LOG_LEVEL_TRACE_VALUE
#elif defined(DICOMHERO_LOG_LEVEL_DEBUG)
#define DICOMHERO_LOG_LEVEL DICOMHERO_LOG_LEVEL_DEBUG_VALUE
#elif defined(DICOMHERO_LOG_LEVEL_INFO)
#define DICOMHERO_LOG_LEVEL DICOMHERO_LOG_LEVEL_INFO_VALUE
#elif defined(DICOMHERO_LOG_LEVEL_WARNING)
#define DICOMHERO_LOG_LEVEL DICOMHERO_LOG_LEVEL_WARNING_VALUE
#elif defined(DICOMHERO_LOG_LEVEL_ERROR)
#define DICOMHERO_LOG_LEVEL DICOMHERO_LOG_LEVEL_ERROR_VALUE
#elif defined(DICOMHERO_LOG_LEVEL_FATAL)
#define DICOMHERO_LOG_LEVEL DICOMHERO_LOG_LEVEL_FATAL_VALUE
#else
#define DICOMHERO_LOG_LEVEL DICOMHERO_LOG_LEVEL_DISABLED_VALUE
#endif

#endif


#if !defined(DICOMHERO_LOG_FATAL_IMPLEMENTATION)

#if !defined(DICOMHERO_LOGGING_LOG4CXX) && !defined(DICOMHERO_LOGGING_ANDROID) && !defined(DICOMHERO_LOGGING_APPLE) && !defined(DICOMHERO_LOGGING_SYSLOG) && !defined(DICOMHERO_LOGGING_COUT)

  #if defined(DICOMHERO_ANDROID)
    #define DICOMHERO_LOGGING_ANDROID
    #if defined(NDEBUG)
      #undef DICOMHERO_LOG_LEVEL
      #define DICOMHERO_LOG_LEVEL DICOMHERO_LOG_LEVEL_DISABLED_VALUE
    #endif
  #elif defined(__APPLE__)
    #define DICOMHERO_LOGGING_APPLE
  #elif defined(DICOMHERO_POSIX)
    #define DICOMHERO_LOGGING_SYSLOG
  #else
    #define DICOMHERO_LOGGING_COUT
  #endif

#endif

#if defined(DICOMHERO_LOGGING_LOG4CXX)

#if DICOMHERO_CPP_VERSION >= 17
  #include <shared_mutex> // Some versions of log4cxx forgot to include shared_mutex
#endif
  #include <log4cxx/logger.h>

  #define DICOMHERO_LOG_FATAL_IMPLEMENTATION(message) LOG4CXX_FATAL(::log4cxx::Logger::getRootLogger(), message.c_str())
  #define DICOMHERO_LOG_ERROR_IMPLEMENTATION(message) LOG4CXX_ERROR(::log4cxx::Logger::getRootLogger(), message.c_str())
  #define DICOMHERO_LOG_WARNING_IMPLEMENTATION(message) LOG4CXX_WARN(::log4cxx::Logger::getRootLogger(), message.c_str())
  #define DICOMHERO_LOG_INFO_IMPLEMENTATION(message) LOG4CXX_INFO(::log4cxx::Logger::getRootLogger(), message.c_str())
  #define DICOMHERO_LOG_DEBUG_IMPLEMENTATION(message) LOG4CXX_DEBUG(::log4cxx::Logger::getRootLogger(), message.c_str())
  #define DICOMHERO_LOG_TRACE_IMPLEMENTATION(message) LOG4CXX_TRACE(::log4cxx::Logger::getRootLogger(), message.c_str())

#elif defined(DICOMHERO_LOGGING_ANDROID)
  #include <android/log.h>

  #define DICOMHERO_LOG_FATAL_IMPLEMENTATION(message) ::__android_log_write(ANDROID_LOG_ASSERT, "Imebra", message.c_str())
  #define DICOMHERO_LOG_ERROR_IMPLEMENTATION(message) ::__android_log_write(ANDROID_LOG_ERROR, "Imebra", message.c_str())
  #define DICOMHERO_LOG_WARNING_IMPLEMENTATION(message) ::__android_log_write(ANDROID_LOG_WARN, "Imebra", message.c_str())
  #define DICOMHERO_LOG_INFO_IMPLEMENTATION(message) ::__android_log_write(ANDROID_LOG_INFO, "Imebra", message.c_str())
  #define DICOMHERO_LOG_DEBUG_IMPLEMENTATION(message) ::__android_log_write(ANDROID_LOG_DEBUG, "Imebra", message.c_str())
  #define DICOMHERO_LOG_TRACE_IMPLEMENTATION(message) ::__android_log_write(ANDROID_LOG_VERBOSE, "Imebra", message.c_str())

#elif defined(DICOMHERO_LOGGING_APPLE)

  namespace dicomhero
  {

  namespace implementation
  {
  void appleLog(const std::string& format, const std::string& message);
  } // namespace implementation

  } // namespace dicomhero

  #define DICOMHERO_LOG_FATAL_IMPLEMENTATION(message) ::dicomhero::implementation::appleLog("FATAL: %@", message.c_str())
  #define DICOMHERO_LOG_ERROR_IMPLEMENTATION(message) ::dicomhero::implementation::appleLog("ERROR: %@", message.c_str())
  #define DICOMHERO_LOG_WARNING_IMPLEMENTATION(message) ::dicomhero::implementation::appleLog("WARNING: %@", message.c_str())
  #define DICOMHERO_LOG_INFO_IMPLEMENTATION(message) ::dicomhero::implementation::appleLog("INFO: %@", message.c_str())
  #define DICOMHERO_LOG_DEBUG_IMPLEMENTATION(message) ::dicomhero::implementation::appleLog("DEBUG: %@", message.c_str())
  #define DICOMHERO_LOG_TRACE_IMPLEMENTATION(message) ::dicomhero::implementation::appleLog("TRACE: %@", message.c_str())

#elif defined(DICOMHERO_LOGGING_SYSLOG)
  #include <syslog.h>

  #define DICOMHERO_LOG_FATAL_IMPLEMENTATION(message) ::syslog(LOG_CRIT, "%s", message.c_str())
  #define DICOMHERO_LOG_ERROR_IMPLEMENTATION(message) ::syslog(LOG_ERR, "%s", message.c_str())
  #define DICOMHERO_LOG_WARNING_IMPLEMENTATION(message) ::syslog(LOG_WARNING, "%s", message.c_str())
  #define DICOMHERO_LOG_INFO_IMPLEMENTATION(message) ::syslog(LOG_INFO, "%s", message.c_str())
  #define DICOMHERO_LOG_DEBUG_IMPLEMENTATION(message) ::syslog(LOG_DEBUG, "%s", message.c_str())
  #define DICOMHERO_LOG_TRACE_IMPLEMENTATION(message) ::syslog(LOG_DEBUG, "%s", message.c_str())

#else

  namespace dicomhero
  {

  namespace implementation
  {

  ///
  /// \brief Returns a string with the current time.
  ///
  /// \return the current time
  ///
  ///////////////////////////////////////////////////////////
  std::string getCurrentTime();

  } // namespace implementation

  } // namespace dicomhero

  #define DICOMHERO_LOG_FATAL_IMPLEMENTATION(message) std::cout << "Imebra FATAL " << ::dicomhero::implementation::getCurrentTime() << " " << message << std::endl;
  #define DICOMHERO_LOG_ERROR_IMPLEMENTATION(message) std::cout << "Imebra ERROR " << ::dicomhero::implementation::getCurrentTime() << " " << message << std::endl;
  #define DICOMHERO_LOG_WARNING_IMPLEMENTATION(message) std::cout << "Imebra WARNING " << ::dicomhero::implementation::getCurrentTime() << " " << message << std::endl;
  #define DICOMHERO_LOG_INFO_IMPLEMENTATION(message) std::cout << "Imebra INFO " << ::dicomhero::implementation::getCurrentTime() << " " << message << std::endl;
  #define DICOMHERO_LOG_DEBUG_IMPLEMENTATION(message) std::cout << "Imebra DEBUG " << ::dicomhero::implementation::getCurrentTime() << " " << message << std::endl;
  #define DICOMHERO_LOG_TRACE_IMPLEMENTATION(message) std::cout << "Imebra TRACE " << ::dicomhero::implementation::getCurrentTime() << " " << message << std::endl;

#endif

#endif // !defined(DICOMHERO_LOG_FATAL_IMPLEMENTATION)

// Logging macros used by Imebra functions
//
///////////////////////////////////////////////////////////

#if DICOMHERO_LOG_LEVEL >= DICOMHERO_LOG_LEVEL_FATAL_VALUE
#define DICOMHERO_LOG_FATAL(message) \
{ \
    std::ostringstream buildMessage; \
    buildMessage << message; \
    DICOMHERO_LOG_FATAL_IMPLEMENTATION(buildMessage.str()); \
}
#else
#define DICOMHERO_LOG_FATAL(message)
#endif

#if DICOMHERO_LOG_LEVEL >= DICOMHERO_LOG_LEVEL_ERROR_VALUE
#define DICOMHERO_LOG_ERROR(message) \
{ \
    std::ostringstream buildMessage; \
    buildMessage << message; \
    DICOMHERO_LOG_ERROR_IMPLEMENTATION(buildMessage.str()); \
}
#else
#define DICOMHERO_LOG_ERROR(message)
#endif

#if DICOMHERO_LOG_LEVEL >= DICOMHERO_LOG_LEVEL_WARNING_VALUE
#define DICOMHERO_LOG_WARNING(message) \
{ \
    std::ostringstream buildMessage; \
    buildMessage << message; \
    DICOMHERO_LOG_WARNING_IMPLEMENTATION(buildMessage.str()); \
}
#else
#define DICOMHERO_LOG_WARNING(message)
#endif

#if DICOMHERO_LOG_LEVEL >= DICOMHERO_LOG_LEVEL_INFO_VALUE
#define DICOMHERO_LOG_INFO(message) \
{ \
    std::ostringstream buildMessage; \
    buildMessage << message; \
    DICOMHERO_LOG_INFO_IMPLEMENTATION(buildMessage.str()); \
}
#else
#define DICOMHERO_LOG_INFO(message)
#endif

#if DICOMHERO_LOG_LEVEL >= DICOMHERO_LOG_LEVEL_DEBUG_DEBUG
#define DICOMHERO_LOG_DEBUG(message) \
{ \
    std::ostringstream buildMessage; \
    buildMessage << message; \
    DICOMHERO_LOG_DEBUG_IMPLEMENTATION(buildMessage.str()); \
}
#else
#define DICOMHERO_LOG_DEBUG(message)
#endif

#if DICOMHERO_LOG_LEVEL >= DICOMHERO_LOG_LEVEL_TRACE_VALUE
#define DICOMHERO_LOG_TRACE(message) \
{ \
    std::ostringstream buildMessage; \
    buildMessage << message; \
    DICOMHERO_LOG_TRACE_IMPLEMENTATION(buildMessage.str()); \
}
#else
#define DICOMHERO_LOG_TRACE(message)
#endif


#endif // CImbxLogging_F1BAF067_21DE_466b_AEA1_6CC4F006FAFA__INCLUDED_
