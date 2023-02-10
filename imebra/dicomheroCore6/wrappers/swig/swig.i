%module (threads="1") dicomhero6


#ifdef SWIGJAVA
    %include <arrays_java.i>
    %include <enums.swg>

    %apply(char *STRING, size_t LENGTH) { (const char *source, size_t sourceSize) };
    %apply(char *STRING, size_t LENGTH) { (char* destination, size_t destinationSize) };

        %rename(assign) operator=;
#endif
#ifdef SWIGPYTHON
    %include <cdata.i>
    %include <pybuffer.i>
    %pybuffer_mutable_binary(void *STRING, size_t LENGTH)
    %apply(void *STRING, size_t LENGTH) { (const char *source, size_t sourceSize) };
    %apply(void *STRING, size_t LENGTH) { (char* destination, size_t destinationSize) };

        %rename(assign) operator=;

#endif

#ifdef SWIGGO
    %include <cdata.i>
    %include <gostring.swg>

        %typemap(gotype) (char* destination, size_t destinationSize) %{[]byte%}

        %typemap(in) (char* destination, size_t destinationSize) {
         $1 = ($1_ltype)$input.array;
         $2 = $input.len;
        }
    %apply(void *STRING, size_t LENGTH) { (const char *source, size_t sourceSize) };

%insert(cgo_comment_typedefs) %{
#cgo LDFLAGS: -ldicomhero
%}

#endif

#define DICOMHERO_API

%{

#include <dicomhero6/dicomhero.h>

%}

%include <stl.i>
%include <std_string.i>

%include <exception.i>
%include <stdint.i>
%include <std_common.i>
%include <std_except.i>
%include <std_vector.i>
%include <std_map.i>


%template(StringsList) std::vector<std::string>;
%template(Groups) std::vector<std::uint16_t>;
%template(TagsIds) std::vector<dicomhero::TagId>;
%template(VOIs) std::vector<dicomhero::VOIDescription>;

%exception {
    try {
        $action
    } catch(const dicomhero::MissingDataElementError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_IndexError, error.c_str());
    } catch(const dicomhero::LutError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_RuntimeError, error.c_str());
    } catch(const dicomhero::StreamError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_IOError, error.c_str());
    } catch(const dicomhero::DictionaryError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_ValueError, error.c_str());
    } catch(const dicomhero::CharsetConversionError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_RuntimeError, error.c_str());
    } catch(const dicomhero::CodecError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_IOError, error.c_str());
    } catch(const dicomhero::DataHandlerError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_ValueError, error.c_str());
    } catch(const dicomhero::DataSetError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_ValueError, error.c_str());
    } catch(const dicomhero::DicomDirError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_RuntimeError, error.c_str());
    } catch(const dicomhero::ImageError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_ValueError, error.c_str());
    } catch(const dicomhero::TransformError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_ValueError, error.c_str());
    } catch(const dicomhero::MemoryError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_MemoryError, error.c_str());
    } catch(const std::bad_cast& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_TypeError, error.c_str());
    } catch(const std::runtime_error& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_RuntimeError, error.c_str());
    } catch(const std::exception& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_RuntimeError, error.c_str());
    }
}


%include "../../library/include/dicomhero6/dicomDefinitions.h"
%include "../../library/include/dicomhero6/tagId.h"
%include "../../library/include/dicomhero6/definitions.h"
%include "../../library/include/dicomhero6/memory.h"
%include "../../library/include/dicomhero6/mutableMemory.h"
%include "../../library/include/dicomhero6/memoryPool.h"
%include "../../library/include/dicomhero6/baseStreamInput.h"
%include "../../library/include/dicomhero6/baseStreamOutput.h"
%include "../../library/include/dicomhero6/streamReader.h"
%include "../../library/include/dicomhero6/streamWriter.h"
%include "../../library/include/dicomhero6/readingDataHandler.h"
%include "../../library/include/dicomhero6/readingDataHandlerNumeric.h"
%include "../../library/include/dicomhero6/writingDataHandler.h"
%include "../../library/include/dicomhero6/writingDataHandlerNumeric.h"
%include "../../library/include/dicomhero6/lut.h"
%include "../../library/include/dicomhero6/image.h"
%include "../../library/include/dicomhero6/overlay.h"
%include "../../library/include/dicomhero6/tag.h"
%include "../../library/include/dicomhero6/dataSet.h"
%include "../../library/include/dicomhero6/codecFactory.h"
%include "../../library/include/dicomhero6/tcpAddress.h"
%include "../../library/include/dicomhero6/tcpListener.h"
%include "../../library/include/dicomhero6/tcpStream.h"
%include "../../library/include/dicomhero6/pipeStream.h"
%include "../../library/include/dicomhero6/transform.h"
%include "../../library/include/dicomhero6/transformHighBit.h"
%include "../../library/include/dicomhero6/transformsChain.h"
%include "../../library/include/dicomhero6/modalityVOILUT.h"
%include "../../library/include/dicomhero6/VOILUT.h"
%include "../../library/include/dicomhero6/VOIDescription.h"
%include "../../library/include/dicomhero6/colorTransformsFactory.h"
%include "../../library/include/dicomhero6/dicomDirEntry.h"
%include "../../library/include/dicomhero6/dicomDir.h"
%include "../../library/include/dicomhero6/dicomDictionary.h"
%include "../../library/include/dicomhero6/drawBitmap.h"
%include "../../library/include/dicomhero6/fileStreamInput.h"
%include "../../library/include/dicomhero6/fileStreamOutput.h"
%include "../../library/include/dicomhero6/memoryStreamInput.h"
%include "../../library/include/dicomhero6/memoryStreamOutput.h"
%include "../../library/include/dicomhero6/acse.h"
%include "../../library/include/dicomhero6/dimse.h"
%include "../../library/include/dicomhero6/date.h"
%include "../../library/include/dicomhero6/age.h"
%include "../../library/include/dicomhero6/patientName.h"
%include "../../library/include/dicomhero6/uidGeneratorFactory.h"
%include "../../library/include/dicomhero6/baseUidGenerator.h"
%include "../../library/include/dicomhero6/randomUidGenerator.h"
%include "../../library/include/dicomhero6/serialNumberUidGenerator.h"




