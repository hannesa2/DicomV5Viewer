.. _changes-log-label:

Changes log
===========

Version |release| (this version)
--------------------------------

- Fixed bug #354 (Imebra switches transfer syntax to implicit when a tag in a sequence is not recognized) as per SOP :ref:`FIXBUG_2`

Version 5.3.2.0
--------------------------------

- Implemented enhancement #351 (Compile also on macOS-bigsur and VisualStudio 2022 on Appveyor) as per SOP :ref:`DEVENH_2`
- Fixed bug #352 (In tcpBaseSocket::poll select (for Windows) returns 0 on time-out) as per SOP :ref:`FIXBUG_2`
- Implemented enhancement #353 (Imebra switches transfer syntax to implicit when a tag is not recognized) as per SOP :ref:`DEVENH_2`

Version 5.3.1.0
--------------------------------

- Fixed bug #350 (Cannot read old NEMA files) as per SOP :ref:`FIXBUG_2`

Version 5.3.0.0
--------------------------------

- Implemented enhancement #315 (Add support for the VR SV, UV, OV) as per SOP :ref:`DEVENH_2`
- Fixed bug #341 (Some ISO 2022 conversions allow 2 escaping sequences, and some ICONV mappings are wrong) as per SOP :ref:`FIXBUG_2`
- Fixed bug #349 (The example "Displaying an image" in the documentation uses VOILUT in the wrong way) as per SOP :ref:`FIXBUG_2`

Version 5.2.1.2
--------------------------------

- Fixed bug #337 (The IOS variable used in CMake conflicts with the same variable that CMake sets when the system is set to "iOS") as per SOP :ref:`FIXBUG_2`
- Fixed bug #342 (The iosphone build on Xcode 12) as per SOP :ref:`FIXBUG_2`
- Implemented enhancement #344 (Run Java tests in the automatic build) as per SOP :ref:`DEVENH_2`
- Implemented enhancement #345 (Remove Python support) as per SOP :ref:`DEVENH_2`

Version 5.2.1.1
--------------------------------

- Fixed bug #334 (The build of ImebraTests fails on some Windows machines) as per SOP :ref:`FIXBUG_2`

Version 5.2.1.0
--------------------------------

- Fixed bug #329 (Slow SCP connection when running on Windows 10) as per SOP :ref:`FIXBUG_2`
- Fixed bug #330 (memoryImpl.h should include <string>)
- Implemented enhancement #331 (Add example of C-FIND processing to scpexample) as per SOP :ref:`DEVENH_2`

Version 5.2.0.0
--------------------------------

- Fixed bug #323 (The PipeStream implementation throws StreamClosedError instead of returning 0 when the pipe has been closed) as per SOP :ref:`FIXBUG_2`
- Fixed bug #324 (The wrappers don't have definitions for VOIDescription and VOIs) as per SOP :ref:`FIXBUG_2`
- Implemented enhancement #325 (Add an example that show the SCP feature) as per SOP :ref:`DEVENH_2`
- Fixed bug #327 (The build fails on VS2015 because two dataHandlerNumeric functions look the same to the compiler, even if they are not) as per SOP :ref:`FIXBUG_2`
- Implemented enhancement #328 (Move the macos build from bitrise to appveyor) as per SOP :ref:`DEVENH_2`

Version 5.1.0.0
--------------------------------

- Implemented enhancement #316 (Add functions to retrieve floats, uint8, uint16, int8, int16) as per SOP :ref:`DEVENH_2`
- Fixed bug #317 (readingDataHandlerStringAS::getAge does not properly check for the age units) as per SOP :ref:`FIXBUG_2`
- Implemented enhancement #318 (The data handler for VR "AT" should provide a way to retrieve the group and the id) as per sop :ref:`DEVENH_2`
- Implemented enhancement #319 (Remove the compilation warnings on Windows) as per sop :ref:`DEVENH_2`
- Fixed bug #320 (CMake tries to build the mm implementation files also when objective-c is not available) as per SOP :ref:`FIXBUG_2`
- Fixed bug #321 (The test objectivec.stringToNSStringTest fails) as per SOP :ref:`FIXBUG_2`

Version 5.0.1.1
--------------------------------

- Fixed bug #307 (Remove the build-tools folder from the source code) as per SOP :ref:`FIXBUG_2`
- Implemented enhancement #308 (Remove non necessary files imebra_android.iml and ant.properties from the javaWrapper folder) as per SOP :ref:`DEVENH_2`
- Implemented enhancement #309 (Add information about the commercial license in the user manual) as per SOP :ref:`DEVENH_2`
- Implemented enhancement #310 (Migration from Mercurial to Git: change the SOPs & scripts to reflect the usage of Git instead of Mercurial) as per SOP :ref:`DEVENH_2`
- Implemented enhancement #311 (Use the bitbucket pipeline artifacts instead of uploading the generated file to dropbox) as per SOP :ref:`DEVENH_2`
- Implemented enhancement #312 (Add QtCreator .user files to gitignore) as per SOP :ref:`DEVENH_2`
- Fixed bug #313 (Fix the CMake install commands so the Cmake configuration is properly exported and reusable by other modules) as per SOP :ref:`FIXBUG_2`
- Fixed bug #314 (The identifier for the Apple compiler changed from clang to AppleClang, causing the compilation to fail) as per SOP :ref:`FIXBUG_2`


Version 5.0.1.0
--------------------------------

- Fixed bug #306 (The group length for groups 0 and 2 is mandatory) as per SOP :ref:`FIXBUG_2`

Version 5.0.0.0
--------------------------------

First public release of Imebra V5.

