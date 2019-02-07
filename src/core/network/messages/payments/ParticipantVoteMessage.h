#ifndef GEO_NETWORK_CLIENT_PARTICIPANTVOTEMESSAGE_H
#define GEO_NETWORK_CLIENT_PARTICIPANTVOTEMESSAGE_H

#include "../base/transaction/TransactionMessage.h"
#include "../../../crypto/lamportscheme.h"

using namespace crypto;

class ParticipantVoteMessage : public TransactionMessage {

public:
    typedef shared_ptr<ParticipantVoteMessage> Shared;

public:
    ParticipantVoteMessage(
        const SerializedEquivalent equivalent,
        vector<BaseAddress::Shared> &senderAddresses,
        const TransactionUUID &transactionUUID,
        lamport::Signature::Shared signature);

    ParticipantVoteMessage(
        BytesShared buffer);

    const MessageType typeID() const;

    const lamport::Signature::Shared signature() const;

    pair<BytesShared, size_t> serializeToBytes() const override;

private:
    lamport::Signature::Shared mSignature;
};


#endif //GEO_NETWORK_CLIENT_PARTICIPANTVOTEMESSAGE_H
