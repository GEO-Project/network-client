#include "CheckIfNodeInBlackListTransaction.h"

CheckIfNodeInBlackListTransaction::CheckIfNodeInBlackListTransaction(
    NodeUUID &nodeUUID,
    CheckIfNodeInBlackListCommand::Shared command,
    StorageHandler *storageHandler,
    Logger &logger):
    BaseTransaction(
        BaseTransaction::CheckIfNodeInBlackListTransactionType,
        nodeUUID,
        logger),
    mCommand(command),
    mStorageHandler(storageHandler)
{
}

CheckIfNodeInBlackListCommand::Shared CheckIfNodeInBlackListTransaction::command() const
{
    return mCommand;
}

TransactionResult::SharedConst CheckIfNodeInBlackListTransaction::run() {
    auto ioTransaction = mStorageHandler->beginTransaction();
    const auto contractorNode = mCommand->contractorUUID();
    const auto kContractorNodesBanned = ioTransaction->blackListHandler()->checkIfNodeExist(contractorNode);
    if (kContractorNodesBanned){
        return transactionResultFromCommand(mCommand->responseOK());
    } else {
        return transactionResultFromCommand(mCommand->responseTrustlineIsAbsent());
    }
}

const string CheckIfNodeInBlackListTransaction::logHeader() const
{
    stringstream s;
    s << "[CheckIfNodeInBlackListTA: " << currentTransactionUUID() << "] ";
    return s.str();
}