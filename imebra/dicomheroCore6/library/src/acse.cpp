/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file acse.cpp
    \brief Implementation of the the ACSE classes.
*/

#include "../include/dicomhero6/acse.h"
#include "../include/dicomhero6/streamReader.h"
#include "../include/dicomhero6/streamWriter.h"
#include "../include/dicomhero6/dataSet.h"
#include "../implementation/acseImpl.h"

namespace dicomhero
{

//
// PresentationContext methods
//
///////////////////////////////////////////////////////////////////////////////

PresentationContext::PresentationContext(const std::string& abstractSyntax):
    m_pPresentationContext(std::make_shared<implementation::presentationContext>(abstractSyntax))
{
}

PresentationContext::PresentationContext(const std::string& abstractSyntax, bool bSCURole, bool bSCPRole):
    m_pPresentationContext(std::make_shared<implementation::presentationContext>(abstractSyntax, bSCURole, bSCPRole))
{
}

PresentationContext::PresentationContext(const PresentationContext& source):
    m_pPresentationContext(getPresentationContextImplementation(source))
{
}

PresentationContext::~PresentationContext()
{
}

void PresentationContext::addTransferSyntax(const std::string& transferSyntax)
{
    m_pPresentationContext->addTransferSyntax(transferSyntax);
}

const std::shared_ptr<implementation::presentationContext>& getPresentationContextImplementation(const PresentationContext& message)
{
    return message.m_pPresentationContext;
}


//
// PresentationContexts methods
//
///////////////////////////////////////////////////////////////////////////////

PresentationContexts::PresentationContexts():
    m_pPresentationContexts(std::make_shared<implementation::presentationContexts>())
{
}

PresentationContexts::PresentationContexts(const PresentationContexts& source):
    m_pPresentationContexts(getPresentationContextsImplementation(source))
{
}

PresentationContexts::~PresentationContexts()
{
}

void PresentationContexts::addPresentationContext(const PresentationContext& presentationContext)
{
    m_pPresentationContexts->m_presentationContexts.push_back(getPresentationContextImplementation(presentationContext));
}

const std::shared_ptr<implementation::presentationContexts>& getPresentationContextsImplementation(const PresentationContexts& message)
{
    return message.m_pPresentationContexts;
}


//
// AssociationMessage methods
//
///////////////////////////////////////////////////////////////////////////////

AssociationMessage::AssociationMessage(const std::string& abstractSyntax):
    AssociationMessage(std::make_shared<implementation::associationMessage>(abstractSyntax))
{
}

AssociationMessage::AssociationMessage(const std::shared_ptr<implementation::associationMessage>& pMessage):
    m_pMessage(pMessage)
{
}

AssociationMessage::AssociationMessage(const AssociationMessage& source):
    m_pMessage(getAssociationMessageImplementation(source))
{
}

AssociationMessage::~AssociationMessage()
{
}

std::string AssociationMessage::getAbstractSyntax() const
{
    DICOMHERO_FUNCTION_START();

    return m_pMessage->getAbstractSyntax();

    DICOMHERO_FUNCTION_END_LOG();
}

DataSet AssociationMessage::getCommand() const
{
    DICOMHERO_FUNCTION_START();

    return DataSet(m_pMessage->getCommandDataSet());

    DICOMHERO_FUNCTION_END_LOG();
}

DataSet AssociationMessage::getPayload() const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::dataSet> pDataSet(m_pMessage->getPayloadDataSetNoThrow());
    if(pDataSet == nullptr)
    {
        DICOMHERO_THROW(AcseNoPayloadError, "Payload not available");
    }
    return DataSet(pDataSet);

    DICOMHERO_FUNCTION_END_LOG();
}

bool AssociationMessage::hasPayload() const
{
    return m_pMessage->getPayloadDataSetNoThrow() != nullptr;
}

const std::shared_ptr<implementation::associationMessage>& getAssociationMessageImplementation(const AssociationMessage& message)
{
    return message.m_pMessage;
}

void AssociationMessage::addDataSet(const DataSet& dataSet)
{
    DICOMHERO_FUNCTION_START();

    getAssociationMessageImplementation(*this)->addDataset(getDataSetImplementation(dataSet));

    DICOMHERO_FUNCTION_END_LOG();
}


//
// AssociationBase methods
//
///////////////////////////////////////////////////////////////////////////////

AssociationBase::AssociationBase(const std::shared_ptr<implementation::associationBase>& pAssociationBase):
    m_pAssociation(pAssociationBase)
{
}

AssociationBase::~AssociationBase()
{
}

AssociationMessage AssociationBase::getCommand()
{
    DICOMHERO_FUNCTION_START();

    return AssociationMessage(m_pAssociation->getCommand());

    DICOMHERO_FUNCTION_END_LOG();
}

AssociationMessage AssociationBase::getResponse(std::uint16_t messageId)
{
    DICOMHERO_FUNCTION_START();

    return AssociationMessage(m_pAssociation->getResponse(messageId));

    DICOMHERO_FUNCTION_END_LOG();
}

void AssociationBase::sendMessage(const AssociationMessage& messageDataSet)
{
    DICOMHERO_FUNCTION_START();

    m_pAssociation->sendMessage(messageDataSet.m_pMessage);

    DICOMHERO_FUNCTION_END_LOG();
}

void AssociationBase::release()
{
    DICOMHERO_FUNCTION_START();

    m_pAssociation->release();

    DICOMHERO_FUNCTION_END_LOG();
}

void AssociationBase::abort()
{
    DICOMHERO_FUNCTION_START();

    m_pAssociation->abort(implementation::acsePDUAAbort::reason_t::serviceUser);

    DICOMHERO_FUNCTION_END_LOG();
}

std::string AssociationBase::getThisAET() const
{
    DICOMHERO_FUNCTION_START();

    return m_pAssociation->getThisAET();

    DICOMHERO_FUNCTION_END_LOG();
}

std::string AssociationBase::getOtherAET() const
{
    DICOMHERO_FUNCTION_START();

    return m_pAssociation->getOtherAET();

    DICOMHERO_FUNCTION_END_LOG();
}

std::string AssociationBase::getTransferSyntax(const std::string &abstractSyntax) const
{
    DICOMHERO_FUNCTION_START();

    return m_pAssociation->getPresentationContextTransferSyntax(abstractSyntax);

    DICOMHERO_FUNCTION_END_LOG();
}

std::vector<std::string> AssociationBase::getTransferSyntaxes(const std::string& abstractSyntax) const
{
    return m_pAssociation->getPresentationContextTransferSyntaxes(abstractSyntax);
}


const std::shared_ptr<implementation::associationBase>& getAssociationBaseImplementation(const AssociationBase& associationBase)
{
    return associationBase.m_pAssociation;
}


//
// AssociationSCU methods
//
///////////////////////////////////////////////////////////////////////////////

AssociationSCU::AssociationSCU(
        const std::string& thisAET,
        const std::string& otherAET,
        std::uint32_t invokedOperations,
        std::uint32_t performedOperations,
        const PresentationContexts& presentationContexts,
        StreamReader& pInput,
        StreamWriter& pOutput,
        std::uint32_t dimseTimeoutSeconds):
    AssociationBase(std::make_shared<implementation::associationSCU>(
                        getPresentationContextsImplementation(presentationContexts),
                thisAET,
                otherAET,
                static_cast<std::uint16_t>(invokedOperations),
                static_cast<std::uint16_t>(performedOperations),
                pInput.m_pReader,
                pOutput.m_pWriter,
                        dimseTimeoutSeconds))
{
}

AssociationSCU::AssociationSCU(const AssociationSCU& source):
    AssociationBase(getAssociationBaseImplementation(source))
{
}

AssociationSCU::~AssociationSCU()
{
}

//
// AssociationSCP methods
//
///////////////////////////////////////////////////////////////////////////////

AssociationSCP::AssociationSCP(
        const std::string& thisAET,
        std::uint32_t invokedOperations,
        std::uint32_t performedOperations,
        const PresentationContexts& presentationContexts,
        StreamReader& pInput,
        StreamWriter& pOutput,
        std::uint32_t dimseTimeoutSeconds,
        std::uint32_t artimTimeoutSeconds):
    AssociationBase(std::make_shared<implementation::associationSCP>(
                        getPresentationContextsImplementation(presentationContexts),
                thisAET,
                static_cast<std::uint16_t>(invokedOperations),
                static_cast<std::uint16_t>(performedOperations),
                pInput.m_pReader,
                pOutput.m_pWriter,
                dimseTimeoutSeconds,
                        artimTimeoutSeconds))
{
}

AssociationSCP::AssociationSCP(const AssociationSCP& source):
    AssociationBase(getAssociationBaseImplementation(source))
{
}

AssociationSCP::~AssociationSCP()
{
}

}
