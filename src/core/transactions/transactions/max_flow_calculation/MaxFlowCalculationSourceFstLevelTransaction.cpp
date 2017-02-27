#include "MaxFlowCalculationSourceFstLevelTransaction.h"

MaxFlowCalculationSourceFstLevelTransaction::MaxFlowCalculationSourceFstLevelTransaction(
    const NodeUUID &nodeUUID,
    MaxFlowCalculationSourceFstLevelInMessage::Shared message,
    TrustLinesManager *trustLinesManager,
    Logger *logger) :

    BaseTransaction(
        BaseTransaction::TransactionType::MaxFlowCalculationSourceFstLevelTransactionType,
        nodeUUID
    ),
    mMessage(message),
    mTrustLinesManager(trustLinesManager),
    mLog(logger){}

MaxFlowCalculationSourceFstLevelTransaction::MaxFlowCalculationSourceFstLevelTransaction(
    BytesShared buffer,
    TrustLinesManager *trustLinesManager) :

    MaxFlowCalculationTransaction(
        BaseTransaction::TransactionType::MaxFlowCalculationSourceFstLevelTransactionType
    ),
    mTrustLinesManager(trustLinesManager){

    deserializeFromBytes(buffer);
}

MaxFlowCalculationSourceFstLevelInMessage::Shared MaxFlowCalculationSourceFstLevelTransaction::message() const {

    return mMessage;
}

pair<BytesShared, size_t> MaxFlowCalculationSourceFstLevelTransaction::serializeToBytes() const {

    auto parentBytesAndCount = BaseTransaction::serializeToBytes();
    auto messageBytesAndCount = mMessage->serializeToBytes();

    size_t bytesCount = parentBytesAndCount.second + messageBytesAndCount.second;
    BytesShared dataBytesShared = tryCalloc(bytesCount);
    //-----------------------------------------------------
    memcpy(
        dataBytesShared.get(),
        parentBytesAndCount.first.get(),
        parentBytesAndCount.second);
    //-----------------------------------------------------
    memcpy(
        dataBytesShared.get() + parentBytesAndCount.second,
        messageBytesAndCount.first.get(),
        messageBytesAndCount.second);
    //-----------------------------------------------------
    return make_pair(
        dataBytesShared,
        bytesCount);
}

void MaxFlowCalculationSourceFstLevelTransaction::deserializeFromBytes(
    BytesShared buffer) {

    BaseTransaction::deserializeFromBytes(buffer);
    BytesShared messageBufferShared = tryCalloc(MaxFlowCalculationSourceFstLevelInMessage::kRequestedBufferSize());
    //-----------------------------------------------------
    memcpy(
        messageBufferShared.get(),
        buffer.get() + BaseTransaction::kOffsetToInheritedBytes(),
        MaxFlowCalculationSourceFstLevelInMessage::kRequestedBufferSize());
    //-----------------------------------------------------
    mMessage = MaxFlowCalculationSourceFstLevelInMessage::Shared(
        new MaxFlowCalculationSourceFstLevelInMessage(
            messageBufferShared));
}

TransactionResult::SharedConst MaxFlowCalculationSourceFstLevelTransaction::run() {

    mLog->logInfo("MaxFlowCalculationSourceFstLevelTransaction->run", "Iam: " + mNodeUUID.stringUUID());
    //mLog->logInfo("MaxFlowCalculationSourceFstLevelTransaction->run", "sender: " + mMessage->senderUUID().stringUUID());
    mLog->logInfo("MaxFlowCalculationSourceFstLevelTransaction->run", "target: " + mMessage->targetUUID().stringUUID());
    mLog->logInfo("MaxFlowCalculationSourceFstLevelTransaction->run",
                  "OutgoingFlows: " + to_string(mTrustLinesManager->getOutgoingFlows().size()));
    mLog->logInfo("MaxFlowCalculationSourceFstLevelTransaction->run",
                  "IncomingFlows: " + to_string(mTrustLinesManager->getIncomingFlows().size()));

    vector<NodeUUID> outgoingFlowUuids = mTrustLinesManager->getFirstLevelNeighborsWithOutgoingFlow();
    NodeUUID targetUUID = mMessage->targetUUID();
    for (auto const &nodeUUIDOutgoingFlow : outgoingFlowUuids) {
        if (nodeUUIDOutgoingFlow == targetUUID) {
            continue;
        }
        Message *message = new MaxFlowCalculationSourceFstLevelOutMessage(
            mNodeUUID,
            targetUUID);

        mLog->logInfo("MaxFlowCalculationSourceFstLevelTransaction->sendFirst", ((NodeUUID)nodeUUIDOutgoingFlow).stringUUID());
        addMessage(
            Message::Shared(message),
            nodeUUIDOutgoingFlow);
    }

    return make_shared<const TransactionResult>(
        TransactionState::exit());

}
