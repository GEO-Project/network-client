#include "FinalAmountsConfigurationMessage.h"

FinalAmountsConfigurationMessage::FinalAmountsConfigurationMessage(
    const SerializedEquivalent equivalent,
    vector<BaseAddress::Shared> senderAddresses,
    const TransactionUUID &transactionUUID,
    const vector<pair<PathID, ConstSharedTrustLineAmount>> &finalAmountsConfig,
    const map<PaymentNodeID, Contractor::Shared> &paymentParticipants) :

    RequestMessageWithReservations(
        equivalent,
        senderAddresses,
        transactionUUID,
        finalAmountsConfig),
    mPaymentParticipants(paymentParticipants),
    mIsReceiptContains(false)
{}

FinalAmountsConfigurationMessage::FinalAmountsConfigurationMessage(
    const SerializedEquivalent equivalent,
    vector<BaseAddress::Shared> senderAddresses,
    const TransactionUUID &transactionUUID,
    const vector<pair<PathID, ConstSharedTrustLineAmount>> &finalAmountsConfig,
    const map<PaymentNodeID, Contractor::Shared> &paymentParticipants,
    const KeyNumber publicKeyNumber,
    const lamport::Signature::Shared signature) :

    RequestMessageWithReservations(
        equivalent,
        senderAddresses,
        transactionUUID,
        finalAmountsConfig),
    mPaymentParticipants(paymentParticipants),
    mIsReceiptContains(true),
    mPublicKeyNumber(publicKeyNumber),
    mSignature(signature)
{}

FinalAmountsConfigurationMessage::FinalAmountsConfigurationMessage(
    BytesShared buffer):
    RequestMessageWithReservations(buffer)
{
    auto parentMessageOffset = RequestMessageWithReservations::kOffsetToInheritedBytes();
    auto bytesBufferOffset = buffer.get() + parentMessageOffset;
    //----------------------------------------------------
    auto *paymentParticipantsCount = new (bytesBufferOffset) SerializedRecordsCount;
    bytesBufferOffset += sizeof(SerializedRecordsCount);
    //-----------------------------------------------------
    for (SerializedRecordNumber idx = 0; idx < *paymentParticipantsCount; idx++) {
        auto *paymentNodeID = new (bytesBufferOffset) PaymentNodeID;
        bytesBufferOffset += sizeof(PaymentNodeID);
        //---------------------------------------------------
        auto contractor = make_shared<Contractor>(bytesBufferOffset);
        bytesBufferOffset += contractor->serializedSize();
        //---------------------------------------------------
        mPaymentParticipants.insert(
            make_pair(
                *paymentNodeID,
                contractor));
    }
    //----------------------------------------------------
    memcpy(
        &mIsReceiptContains,
        bytesBufferOffset,
        sizeof(byte));
    //----------------------------------------------------
    if (mIsReceiptContains) {
        bytesBufferOffset += sizeof(byte);
        memcpy(
            &mPublicKeyNumber,
            bytesBufferOffset,
            sizeof(KeyNumber));
        bytesBufferOffset += sizeof(KeyNumber);

        auto signature = make_shared<lamport::Signature>(
            bytesBufferOffset);
        mSignature = signature;
    }
}

const Message::MessageType FinalAmountsConfigurationMessage::typeID() const
{
    return Message::Payments_FinalAmountsConfiguration;
}

const map<PaymentNodeID, Contractor::Shared>& FinalAmountsConfigurationMessage::paymentParticipants() const
{
    return mPaymentParticipants;
}

bool FinalAmountsConfigurationMessage::isReceiptContains() const
{
    return mIsReceiptContains;
}

const KeyNumber FinalAmountsConfigurationMessage::publicKeyNumber() const
{
    return mPublicKeyNumber;
}

const lamport::Signature::Shared FinalAmountsConfigurationMessage::signature() const
{
    return mSignature;
}

pair<BytesShared, size_t> FinalAmountsConfigurationMessage::serializeToBytes() const
{
    auto parentBytesAndCount = RequestMessageWithReservations::serializeToBytes();
    size_t bytesCount = parentBytesAndCount.second
                        + sizeof(SerializedRecordsCount)
                        + sizeof(byte);
    for (const auto &participant : mPaymentParticipants) {
        bytesCount += sizeof(PaymentNodeID) + participant.second->serializedSize();
    }
    if (mIsReceiptContains) {
        bytesCount += sizeof(KeyNumber)
                + lamport::Signature::signatureSize();
    }

    BytesShared buffer = tryMalloc(bytesCount);

    auto initialOffset = buffer.get();
    memcpy(
        initialOffset,
        parentBytesAndCount.first.get(),
        parentBytesAndCount.second);
    auto bytesBufferOffset = initialOffset + parentBytesAndCount.second;

    //----------------------------------------------------
    auto paymentParticipantsCount = (SerializedRecordsCount)mPaymentParticipants.size();
    memcpy(
        bytesBufferOffset,
        &paymentParticipantsCount,
        sizeof(SerializedRecordsCount));
    bytesBufferOffset += sizeof(SerializedRecordsCount);
    //----------------------------------------------------
    for (auto const &paymentNodeIdAndContractor : mPaymentParticipants) {
        memcpy(
            bytesBufferOffset,
            &paymentNodeIdAndContractor.first,
            sizeof(PaymentNodeID));
        bytesBufferOffset += sizeof(PaymentNodeID);

        auto contractorSerializedData = paymentNodeIdAndContractor.second->serializeToBytes();
        memcpy(
            bytesBufferOffset,
            contractorSerializedData.get(),
            paymentNodeIdAndContractor.second->serializedSize());
        bytesBufferOffset += paymentNodeIdAndContractor.second->serializedSize();
    }
    //----------------------------------------------------
    memcpy(
        bytesBufferOffset,
        &mIsReceiptContains,
        sizeof(byte));
    //----------------------------------------------------
    if (mIsReceiptContains) {
        bytesBufferOffset += sizeof(byte);
        memcpy(
            bytesBufferOffset,
            &mPublicKeyNumber,
            sizeof(KeyNumber));
        bytesBufferOffset += sizeof(KeyNumber);

        memcpy(
            bytesBufferOffset,
            mSignature->data(),
            mSignature->signatureSize());
    }
    //----------------------------------------------------
    return make_pair(
        buffer,
        bytesCount);
}
