.. _build-distribution-label:

Creating the source distribution from the code in the VCS
=========================================================

This section describes how to create an Imebra Source Distribution containing the full
C++source code, the Java wrappers for Android, the HTML documentation, the test units code coverage
information.

The Imebra image is built on Ubuntu 16.04 with the following apt packages:

- git
- doxygen
- g++
- lcov
- python3
- python3-dev
- python3-pip
- ant
- cmake
- swig
- liblog4cxx-dev
- libdcmtk-dev
- default-jdk
- junit4
- dcmtk

Additionally, three Python packages must be present (installable with pip):

- Sphinx version 2.4.4
- breathe version 4.14.2
- sphinx_rtd_theme

In order to install the packages, type the following commands as root or prepends them with sudo:
::

    apt-get update
    apt-get install tzdata
    apt-get install git
    apt-get install doxygen
    apt-get install g++
    apt-get install lcov
    apt-get install python3
    apt-get install python3-dev
    apt-get install python3-pip
    apt-get install ant
    apt-get install cmake
    apt-get install swig
    apt-get install liblog4cxx-dev
    apt-get install libdcmtk-dev
    apt-get install default-jdk
    apt-get install junit4
    apt-get install dcmtk
    pip3 install Sphinx==2.4.4
    pip3 install breathe==4.14.2
    pip3 install sphinx_rtd_theme


Then clone the Imebra git repository:
::

    git clone git@bitbucket.org:binarno/imebra_git.git

Finally, cd into the imebra folder and execute ant to build the source distribution that includes:

- full C++ source code
- generated Java source code for the Android wrapper
- html documentation
- unit tests
- code coverage report

::

    cd imebra
    ant


Versioning
==========

Public releases of Imebra V5 are versioned according to the rules defined in `Semantic versioning <http://semver.org/>`_.

Additionally, Imebra distributions contain a 4th number that indicates the branch revision number and is used to identify
builds that don't contain any change in the library's source code and interface but contains changes in the auxiliary files (e.g.
changes in the documentation, tests units, etc).

Nightly releases are versioned as public releases but their minor version or patch number are set to 999 (the master branch
or the major version branches have a minor version set to 999, the minor version branches have a patch number set to 999).

For instance:

- version 5.1.2.23 indicates a stable build, built from the revision 23of the branch "5.1.2"
- version 5.1.999.45 indicates a nightly build of version 5.1, build from the commit number 45 in the branch.
- version 5.999.999.678 indicates a nightly build of version 5 (master branch), build from the commit number 678 in the branch.

