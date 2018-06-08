#include "ReservationsInRelationToNodeMessage.h"

ReservationsInRelationToNodeMessage::ReservationsInRelationToNodeMessage(
    const SerializedEquivalent equivalent,
    const NodeUUID &senderUUID,
    const TransactionUUID &transactionUUID,
    const vector<pair<PathID, AmountReservation::ConstShared>> &reservations,
    PaymentNodeID paymentNodeID,
    uint32_t publicKeyHash) :

    TransactionMessage(
        equivalent,
        senderUUID,
        transactionUUID),

    mReservations(reservations),
    mPaymentNodeID(paymentNodeID),
    mPublicKeyHash(publicKeyHash)
{}

ReservationsInRelationToNodeMessage::ReservationsInRelationToNodeMessage(
    BytesShared buffer):
    TransactionMessage(buffer)
{
    auto parentMessageOffset = TransactionMessage::kOffsetToInheritedBytes();
    auto bytesBufferOffset = buffer.get() + parentMessageOffset;
    //----------------------------------------------------
    SerializedRecordsCount *reservationsCount = new (bytesBufferOffset) SerializedRecordsCount;
    bytesBufferOffset += sizeof(SerializedRecordsCount);
    //-----------------------------------------------------
    mReservations.reserve(*reservationsCount);
    for (SerializedRecordNumber idx = 0; idx < *reservationsCount; idx++) {

        // PathID
        PathID *pathID = new (bytesBufferOffset) PathID;
        bytesBufferOffset += sizeof(PathID);

        // Amount
        vector<byte> bufferTrustLineAmount(
            bytesBufferOffset,
            bytesBufferOffset + kTrustLineAmountBytesCount);
        bytesBufferOffset += kTrustLineAmountBytesCount;
        TrustLineAmount reservationAmount = bytesToTrustLineAmount(bufferTrustLineAmount);

        // Direction
        AmountReservation::SerializedReservationDirectionSize *direction =
                new (bytesBufferOffset)AmountReservation::SerializedReservationDirectionSize;
        bytesBufferOffset += sizeof(AmountReservation::SerializedReservationDirectionSize);
        auto reservationEnumDirection = static_cast<AmountReservation::ReservationDirection>(*direction);

        auto amountReservation = make_shared<AmountReservation>(
            NodeUUID::empty(),
            reservationAmount,
            reservationEnumDirection);
        mReservations.push_back(
            make_pair(
                *pathID,
                amountReservation));
    }

    memcpy(
        &mPaymentNodeID,
        bytesBufferOffset,
        sizeof(PaymentNodeID));
    bytesBufferOffset += sizeof(PaymentNodeID);

    memcpy(
        &mPublicKeyHash,
        bytesBufferOffset,
        sizeof(uint32_t));
}

const vector<pair<PathID, AmountReservation::ConstShared>>& ReservationsInRelationToNodeMessage::reservations() const
{
    return mReservations;
}

const PaymentNodeID ReservationsInRelationToNodeMessage::paymentNodeID() const
{
    mPaymentNodeID;
}

const uint32_t ReservationsInRelationToNodeMessage::publicKeyHash() const
{
    return mPublicKeyHash;
}

pair<BytesShared, size_t> ReservationsInRelationToNodeMessage::serializeToBytes() const
    throw (bad_alloc)
{
    auto parentBytesAndCount = TransactionMessage::serializeToBytes();
    size_t bytesCount =
        + parentBytesAndCount.second
        + sizeof(SerializedRecordsCount)
        + mReservations.size() *
          (sizeof(PathID) + kTrustLineAmountBytesCount + sizeof(AmountReservation::SerializedReservationDirectionSize))
        + sizeof(PaymentNodeID)
        + sizeof(uint32_t);

    BytesShared buffer = tryMalloc(bytesCount);

    auto initialOffset = buffer.get();
    memcpy(
        initialOffset,
        parentBytesAndCount.first.get(),
        parentBytesAndCount.second);
    auto bytesBufferOffset = initialOffset + parentBytesAndCount.second;
    //----------------------------------------------------
    SerializedRecordsCount reservationsCount = (SerializedRecordsCount)mReservations.size();
    memcpy(
        bytesBufferOffset,
        &reservationsCount,
        sizeof(SerializedRecordsCount));
    bytesBufferOffset += sizeof(SerializedRecordsCount);
    //----------------------------------------------------
    for (auto const &it : mReservations) {
        memcpy(
            bytesBufferOffset,
            &it.first,
            sizeof(PathID));
        bytesBufferOffset += sizeof(PathID);

        vector<byte> serializedAmount = trustLineAmountToBytes(it.second->amount());
        memcpy(
            bytesBufferOffset,
            serializedAmount.data(),
            kTrustLineAmountBytesCount);
        bytesBufferOffset += kTrustLineAmountBytesCount;

        const auto kDirection = it.second->direction();
        memcpy(
            bytesBufferOffset,
            &kDirection,
            sizeof(AmountReservation::SerializedReservationDirectionSize));
        bytesBufferOffset += sizeof(AmountReservation::SerializedReservationDirectionSize);
    }
    //----------------------------------------------------
    mempcpy(
        bytesBufferOffset,
        &mPaymentNodeID,
        sizeof(PaymentNodeID));
    bytesBufferOffset += sizeof(PaymentNodeID);
    //----------------------------------------------------
    memcpy(
        bytesBufferOffset,
        &mPublicKeyHash,
        sizeof(uint32_t));

    return make_pair(
        buffer,
        bytesCount);
}

const Message::MessageType ReservationsInRelationToNodeMessage::typeID() const
{
    return Message::Payments_ReservationsInRelationToNode;
}