﻿#include "CoordinatorReservationRequestMessage.h"


CoordinatorReservationRequestMessage::CoordinatorReservationRequestMessage(
    const NodeUUID& senderUUID,
    const TransactionUUID& transactionUUID,
    const vector<pair<PathID, ConstSharedTrustLineAmount>> &finalAmountsConfig,
    const NodeUUID& nextNodeInThePath) :

    FinalAmountsConfigurationMessage(
        senderUUID,
        transactionUUID,
        finalAmountsConfig),
    mNextPathNode(nextNodeInThePath)
{}

CoordinatorReservationRequestMessage::CoordinatorReservationRequestMessage(
    BytesShared buffer) :

    FinalAmountsConfigurationMessage(buffer)
{
    size_t parentMessageOffset = TransactionMessage::kOffsetToInheritedBytes()
                                 + sizeof(FinalAmountsConfigurationMessage::RecordCount)
                                 + finalAmountsConfiguration().size() *
                                   (sizeof(PathID) + kTrustLineAmountBytesCount);

    memcpy(
        mNextPathNode.data,
        buffer.get() + parentMessageOffset,
        NodeUUID::kBytesSize);
}


const NodeUUID& CoordinatorReservationRequestMessage::nextNodeInPath() const
{
    return mNextPathNode;
}

const Message::MessageType CoordinatorReservationRequestMessage::typeID() const
{
    return Message::Payments_CoordinatorReservationRequest;
}

/**
 * @throws bad_alloc;
 */
pair<BytesShared, size_t> CoordinatorReservationRequestMessage::serializeToBytes() const
    throw(bad_alloc)
{    
    auto parentBytesAndCount = FinalAmountsConfigurationMessage::serializeToBytes();
    size_t totalBytesCount =
        + parentBytesAndCount.second
        + NodeUUID::kBytesSize;

    BytesShared buffer = tryMalloc(totalBytesCount);
    memcpy(
        buffer.get(),
        parentBytesAndCount.first.get(),
        parentBytesAndCount.second);

    memcpy(
        buffer.get() + parentBytesAndCount.second,
        mNextPathNode.data,
        NodeUUID::kBytesSize);

    return make_pair(
        buffer,
        totalBytesCount);
}
