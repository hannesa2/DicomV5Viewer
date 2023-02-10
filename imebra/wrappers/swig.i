%module (threads="1") imebra


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
#cgo LDFLAGS: -limebra
%}

#endif

#define IMEBRA_API

%{

#include <imebra/imebra.h>

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
%template(TagsIds) std::vector<imebra::TagId>;
%template(VOIs) std::vector<imebra::VOIDescription>;

%exception {
    try {
        $action
    } catch(const imebra::MissingDataElementError& e) {
        std::string error(imebra::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_IndexError, error.c_str());
    } catch(const imebra::LutError& e) {
        std::string error(imebra::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_RuntimeError, error.c_str());
    } catch(const imebra::StreamError& e) {
        std::string error(imebra::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_IOError, error.c_str());
    } catch(const imebra::DictionaryError& e) {
        std::string error(imebra::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_ValueError, error.c_str());
    } catch(const imebra::CharsetConversionError& e) {
        std::string error(imebra::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_RuntimeError, error.c_str());
    } catch(const imebra::CodecError& e) {
        std::string error(imebra::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_IOError, error.c_str());
    } catch(const imebra::DataHandlerError& e) {
        std::string error(imebra::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_ValueError, error.c_str());
    } catch(const imebra::DataSetError& e) {
        std::string error(imebra::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_ValueError, error.c_str());
    } catch(const imebra::DicomDirError& e) {
        std::string error(imebra::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_RuntimeError, error.c_str());
    } catch(const imebra::ImageError& e) {
        std::string error(imebra::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_ValueError, error.c_str());
    } catch(const imebra::TransformError& e) {
        std::string error(imebra::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_ValueError, error.c_str());
    } catch(const imebra::MemoryError& e) {
        std::string error(imebra::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_MemoryError, error.c_str());
    } catch(const std::bad_cast& e) {
        std::string error(imebra::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_TypeError, error.c_str());
    } catch(const std::runtime_error& e) {
        std::string error(imebra::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_RuntimeError, error.c_str());
    } catch(const std::exception& e) {
        std::string error(imebra::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_RuntimeError, error.c_str());
    }
}


%include "../library/include/imebra/dicomDefinitions.h"
%include "../library/include/imebra/tagId.h"
%include "../library/include/imebra/definitions.h"
%include "../library/include/imebra/memory.h"
%include "../library/include/imebra/mutableMemory.h"
%include "../library/include/imebra/memoryPool.h"
%include "../library/include/imebra/baseStreamInput.h"
%include "../library/include/imebra/baseStreamOutput.h"
%include "../library/include/imebra/streamReader.h"
%include "../library/include/imebra/streamWriter.h"
%include "../library/include/imebra/readingDataHandler.h"
%include "../library/include/imebra/readingDataHandlerNumeric.h"
%include "../library/include/imebra/writingDataHandler.h"
%include "../library/include/imebra/writingDataHandlerNumeric.h"
%include "../library/include/imebra/lut.h"
%include "../library/include/imebra/image.h"
%include "../library/include/imebra/overlay.h"
%include "../library/include/imebra/tag.h"
%include "../library/include/imebra/dataSet.h"
%include "../library/include/imebra/codecFactory.h"
%include "../library/include/imebra/tcpAddress.h"
%include "../library/include/imebra/tcpListener.h"
%include "../library/include/imebra/tcpStream.h"
%include "../library/include/imebra/pipeStream.h"
%include "../library/include/imebra/transform.h"
%include "../library/include/imebra/transformHighBit.h"
%include "../library/include/imebra/transformsChain.h"
%include "../library/include/imebra/modalityVOILUT.h"
%include "../library/include/imebra/VOILUT.h"
%include "../library/include/imebra/VOIDescription.h"
%include "../library/include/imebra/colorTransformsFactory.h"
%include "../library/include/imebra/dicomDirEntry.h"
%include "../library/include/imebra/dicomDir.h"
%include "../library/include/imebra/dicomDictionary.h"
%include "../library/include/imebra/drawBitmap.h"
%include "../library/include/imebra/fileStreamInput.h"
%include "../library/include/imebra/fileStreamOutput.h"
%include "../library/include/imebra/memoryStreamInput.h"
%include "../library/include/imebra/memoryStreamOutput.h"
%include "../library/include/imebra/acse.h"
%include "../library/include/imebra/dimse.h"
%include "../library/include/imebra/date.h"
%include "../library/include/imebra/age.h"
%include "../library/include/imebra/patientName.h"
%include "../library/include/imebra/uidGeneratorFactory.h"
%include "../library/include/imebra/baseUidGenerator.h"
%include "../library/include/imebra/randomUidGenerator.h"
%include "../library/include/imebra/serialNumberUidGenerator.h"




