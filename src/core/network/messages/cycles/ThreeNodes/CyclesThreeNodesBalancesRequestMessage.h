#ifndef GEO_NETWORK_CLIENT_BALANCESREQUESTMESSAGE_H
#define GEO_NETWORK_CLIENT_BALANCESREQUESTMESSAGE_H

#include "../../base/transaction/TransactionMessage.h"
#include "../../../../contractors/addresses/BaseAddress.h"
#include "../../../../common/multiprecision/MultiprecisionUtils.h"

class CyclesThreeNodesBalancesRequestMessage:
    public TransactionMessage {

public:
    typedef shared_ptr<CyclesThreeNodesBalancesRequestMessage> Shared;

public:
    CyclesThreeNodesBalancesRequestMessage(
        const SerializedEquivalent equivalent,
        const NodeUUID &senderUUID,
        ContractorID idOnReceiverSide,
        const TransactionUUID &transactionUUID,
        vector<BaseAddress::Shared> &neighbors);

    CyclesThreeNodesBalancesRequestMessage(
        BytesShared buffer);

    const MessageType typeID() const;

    vector<BaseAddress::Shared> neighbors();

    virtual pair<BytesShared, size_t> serializeToBytes() const
        throw(bad_alloc);

protected:
    vector<BaseAddress::Shared> mNeighbors;
};

#endif //GEO_NETWORK_CLIENT_BALANCESREQUESTMESSAGE_H
