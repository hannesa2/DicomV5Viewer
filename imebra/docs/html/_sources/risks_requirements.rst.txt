
.. _REQUIREMENTS:

Requirements
------------

This section lists the Imebra v.4 top level requirements and the requirements needed to mitigate the identified risks.


.. _REQ_FUNC:

Functional requirements
.......................




.. _REQ_READ_DICOM_FILES:

[REQ_READ_DICOM_FILES] The library must be able to read DICOM files from a data source and replicate their structure in memory
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must be able to read DICOM files from a data source and replicate their structure in
memory.

The following transfer syntaxes must be supported:

- jpeg baseline (8 bits per color channel lossy), transfer syntax 1.2.840.10008.1.2.4.50
- jpeg baseline extended (12 bits per color channel lossy), transfer syntax 1.2.840.10008.1.2.4.51
- jpeg lossless (up to 16 bits per color channel lossless), transfer syntaxes 1.2.840.10008.1.2.4.57 and 1.2.840.10008.1.2.4.70
- raw dicom (up to 16 bits per color channel lossless), transfer syntaxes 1.2.840.10008.1.2, 1.2.840.10008.1.2.1 and 1.2.840.10008.1.2.2
- rle dicom (up to 16 bits per color channel lossless), transfer syntax 1.2.840.10008.1.2.5






.. _REQ_WRITE_DICOM_FILES:

[REQ_WRITE_DICOM_FILES] The library must be able to write DICOM files from a DICOM structure in memory
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must be able to write DICOM files from a DICOM structure in memory.

The following transfer syntaxes must be supported:

- jpeg baseline (8 bits per color channel lossy), transfer syntax 1.2.840.10008.1.2.4.50
- jpeg baseline extended (12 bits per color channel lossy), transfer syntax 1.2.840.10008.1.2.4.51
- jpeg lossless (up to 16 bits per color channel lossless), transfer syntaxes 1.2.840.10008.1.2.4.57 and 1.2.840.10008.1.2.4.70
- raw dicom (up to 16 bits per color channel lossless), transfer syntaxes 1.2.840.10008.1.2, 1.2.840.10008.1.2.1 and 1.2.840.10008.1.2.2
- rle dicom (up to 16 bits per color channel lossless), transfer syntax 1.2.840.10008.1.2.5






.. _REQ_DIMSE:

[REQ_DIMSE] The library must be able to send and receive DIMSE messages
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must be able to build and parse DIMSE messages through an ACSE service.

The following DIMSE services must be supported:

- C-STORE
- C-GET
- C-MOVE
- C-FIND
- C-ECHO
- C-CANCEL
- N-EVENT-REPORT
- N-GET
- N-SET
- N-ACTION
- N-CREATE
- N-DELETE



Children requirements: 

- :ref:`REQ_GENERIC_STREAM_PROTOCOL`
- :ref:`REQ_TCPIP_PROTOCOL`



.. _REQ_ACSE:

[REQ_ACSE] The library must be able to send and receive ACSE messages through a generic transport mechanism
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must be able to send and receive DUL messages through a generic stream oriented
transport mechanism.

The ACSE management should not be exposed in the API.






.. _REQ_GENERIC_STREAM_PROTOCOL:

[REQ_GENERIC_STREAM_PROTOCOL] There must be a generic streaming protocol able to transport DIMSE messages
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

There must be a generic streaming protocol able to transport DIMSE messages.

The generic streaming protocol must derive from the Imebra base stream class and offer
timeout capabilities and termination capabilities when waiting for incoming or outgoing data.


Parent requirements:

- :ref:`REQ_DIMSE`




.. _REQ_TCPIP_PROTOCOL:

[REQ_TCPIP_PROTOCOL] Imebra must supply a basic TCP streaming class
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

A basic TCP streaming class must be provided so that it can be used with DUL.

TLS is out of the scope of this class.


Parent requirements:

- :ref:`REQ_DIMSE`

Children requirements: 

- :ref:`REQ_USER_PROTOCOL`



.. _REQ_USER_PROTOCOL:

[REQ_USER_PROTOCOL] Imebra must supply a base class for IO streaming
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

Since Imebra does not provide TLS, it must provide a base IO streaming class
from which the user can build its own streaming class.


Parent requirements:

- :ref:`REQ_TCPIP_PROTOCOL`

Children requirements: 

- :ref:`REQ_NO_CALLBACK`



.. _REQ_FUNCTIONAL_MACROS:

[REQ_FUNCTIONAL_MACROS] The operations that get image specific parameters should be aware of Functional Macros
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

Function that retrieve image related information should use also the Functional Macros (global or frame specific).






.. _REQ_ENDIANESS_PLATFORM:

[REQ_ENDIANESS_PLATFORM] Exposed memory with raw numerical data must use the platform endianess to represent numbers
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

Numbers in the tag's memory exposed by the library must be represented using the byte endianess of
the platform on which the library is being used.






.. _REQ_READ_TAGS:

[REQ_READ_TAGS] The library must be able to extract the information contained in the DICOM tags
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must be able to extract the tags information from the DICOM structure in memory.

The following VRs must be supported: AE, AS, AT, CS, DA, DS, DT, FL, FD, IS, LO, LT,
OB, OF, OD, OW, PN, SH, SL, SQ, SS, ST, TM, UI, UL, UN, US, UT, IS



Children requirements: 

- :ref:`REQ_VR_CONVERSION`
- :ref:`REQ_RETURN_DEFAULT_VALUE`

Introduced risks: 

- :ref:`RISK_TAGS_DONT_EXIST`


.. _REQ_WRITE_TAGS:

[REQ_WRITE_TAGS] The library must be able to write tags into the DICOM structure
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must be able to write tags into the DICOM structure in memory.

The following VRs must be supported: AE, AS, AT, CS, DA, DS, DT, FL, FD, IS, LO, LT,
OB, OF, OD, OW, PN, SH, SL, SQ, SS, ST, TM, UI, UL, UN, US, UT, IS



Children requirements: 

- :ref:`REQ_VR_CONVERSION`



.. _REQ_DECOMPRESS_IMAGES:

[REQ_DECOMPRESS_IMAGES] Imebra must be able to decompress images contained in the DICOM dataset
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

Imebra must be able to extract decompressed images from the DICOM dataset.
The recognized transfer syntaxes for the image compression are:

- jpeg baseline (8 bits per color channel lossy), transfer syntax 1.2.840.10008.1.2.4.50
- jpeg baseline extended (12 bits per color channel lossy), transfer syntax 1.2.840.10008.1.2.4.51
- jpeg lossless (up to 16 bits per color channel lossless), transfer syntaxes 1.2.840.10008.1.2.4.57 and 1.2.840.10008.1.2.4.70
- raw dicom (up to 16 bits per color channel lossless), transfer syntaxes 1.2.840.10008.1.2, 1.2.840.10008.1.2.1 and 1.2.840.10008.1.2.2
- rle dicom (up to 16 bits per color channel lossless), transfer syntax 1.2.840.10008.1.2.5




Introduced risks: 

- :ref:`RISK_OUT_OF_MEMORY_BIG_IMAGE`


.. _REQ_COMPRESS_IMAGES:

[REQ_COMPRESS_IMAGES] Imebra must be able to compress images and insert them in the DICOM dataset
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

Imebra must be able to compress images and insert them in the DICOM dataset.

The recognized transfer syntaxes for the image compression are:

- jpeg baseline (8 bits per color channel lossy), transfer syntax 1.2.840.10008.1.2.4.50
- jpeg baseline extended (12 bits per color channel lossy), transfer syntax 1.2.840.10008.1.2.4.51
- jpeg lossless (up to 16 bits per color channel lossless), transfer syntaxes 1.2.840.10008.1.2.4.57 and 1.2.840.10008.1.2.4.70
- raw dicom (up to 16 bits per color channel lossless), transfer syntaxes 1.2.840.10008.1.2, 1.2.840.10008.1.2.1 and 1.2.840.10008.1.2.2
- rle dicom (up to 16 bits per color channel lossless), transfer syntax 1.2.840.10008.1.2.5






.. _REQ_PARSE_DICOMDIR:

[REQ_PARSE_DICOMDIR] The library must be able to parse DICOMDIR structures and the records they contain
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

Imebra must be able to parse DICOMDIR structures and the records they contain.






.. _REQ_BUILD_DICOMDIR:

[REQ_BUILD_DICOMDIR] The library must be able to build DICOMDIR structures and the records they contain
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

Imebra must be able to build DICOMDIR structures and the records they contain.






.. _REQ_VOI_FUNCTION:

[REQ_VOI_FUNCTION] Allow the calculation of the VOI transform using different defined DICOM functions
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

Allow the calculation of the VOI transform using the functions LINEAR, LINEAR_EXACT and SIGMOID as defined by DICOM






.. _REQ_EXCEPTIONS:

[REQ_EXCEPTIONS] All the error should be reported via C++ exceptions
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library should throw specific C++ exceptions to report errors.






.. _REQ_RAW_MEMORY:

[REQ_RAW_MEMORY] The library must be able to expose the raw memory of numeric DICOM tags
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

To be able to perform fast image processing, the client application needs access to the images or
LUTs raw memory data.

This implies that Imebra must be able to expose the raw memory used to store numeric tags (VRs: AT, FL, FD,
OF, OW, OD, SS, SL, UL, US).




Introduced risks: 

- :ref:`RISK_BUFFER_OVERFLOW`


.. _REQ_EXTRACT_LUT:

[REQ_EXTRACT_LUT] The library must be able to extract LUT information from the DataSet
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must be able to extract LUT information from the dataset, regardless of the tag where
it is stored.






.. _REQ_DELAYED_LOAD:

[REQ_DELAYED_LOAD] The library must be able to delay the loading of large chunk of data from the DICOM file
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

In order to minimize the memory footprint of the loaded datasets, the library must be able to load
the tags data only when necessary.

It should also release the loaded memory when the data is no longer necessary






.. _REQ_UID_GEN:

[REQ_UID_GEN] Supply a mechanism to generate unique DICOM UIDs
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must be able to generate unique UIDs to be used in DICOM datasets as SOP instance UID.






.. _REQ_VR_CONVERSION:

[REQ_VR_CONVERSION] The library must be able to convert data between different VRs
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must be able to convert data between different VRs, for instance
from integer to double or string.


Parent requirements:

- :ref:`REQ_READ_TAGS`
- :ref:`REQ_WRITE_TAGS`


Introduced risks: 

- :ref:`RISK_VR_CONVERSION`


.. _REQ_LOGGING:

[REQ_LOGGING] The library must log the most important tasks execution
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must log to the device standard logging the most important steps.






.. _REQ_APPLY_MODALITY_VOILUT:

[REQ_APPLY_MODALITY_VOILUT] The library must be able to apply the modality VOI or LUT to extracted images
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must be able to apply to the images the modality VOI or LUT specified in the dataset.




Introduced risks: 

- :ref:`RISK_WRONG_MODALITY_VOILUT_DATASET`


.. _REQ_PREPARE_RGB_IMAGE:

[REQ_PREPARE_RGB_IMAGE] Imebra must be able to create an image ready to be displayed on the computer screen
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

Imebra must be able to convert the images extracted from DICOM structures into RGBA images ready to
be displayed into computer screens






.. _REQ_APPLY_VOILUT:

[REQ_APPLY_VOILUT] The library must be able to apply the presentation VOI/LUT to the extracted images
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must be able to apply the presentation VOI/LUT to the images extracted from DICOM
datasets




Introduced risks: 

- :ref:`RISK_WRONG_VOILUT_DATASET`


.. _REQ_RETURN_DEFAULT_VALUE:

[REQ_RETURN_DEFAULT_VALUE] There has to be a special function able to return a default value for missing tags
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

In addition to the functions that throw an exception when the required data is missing, special
functions able to return a default value for missing data should be present.


Parent requirements:

- :ref:`REQ_READ_TAGS`


Introduced risks: 

- :ref:`RISK_RECEIVE_DEFAULT_VALUE`


.. _REQ_APP_DECIDES_DEFAULT_VALUE:

[REQ_APP_DECIDES_DEFAULT_VALUE] Default values must be explicitly set by the application for each tag
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must not decide the default value to return when a tag is missing: the
client application must specify the default value on each call.

Mitigates:

- :ref:`RISK_RECEIVE_DEFAULT_VALUE` by 50% The end application must decide the default value, but there is a chance that it still choose the wrong default valur





.. _REQ_THROW_ON_MISSING_DATA:

[REQ_THROW_ON_MISSING_DATA] The library must throw an exception when the client tries to access data that doesn't exist
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must throw an exception when the client tries to access data that doesn't exist.

Mitigates:

- :ref:`RISK_TAGS_DONT_EXIST` by 100% 





.. _REQ_DONT_RETURN_POINTER:

[REQ_DONT_RETURN_POINTER] The API should not return pointers to allocated objects
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

Instead of returning pointers to the allocated objects, the library should return the object instead.
Because the API allocated objects hold just pointer to the implementation classes, copying them around
should not impact the performances.




Introduced risks: 

- :ref:`RISK_COPY_CONST_OBJECTS`


.. _REQ_INSERT_FILES_IN_TAGS:

[REQ_INSERT_FILES_IN_TAGS] Allow to insert reference to files into DICOM tags
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The API client should be able to specify a file as content of a DICOM tag: when the DICOM stream is encoded then
the specific tag content should be fetched directly from the file.






.. _REQ_IMMUTABLE_CLASSES:

[REQ_IMMUTABLE_CLASSES] Data classes should be immutable, with mutable subclasses
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The data classes should be immutable. Mutable subclasses should be used for objects that need to be modified.

Mitigates:

- :ref:`RISK_COPY_CONST_OBJECTS` by 100% By having separate mutable and immutable classes, the compiler will not allow copying an immutable object into a mutable one.





.. _REQ_OVERLAYS:

[REQ_OVERLAYS] The API must supply methods to retrieve and set overlay bitmaps
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The DataSet class must supply methods to retrieve and set overlay bitmaps.






.. _REQ_IMPL:

Implementation requirements
...........................




.. _REQ_NO_CALLBACK:

[REQ_NO_CALLBACK] User extensions should not be achievable by extending Imebra classes or by supplying callbacks
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

Allowing the user to extend Imebra classes or to provide callback functions complicates the separation
between the Imebra's interface and its implementation.


Parent requirements:

- :ref:`REQ_USER_PROTOCOL`




.. _REQ_NO_MULTIPLE_INHERITANCE:

[REQ_NO_MULTIPLE_INHERITANCE] Multiple inheritance is not allowed
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

Some language for which bindings are required don't support multiple inheritance, therefore it should not be used.






.. _REQ_CPP:

[REQ_CPP] The library must be implemented in C++ 0x
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must be implemented in C++0x




Introduced risks: 

- :ref:`RISK_BUFFER_OVERFLOW`
- :ref:`RISK_MEMORY_ALLOC`
- :ref:`RISK_OBJECT_ALLOC`


.. _REQ_BINARY_COMPATIBILITY:

[REQ_BINARY_COMPATIBILITY] The library should offer binary compatibility between minor revisions
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library should offer binary compatibility between minor revisions.

In order to achieve this goal, minimal parts of the library interface should be exposed to the client
application






.. _REQ_MEMORY_ALLOCATION:

[REQ_MEMORY_ALLOCATION] Memory should be allocated via cpp std arrays, vectors, strings, etc, not through new
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

Memory shold be allocated via c++ provided classes instantiated on the stack or
shared pointer if they have to be shared.

Mitigates:

- :ref:`RISK_MEMORY_ALLOC` by 80% 





.. _REQ_OBJECT_ALLOCATION:

[REQ_OBJECT_ALLOCATION] Objects should be allocated via shared pointers, unique pointers or on the stack
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

Objects shared between different components should be allocated via shared pointers,
while objects used only once should be allocated via unique pointers or, preferably, on the stack

Mitigates:

- :ref:`RISK_OBJECT_ALLOC` by 80% 



Introduced risks: 

- :ref:`RISK_SHARED_PTR_NEW`


.. _REQ_THROW_WRONG_CONVERSION:

[REQ_THROW_WRONG_CONVERSION] Throw exception on non allowed VR conversions
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

Some VR convenversions cannot be safely executed.
In particular, the following conversions are forbidden: time and date to/from numbers, age to/from anything else.
Failed conversion from strings to numbers must throw an exception.

Mitigates:

- :ref:`RISK_VR_CONVERSION` by 80% 





.. _REQ_MAKE_SHARED:

[REQ_MAKE_SHARED] Object inserted in shared pointers must be allocated via make_shared
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

Object that at some point are inserted into shared pointers must be
allocated via make_shared

Mitigates:

- :ref:`RISK_SHARED_PTR_NEW` by 90% 





.. _REQ_INTEGER_TYPES:

[REQ_INTEGER_TYPES] The integer types in the public interface must be consistent
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

All the integer that express a size, a file offset or an index must be of type size_t.
All the other integers must be int32_t or uint32_t






.. _REQ_VARIABLE_MAX_IMAGE_SIZE:

[REQ_VARIABLE_MAX_IMAGE_SIZE] The settings of the maximum image size must be settable at runtime
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The client application must be able to modify the maximum acceptable image size.
The max image size settings must be clearly explained in the documentation.


Parent requirements:

- :ref:`REQ_MAX_IMAGE_SIZE`




.. _REQ_TAGID_SEPARATE_CLASS:

[REQ_TAGID_SEPARATE_CLASS] The tag id must be specified using a specific class
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

A class must be used to specify a Dicom tag's id (group, order, id).

Mitigates:

- :ref:`RISK_LONG_PARAMETERS_LIST` by 100% Moving the tag's id outside the parameters list reduces the possibility of errors. Additionally, the tag's id is isolated and visible.





.. _REQ_DONT_EXPOSE_INDEXED_WRITING:

[REQ_DONT_EXPOSE_INDEXED_WRITING] Don't expose methods that allow indexed writing into the buffer while resetting it
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must not expose methods that allow indexed writing into the buffers and
silently erase its previous content.

Mitigates:

- :ref:`RISK_BUFFER_RESET` by 90% If there are no functions that enable indexed writing into the buffer while also resetting it, then the client will not be able to do that





.. _REQ_PERF:

Performances
............




.. _REQ_WRAP_FUNCTIONS_EXCEPTIONS_INFO:

[REQ_WRAP_FUNCTIONS_EXCEPTIONS_INFO] All the functions must be wrapped by macros that report the exception info
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

All the functions must be wrapped by special macros that capture
the information about the exception being thrown or that cause a stack unwind.






.. _REQ_MEMORY_POOL:

[REQ_MEMORY_POOL] The library should reuse unused memory instead of allocating new blocks.
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

When a block of memory is discarded it should be stored in a memory pool
for a while and reused when the library needs a block of the same size.



Children requirements: 

- :ref:`REQ_MEMORY_POOL_THREAD`

Introduced risks: 

- :ref:`RISK_FULL_MEMORY`


.. _REQ_WRITING_HANDLER_EMPTY:

[REQ_WRITING_HANDLER_EMPTY] New writing handler that write data to a buffer should be initially empty
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

For performance reasons, when a buffer returns a new writing data handler (an object
used to write data in the tag) the writing data handler should be initially empty




Introduced risks: 

- :ref:`RISK_BUFFER_RESET`


.. _REQ_MEMORY_POOL_THREAD:

[REQ_MEMORY_POOL_THREAD] There should be a memory pool per thread
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

A memory pool per thread removes the need for synchronization, increasing the
speed of the memory pool methods.


Parent requirements:

- :ref:`REQ_MEMORY_POOL`




.. _REQ_MEMORY_POOL_NEW_HANDLER:

[REQ_MEMORY_POOL_NEW_HANDLER] Provide a std::new_handler that clears the memory pool when necessary
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The std::new_handler function will be automatically called when a new memory
allocation fails, giving the memory pool an opportunity to clear the unused memory.

Mitigates:

- :ref:`RISK_FULL_MEMORY` by 50% The std::new_handler is able to clear the memory pool when a memory allocation fails. Because there is a memory pool per thread, only the memory in the memory pool of the current thread is cleared when a memory allocation fails.





.. _REQ_SEC:

Security
........




.. _REQ_MAX_IMAGE_SIZE:

[REQ_MAX_IMAGE_SIZE] The library must reject images that are bigger than a predefined size
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

The library must have a configurable setting that specifies the maximum
size of the images that can be loaded. An exception must be thrown if the image
is bigger than the setting allows.

Mitigates:

- :ref:`RISK_OUT_OF_MEMORY_BIG_IMAGE` by 80% 


Children requirements: 

- :ref:`REQ_VARIABLE_MAX_IMAGE_SIZE`



.. _RISKS:



Risks
-----

Your development process should take into account the risks exposed in this section.

The risks are ordered by their total mitigated risk (severity * likelihood - mitigation). The most severe risks appear first.

When a risk is mitigated then it contains a link to the mitigating requirement.


.. _RISK_BUFFER_OVERFLOW:

[RISK_BUFFER_OVERFLOW] The library and its client may read or write memory outside the allocated buffer
.......................................................................................................



Likelihood: 100% 

Severity: 100 (0 = no impact, 100 = deadly) 

Total risk (Likelyhood by Severity, 0 = no risk, 10000 = maximum risk): 10000

Mitigated total risk (0 = no risk, 10000 = maximum risk): 10000

Caused by:

- :ref:`REQ_CPP`
- :ref:`REQ_RAW_MEMORY`



.. _RISK_RECEIVE_DEFAULT_VALUE:

[RISK_RECEIVE_DEFAULT_VALUE] When receiving default values for non-existent data the client may understand that the tag is actually present
...........................................................................................................................................

When receiving default values for non-existent data the client may understand that the tag is
actually present.

Likelihood: 100% It is really common that a dataset is missing some tags.

Severity: 100 (0 = no impact, 100 = deadly) If the client application is not aware of the fact that the library may have returned a default value instead of the actual one (that is missing) then it could use it as base for clinical actions or diagnoses.

Total risk (Likelyhood by Severity, 0 = no risk, 10000 = maximum risk): 10000

Mitigated total risk (0 = no risk, 10000 = maximum risk): 5000

Caused by:

- :ref:`REQ_RETURN_DEFAULT_VALUE`


Mitigated by: 

- :ref:`REQ_APP_DECIDES_DEFAULT_VALUE` (by 50%)

.. _RISK_VR_CONVERSION:

[RISK_VR_CONVERSION] Implicit VR conversion may hide wrong tag's VR
...................................................................

The library or the client may read a tag and assume its type: an implicit VR
conversion may hide the fact that the tag has in fact the wrong VR and contain a different
information than the assumed one.

Likelihood: 100% 

Severity: 100 (0 = no impact, 100 = deadly) 

Total risk (Likelyhood by Severity, 0 = no risk, 10000 = maximum risk): 10000

Mitigated total risk (0 = no risk, 10000 = maximum risk): 2000

Caused by:

- :ref:`REQ_VR_CONVERSION`


Mitigated by: 

- :ref:`REQ_THROW_WRONG_CONVERSION` (by 80%)

.. _RISK_MEMORY_ALLOC:

[RISK_MEMORY_ALLOC] The library may use deallocated memory or forget to deallocate memory
.........................................................................................



Likelihood: 100% 

Severity: 100 (0 = no impact, 100 = deadly) The usage of deleted objects may lead to wrong images, tags and ultimately diagnosis

Total risk (Likelyhood by Severity, 0 = no risk, 10000 = maximum risk): 10000

Mitigated total risk (0 = no risk, 10000 = maximum risk): 2000

Caused by:

- :ref:`REQ_CPP`


Mitigated by: 

- :ref:`REQ_MEMORY_ALLOCATION` (by 80%)

.. _RISK_OBJECT_ALLOC:

[RISK_OBJECT_ALLOC] The library and its client may use deallocated objects or forget to deallocate objects
..........................................................................................................



Likelihood: 100% In large projects memory leakage or misusage of raw pointer will almost certainly happen.

Severity: 100 (0 = no impact, 100 = deadly) The usage of deleted objects may lead to wrong images, tags and ultimately diagnosis.

Total risk (Likelyhood by Severity, 0 = no risk, 10000 = maximum risk): 10000

Mitigated total risk (0 = no risk, 10000 = maximum risk): 2000

Caused by:

- :ref:`REQ_CPP`


Mitigated by: 

- :ref:`REQ_OBJECT_ALLOCATION` (by 80%)

.. _RISK_BUFFER_RESET:

[RISK_BUFFER_RESET] When a client wants to write several values in the buffer it may inadvertently reset the buffer
...................................................................................................................

Because a writing data handler always starts in an empty state, a client
may inadvertently erase the buffer content when writing new content into it.

Likelihood: 100% If the library supplies a function able to write in different locations of a buffer then it is very likely that the client will use such function.

Severity: 100 (0 = no impact, 100 = deadly) The final dicom content may not represent what the client intended.

Total risk (Likelyhood by Severity, 0 = no risk, 10000 = maximum risk): 10000

Mitigated total risk (0 = no risk, 10000 = maximum risk): 1000

Caused by:

- :ref:`REQ_WRITING_HANDLER_EMPTY`


Mitigated by: 

- :ref:`REQ_DONT_EXPOSE_INDEXED_WRITING` (by 90%)

.. _RISK_SHARED_PTR_NEW:

[RISK_SHARED_PTR_NEW] Out of sync shared_ptr usage counter
..........................................................

When an object is allocated with new and later inserted into a shared pointer
then the actual object usage counter and the shared pointer usage
counter may be out of sync.

Likelihood: 50% Developers will usually avoid this error, but it may happen.

Severity: 100 (0 = no impact, 100 = deadly) This may lead to usage of memory containing random values, resulting in wrong images, tags and finally diagnoses.

Total risk (Likelyhood by Severity, 0 = no risk, 10000 = maximum risk): 5000

Mitigated total risk (0 = no risk, 10000 = maximum risk): 500

Caused by:

- :ref:`REQ_OBJECT_ALLOCATION`


Mitigated by: 

- :ref:`REQ_MAKE_SHARED` (by 90%)

.. _RISK_WRONG_MODALITY_VOILUT_DATASET:

[RISK_WRONG_MODALITY_VOILUT_DATASET] The client may apply to the image the modality VOI/LUT from the wrong dataset
..................................................................................................................

The client may apply to the image the modality VOI/LUT from the wrong dataset

Likelihood: 5% It is unlikely that the developer will pass the wrong DataSet to the transform.

Severity: 100 (0 = no impact, 100 = deadly) Errors in the modality VOILUT may change the meaning of the pixels, resulting in wrong diagnoses.

Total risk (Likelyhood by Severity, 0 = no risk, 10000 = maximum risk): 500

Mitigated total risk (0 = no risk, 10000 = maximum risk): 500

Caused by:

- :ref:`REQ_APPLY_MODALITY_VOILUT`



.. _RISK_FULL_MEMORY:

[RISK_FULL_MEMORY] The memory retained in the memory pool may cause an out-of-memory error
..........................................................................................



Likelihood: 50% On embedded or small devices (e.g. mobile phones) the amount of RAM may be limited. The usage of a memory pool causes the accumulation.

Severity: 10 (0 = no impact, 100 = deadly) This is a low risk error: the software will stop working and report the error.

Total risk (Likelyhood by Severity, 0 = no risk, 10000 = maximum risk): 500

Mitigated total risk (0 = no risk, 10000 = maximum risk): 250

Caused by:

- :ref:`REQ_MEMORY_POOL`


Mitigated by: 

- :ref:`REQ_MEMORY_POOL_NEW_HANDLER` (by 50%)

.. _RISK_WRONG_VOILUT_DATASET:

[RISK_WRONG_VOILUT_DATASET] The library client may apply to an image the VOI/LUT from a wrong dataset
.....................................................................................................

The client library may apply to an image the VOILUT from the wrong dataset.

Likelihood: 5% It is unlikely that the developer will pass the wrong DataSet to the transform.

Severity: 30 (0 = no impact, 100 = deadly) The risk is related to the presentation LUT, which is used only for presentation of the data, not for analysis.

Total risk (Likelyhood by Severity, 0 = no risk, 10000 = maximum risk): 150

Mitigated total risk (0 = no risk, 10000 = maximum risk): 150

Caused by:

- :ref:`REQ_APPLY_VOILUT`



.. _RISK_OUT_OF_MEMORY_BIG_IMAGE:

[RISK_OUT_OF_MEMORY_BIG_IMAGE] Big images or corrupted image size tags may cause an out-of-memory error
.......................................................................................................

Big images or corrupted image size tags may cause an out-of-memory error

Likelihood: 50% This could happen on embedded or small devices (e.g. mobile phones) where the amount of RAM may be limited.

Severity: 10 (0 = no impact, 100 = deadly) This is a low risk error: the software will stop working and report the error.

Total risk (Likelyhood by Severity, 0 = no risk, 10000 = maximum risk): 500

Mitigated total risk (0 = no risk, 10000 = maximum risk): 100

Caused by:

- :ref:`REQ_DECOMPRESS_IMAGES`


Mitigated by: 

- :ref:`REQ_MAX_IMAGE_SIZE` (by 80%)

.. _RISK_LONG_PARAMETERS_LIST:

[RISK_LONG_PARAMETERS_LIST] Specifying the tag id in the dataset methods may create a long confusing list of parameters
.......................................................................................................................

Because the tag id is composed by group id and tag id (and optionally order id),
the list of parameters in the methods that access a dataset's tags may become too long
and confuse the developers that use the library.

Likelihood: 80% It is very easy to get confused when a long list of parameters is used in a method call, specially when all the parameters are integers (e.g. when setting an integer tag's value).

Severity: 100 (0 = no impact, 100 = deadly) Referencing the wrong tag may cause wrong diagnoses or therapies and lead to death.

Total risk (Likelyhood by Severity, 0 = no risk, 10000 = maximum risk): 8000

Mitigated total risk (0 = no risk, 10000 = maximum risk): 0


Mitigated by: 

- :ref:`REQ_TAGID_SEPARATE_CLASS` (by 100%)

.. _RISK_COPY_CONST_OBJECTS:

[RISK_COPY_CONST_OBJECTS] A const object may be copied into a non-const object
..............................................................................

Because the objects returned by the API are just handlers to implementation objects, the user
may copy a const object into a non-const one, introducing the possibility that the implementation object
pointed by the const object may be changed through the non-const object.

Likelihood: 100% 

Severity: 100 (0 = no impact, 100 = deadly) 

Total risk (Likelyhood by Severity, 0 = no risk, 10000 = maximum risk): 10000

Mitigated total risk (0 = no risk, 10000 = maximum risk): 0

Caused by:

- :ref:`REQ_DONT_RETURN_POINTER`


Mitigated by: 

- :ref:`REQ_IMMUTABLE_CLASSES` (by 100%)

.. _RISK_TAGS_DONT_EXIST:

[RISK_TAGS_DONT_EXIST] The client may ask for tags that don't exist
...................................................................

The client may ask for data not included in the dataset

Likelihood: 100% The chances of requesting a non-existing tag are really high and may happen on every loaded dataset.

Severity: 100 (0 = no impact, 100 = deadly) Missing tags may be essential in making sense of the image and the information contained in the dataset.

Total risk (Likelyhood by Severity, 0 = no risk, 10000 = maximum risk): 10000

Mitigated total risk (0 = no risk, 10000 = maximum risk): 0

Caused by:

- :ref:`REQ_READ_TAGS`


Mitigated by: 

- :ref:`REQ_THROW_ON_MISSING_DATA` (by 100%)


