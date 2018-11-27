#include "PublicKeysSharingSourceTransaction.h"

PublicKeysSharingSourceTransaction::PublicKeysSharingSourceTransaction(
    const NodeUUID &nodeUUID,
    const NodeUUID &contractorUUID,
    const SerializedEquivalent equivalent,
    ContractorsManager *contractorsManager,
    TrustLinesManager *manager,
    StorageHandler *storageHandler,
    Keystore *keystore,
    TrustLinesInfluenceController *trustLinesInfluenceController,
    Logger &logger) :
    BaseTransaction(
        BaseTransaction::PublicKeysSharingSourceTransactionType,
        nodeUUID,
        equivalent,
        logger),
    mContractorUUID(contractorUUID),
    mCurrentKeyNumber(0),
    mKeysCount(crypto::TrustLineKeychain::kDefaultKeysSetSize),
    mCountSendingAttempts(0),
    mContractorsManager(contractorsManager),
    mTrustLines(manager),
    mStorageHandler(storageHandler),
    mKeysStore(keystore),
    mTrustLinesInfluenceController(trustLinesInfluenceController)
{
    mStep = Initialization;
}

PublicKeysSharingSourceTransaction::PublicKeysSharingSourceTransaction(
    const NodeUUID &nodeUUID,
    const NodeUUID &contractorUUID,
    ContractorID contractorID,
    const SerializedEquivalent equivalent,
    ContractorsManager *contractorsManager,
    TrustLinesManager *manager,
    StorageHandler *storageHandler,
    Keystore *keystore,
    TrustLinesInfluenceController *trustLinesInfluenceController,
    Logger &logger) :
    BaseTransaction(
        BaseTransaction::PublicKeysSharingSourceTransactionType,
        nodeUUID,
        equivalent,
        logger),
    mContractorUUID(contractorUUID),
    mContractorID(contractorID),
    mCurrentKeyNumber(0),
    mKeysCount(crypto::TrustLineKeychain::kDefaultKeysSetSize),
    mCountSendingAttempts(0),
    mContractorsManager(contractorsManager),
    mTrustLines(manager),
    mStorageHandler(storageHandler),
    mKeysStore(keystore),
    mTrustLinesInfluenceController(trustLinesInfluenceController)
{
    mStep = Initialization;
}


PublicKeysSharingSourceTransaction::PublicKeysSharingSourceTransaction(
    const NodeUUID &nodeUUID,
    ShareKeysCommand::Shared command,
    ContractorsManager *contractorsManager,
    TrustLinesManager *manager,
    StorageHandler *storageHandler,
    Keystore *keystore,
    TrustLinesInfluenceController *trustLinesInfluenceController,
    Logger &logger) :
    BaseTransaction(
        BaseTransaction::PublicKeysSharingSourceTransactionType,
        nodeUUID,
        mCommand->equivalent(),
        logger),
    mCommand(command),
    mContractorUUID(mCommand->contractorUUID()),
    mContractorID(mCommand->contractorID()),
    mCurrentKeyNumber(0),
    mKeysCount(crypto::TrustLineKeychain::kDefaultKeysSetSize),
    mCountSendingAttempts(0),
    mContractorsManager(contractorsManager),
    mTrustLines(manager),
    mStorageHandler(storageHandler),
    mKeysStore(keystore),
    mTrustLinesInfluenceController(trustLinesInfluenceController)
{
    mStep = CommandInitialization;
}

TransactionResult::SharedConst PublicKeysSharingSourceTransaction::run()
{
    switch (mStep) {
        case Stages::Initialization: {
            return runPublicKeysSharingInitializationStage();
        }
        case Stages::CommandInitialization: {
            return runCommandPublicKeysSharingInitializationStage();
        }
        case Stages::ResponseProcessing: {
            return runPublicKeysSendNextKeyStage();
        }
        default:
            throw ValueError(logHeader() + "::run: "
                    "wrong value of mStep");
    }
}

TransactionResult::SharedConst PublicKeysSharingSourceTransaction::runPublicKeysSharingInitializationStage()
{
    info() << "runPublicKeysSharingInitializationStage with " << mContractorUUID << " " << mContractorID;

    if (mContractorUUID == mNodeUUID) {
        warning() << "Attempt to launch transaction against itself was prevented.";
        return resultDone();
    }

    if (mTrustLines->trustLineState(mContractorID) == TrustLine::Archived) {
        warning() << "Invalid TL state " << mTrustLines->trustLineState(mContractorID);
        return resultDone();
    }

    auto ioTransaction = mStorageHandler->beginTransaction();
    auto keyChain = mKeysStore->keychain(
        mTrustLines->trustLineID(mContractorID));
    try {
        keyChain.removeUnusedOwnKeys(
            ioTransaction);
        keyChain.generateKeyPairsSet(
            ioTransaction);
        info() << "All keys saved";

#ifdef TESTS
        mTrustLinesInfluenceController->testThrowExceptionOnSourceInitializationStage(
            BaseTransaction::PublicKeysSharingSourceTransactionType);
        mTrustLinesInfluenceController->testTerminateProcessOnSourceInitializationStage(
            BaseTransaction::PublicKeysSharingSourceTransactionType);
#endif

        mCurrentPublicKey = keyChain.publicKey(
            ioTransaction,
            mCurrentKeyNumber);
        if (mCurrentPublicKey == nullptr) {
            warning() << "There are no data for keyNumber " << mCurrentKeyNumber;
            // todo run reset keys sharing TA
            return resultDone();
        }
    } catch (IOError &e) {
        ioTransaction->rollback();
        error() << "Can't generate public keys. Details: " << e.what();
        throw e;
    }

    sendMessage<PublicKeysSharingInitMessage>(
        mContractorID,
        mEquivalent,
        mNodeUUID,
        mContractorsManager->ownAddresses(),
        mTransactionUUID,
        mKeysCount,
        mCurrentKeyNumber,
        mCurrentPublicKey);
    mCountSendingAttempts++;
    info() << "Send key number: " << mCurrentKeyNumber;

    mStep = ResponseProcessing;
    return resultWaitForMessageTypes(
        {Message::TrustLines_HashConfirmation},
        kWaitMillisecondsForResponse);
}

TransactionResult::SharedConst PublicKeysSharingSourceTransaction::runCommandPublicKeysSharingInitializationStage()
{
    info() << "runCommandPublicKeysSharingInitializationStage with " << mContractorUUID << " " << mContractorID;

    if (mContractorUUID == mNodeUUID) {
        warning() << "Attempt to launch transaction against itself was prevented.";
        return resultProtocolError();
    }

    if (mTrustLines->trustLineState(mContractorID) == TrustLine::Archived) {
        warning() << "Invalid TL state " << mTrustLines->trustLineState(mContractorID);
        return resultProtocolError();
    }

    auto ioTransaction = mStorageHandler->beginTransaction();
    auto keyChain = mKeysStore->keychain(
        mTrustLines->trustLineID(mContractorID));
    try {
        keyChain.removeUnusedOwnKeys(
            ioTransaction);
        keyChain.generateKeyPairsSet(
            ioTransaction);
        info() << "All keys saved";

#ifdef TESTS
        mTrustLinesInfluenceController->testThrowExceptionOnSourceInitializationStage(
            BaseTransaction::PublicKeysSharingSourceTransactionType);
        mTrustLinesInfluenceController->testTerminateProcessOnSourceInitializationStage(
            BaseTransaction::PublicKeysSharingSourceTransactionType);
#endif

        mCurrentPublicKey = keyChain.publicKey(
            ioTransaction,
            mCurrentKeyNumber);
        if (mCurrentPublicKey == nullptr) {
            warning() << "There are no data for keyNumber " << mCurrentKeyNumber;
            // todo run reset keys sharing TA
            return resultUnexpectedError();
        }
    } catch (IOError &e) {
        ioTransaction->rollback();
        error() << "Can't generate public keys. Details: " << e.what();
        return resultUnexpectedError();
    }

    sendMessage<PublicKeysSharingInitMessage>(
        mContractorID,
        mEquivalent,
        mNodeUUID,
        mContractorsManager->ownAddresses(),
        mTransactionUUID,
        mKeysCount,
        mCurrentKeyNumber,
        mCurrentPublicKey);
    mCountSendingAttempts++;
    info() << "Send key number: " << mCurrentKeyNumber;

    mStep = ResponseProcessing;
    return resultOK();
}

TransactionResult::SharedConst PublicKeysSharingSourceTransaction::runPublicKeysSendNextKeyStage()
{
    info() << "runPublicKeysSendNextKeyStage";
    if (mContext.empty()) {
        warning() << "No confirmation message received.";
        if (mCountSendingAttempts < kMaxCountSendingAttempts) {
            if (mCurrentKeyNumber == 0) {
                sendMessage<PublicKeysSharingInitMessage>(
                    mContractorID,
                    mEquivalent,
                    mNodeUUID,
                    mContractorsManager->ownAddresses(),
                    mTransactionUUID,
                    mKeysCount,
                    mCurrentKeyNumber,
                    mCurrentPublicKey);
            } else {
                sendMessage<PublicKeyMessage>(
                    mContractorID,
                    mEquivalent,
                    mNodeUUID,
                    mContractorsManager->ownAddresses(),
                    mTransactionUUID,
                    mCurrentKeyNumber,
                    mCurrentPublicKey);
            }
            mCountSendingAttempts++;
            info() << "Send message " << mCountSendingAttempts << " times";
            return resultWaitForMessageTypes(
                {Message::TrustLines_HashConfirmation},
                kWaitMillisecondsForResponse);
        }
        info() << "Transaction will be closed";
        return resultDone();
    }

    auto message = popNextMessage<PublicKeyHashConfirmation>();
    if (message->senderUUID != mContractorUUID) {
        warning() << "Sender is not contractor of this transaction";
        return resultContinuePreviousState();
    }

    if (!mTrustLines->trustLineIsPresent(mContractorID)) {
        warning() << "Something wrong, because TL must be created";
        // todo : need correct reaction
        return resultDone();
    }

    if (message->state() != ConfirmationMessage::OK) {
        warning() << "Contractor didn't accept public key. Response code: " << message->state();
        // todo run reset keys sharing TA
        return resultDone();
    }

    if (message->number() < mCurrentKeyNumber) {
        info() << "message key number " << message->number() << " is less than current. ignore it";
        return resultContinuePreviousState();
    }

    if (message->number() != mCurrentKeyNumber || *message->hashConfirmation() != *mCurrentPublicKey->hash()) {
        warning() << "Number " << message->number() << " or Hash is incorrect";
        // todo run reset keys sharing TA
        return resultDone();
    }

    info() << "Key number: " << mCurrentKeyNumber << " confirmed";
    mCurrentKeyNumber++;
    auto keyChain = mKeysStore->keychain(
        mTrustLines->trustLineID(mContractorID));
    if (mCurrentKeyNumber >= TrustLineKeychain::kDefaultKeysSetSize) {
        info() << "all keys confirmed";
        auto ioTransaction = mStorageHandler->beginTransaction();
        try {
            mTrustLines->setTrustLineState(
                mContractorID,
                TrustLine::Active,
                ioTransaction);
            mTrustLines->setIsOwnKeysPresent(
                mContractorID,
                true);
            info() << "TL is ready for using";
            if (!mTrustLines->isTrustLineEmpty(mContractorID)) {
                auditNewSignal(mContractorUUID, mContractorID, mEquivalent);
            } else {
                if (mTrustLines->trustLineContractorKeysPresent(mContractorID)) {
                    info() << "Init audit signal";
                    auditNewSignal(mContractorUUID, mContractorID, mEquivalent);
                }
            }
        } catch (IOError &e) {
            ioTransaction->rollback();
            error() << "Can't update TL state. Details " << e.what();
            throw e;
        }
        return resultDone();
    }

    auto ioTransaction = mStorageHandler->beginTransaction();
    try {
        mCurrentPublicKey = keyChain.publicKey(
            ioTransaction,
            mCurrentKeyNumber);
        if (mCurrentPublicKey == nullptr) {
            warning() << "There are no data for keyNumber " << mCurrentKeyNumber;
            // todo run reset keys sharing TA
            return resultDone();
        }

#ifdef TESTS
        mTrustLinesInfluenceController->testThrowExceptionOnSourceProcessingResponseStage(
            BaseTransaction::PublicKeysSharingSourceTransactionType);
        mTrustLinesInfluenceController->testTerminateProcessOnSourceProcessingResponseStage(
            BaseTransaction::PublicKeysSharingSourceTransactionType);
#endif

    } catch (IOError &e) {
        ioTransaction->rollback();
        error() << "Can't serialize TA. Details " << e.what();
        throw e;
    }

    sendMessage<PublicKeyMessage>(
        mContractorID,
        mEquivalent,
        mNodeUUID,
        mContractorsManager->ownAddresses(),
        mTransactionUUID,
        mCurrentKeyNumber,
        mCurrentPublicKey);
    mCountSendingAttempts = 1;
    info() << "Send key number: " << mCurrentKeyNumber;

    return resultWaitForMessageTypes(
        {Message::TrustLines_HashConfirmation},
        kWaitMillisecondsForResponse);
}

TransactionResult::SharedConst PublicKeysSharingSourceTransaction::resultOK()
{
    return transactionResultFromCommandAndWaitForMessageTypes(
        mCommand->responseOK(),
        {Message::TrustLines_HashConfirmation},
        kWaitMillisecondsForResponse);
}

TransactionResult::SharedConst PublicKeysSharingSourceTransaction::resultProtocolError()
{
    return transactionResultFromCommand(
        mCommand->responseProtocolError());
}

TransactionResult::SharedConst PublicKeysSharingSourceTransaction::resultUnexpectedError()
{
    return transactionResultFromCommand(
        mCommand->responseUnexpectedError());
}

const string PublicKeysSharingSourceTransaction::logHeader() const
{
    stringstream s;
    s << "[PublicKeysSharingSourceTA: " << currentTransactionUUID() << " " << mEquivalent << "]";
    return s.str();
}