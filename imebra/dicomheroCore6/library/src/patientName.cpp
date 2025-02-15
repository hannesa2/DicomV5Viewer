/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file patientName.cpp
    \brief Implementation of the classes PatientName and UnicodePatientName.

*/

#include "../include/dicomhero6/patientName.h"
#include "../implementation/patientNameImpl.h"
#include "../implementation/exceptionImpl.h"

namespace dicomhero
{


PatientName::PatientName(const PatientName& source):
    m_pPatientName(getPatientNameImplementation(source))
{
}

PatientName::~PatientName()
{
}

PatientName::PatientName(const std::string& alphabeticRepresentation, const std::string& ideographicRepresentation, const std::string& phoneticRepresentation):
    m_pPatientName(std::make_shared<implementation::patientName>(alphabeticRepresentation, ideographicRepresentation, phoneticRepresentation))
{
}

PatientName::PatientName(const std::shared_ptr<implementation::patientName>& pPatientName):
    m_pPatientName(pPatientName)
{
}

const std::shared_ptr<implementation::patientName>& getPatientNameImplementation(const PatientName& patientName)
{
    return patientName.m_pPatientName;
}

std::string PatientName::getAlphabeticRepresentation() const
{
    DICOMHERO_FUNCTION_START();

    return m_pPatientName->getAlphabeticRepresentation();

    DICOMHERO_FUNCTION_END_LOG();
}

std::string PatientName::getIdeographicRepresentation() const
{
    DICOMHERO_FUNCTION_START();

    return m_pPatientName->getIdeographicRepresentation();

    DICOMHERO_FUNCTION_END_LOG();
}

std::string PatientName::getPhoneticRepresentation() const
{
    DICOMHERO_FUNCTION_START();

    return m_pPatientName->getPhoneticRepresentation();

    DICOMHERO_FUNCTION_END_LOG();
}

UnicodePatientName::UnicodePatientName(const UnicodePatientName& source):
    m_pPatientName(source.m_pPatientName)
{
}

UnicodePatientName::~UnicodePatientName()
{
}

UnicodePatientName::UnicodePatientName(const std::wstring& alphabeticRepresentation, const std::wstring& ideographicRepresentation, const std::wstring& phoneticRepresentation):
    m_pPatientName(std::make_shared<implementation::unicodePatientName>(alphabeticRepresentation, ideographicRepresentation, phoneticRepresentation))
{
}

UnicodePatientName::UnicodePatientName(const std::shared_ptr<implementation::unicodePatientName>& pPatientName):
    m_pPatientName(pPatientName)
{
}

const std::shared_ptr<implementation::unicodePatientName>& getUnicodePatientNameImplementation(const UnicodePatientName& patientName)
{
    return patientName.m_pPatientName;
}

std::wstring UnicodePatientName::getAlphabeticRepresentation() const
{
    DICOMHERO_FUNCTION_START();

    return m_pPatientName->getAlphabeticRepresentation();

    DICOMHERO_FUNCTION_END_LOG();
}

std::wstring UnicodePatientName::getIdeographicRepresentation() const
{
    DICOMHERO_FUNCTION_START();

    return m_pPatientName->getIdeographicRepresentation();

    DICOMHERO_FUNCTION_END_LOG();
}

std::wstring UnicodePatientName::getPhoneticRepresentation() const
{
    DICOMHERO_FUNCTION_START();

    return m_pPatientName->getPhoneticRepresentation();

    DICOMHERO_FUNCTION_END_LOG();
}


} // namespace dicomhero

