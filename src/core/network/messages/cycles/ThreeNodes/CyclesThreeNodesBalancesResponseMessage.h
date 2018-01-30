#ifndef GEO_NETWORK_CLIENT_BALANCESRESPONCEMESSAGE_H
#define GEO_NETWORK_CLIENT_BALANCESRESPONCEMESSAGE_H

#include "../../base/transaction/TransactionMessage.h"
#include "../../../../common/multiprecision/MultiprecisionUtils.h"


class CyclesThreeNodesBalancesResponseMessage:
    public TransactionMessage {

public:
    typedef shared_ptr<CyclesThreeNodesBalancesResponseMessage> Shared;

public:
    CyclesThreeNodesBalancesResponseMessage(
        const NodeUUID &senderUUID,
        const TransactionUUID &transactionUUID,
        uint16_t neighborsUUUIDCount);

    CyclesThreeNodesBalancesResponseMessage(
        const NodeUUID &senderUUID,
        const TransactionUUID &transactionUUID,
        vector<NodeUUID> &neighborsUUUID);

    CyclesThreeNodesBalancesResponseMessage(
        BytesShared buffer);

    virtual pair<BytesShared, size_t> serializeToBytes() const
        throw (bad_alloc);

    void addNeighborUUIDAndBalance(NodeUUID neighborUUID)
        throw (bad_alloc);

    const MessageType typeID() const
        noexcept;

    const bool isTransactionMessage() const
        noexcept;

    vector<NodeUUID> NeighborsAndBalances()
        noexcept;

protected:
    vector<NodeUUID> mNeighborsUUUID;
};

#endif //GEO_NETWORK_CLIENT_BALANCESRESPONCEMESSAGE_H