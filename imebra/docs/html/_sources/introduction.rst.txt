Introduction
============

Imebra is a C++ library able to parse and build DICOM files (including DICOMDIR
files) and send and receives ACSE messages and DIMSE commands and responses.

It also supplies the necessary codecs to encode and decode the images embedded in the DICOM structures.

When Imebra reads a DICOM stream then it inserts the DICOM content into the :ref:`DataSet` class.

Other functions allow the application to read or write into the DICOM tags, or to store new images 
into the dataSet.

You can get Imebra from https://imebra.com

Before committing to the usage of Imebra, please read the :ref:`REQUIREMENTS` that the library
fullfills as well as the :ref:`RISKS` that the usage of the library introduces.

