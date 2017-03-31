#ifndef GEO_NETWORK_CLIENT_GETNEIGHBORTRANSACTION_H
#define GEO_NETWORK_CLIENT_GETNEIGHBORTRANSACTION_H

#include "../../../base/UniqueTransaction.h"
#include "../../../../../trust_lines/manager/TrustLinesManager.h"
#include "../../../../../io/storage/StorageHandler.h"
#include "../../../../../network/messages/cycles/ThreeNodes/ThreeNodesBalancesRequestMessage.h"
#include "../../../../../network/messages/cycles/ThreeNodes/ThreeNodesBalancesResponseMessage.h"
#include <set>

class GetThreeNodesNeighborBalancesTransaction : public UniqueTransaction {

public:
    GetThreeNodesNeighborBalancesTransaction(
            const TransactionType type,
            const NodeUUID &nodeUUID,
            const NodeUUID &contractorUUID,
            TransactionsScheduler *scheduler,
            TrustLinesManager *manager,
            StorageHandler *handler,
            Logger *logger);

    GetThreeNodesNeighborBalancesTransaction(
            const TransactionType type,
            const NodeUUID &nodeUUID,
            const NodeUUID &contractorUUID,
            ThreeNodesBalancesRequestMessage::Shared message,
            TransactionsScheduler *scheduler,
            TrustLinesManager *manager,
            Logger *logger);

    GetThreeNodesNeighborBalancesTransaction(TransactionsScheduler *scheduler);

    TransactionResult::SharedConst run();

    TransactionResult::SharedConst waitingForNeighborBalances();
    set<NodeUUID> getNeighborsWithContractor();
    pair<BytesShared, size_t> serializeToBytes() const {};

private:
    const uint16_t kResponseCodeSuccess = 200;
    const uint16_t kMaxRequestsCount = 5;
    const uint8_t kConnectionProgression = 2;
    const uint32_t kStandardConnectionTimeout = 20000;

    uint16_t mRequestCounter = 0;
    uint32_t mConnectionTimeout = kStandardConnectionTimeout;
//    Nodes Balances that are mutual between core node and contract node
    ThreeNodesBalancesRequestMessage::Shared mRequestMessage = nullptr;
    NodeUUID mContractorUUID;
    TrustLinesManager *mTrustLinesManager;
    Logger *mlogger;
    StorageHandler *mStorageHandler;
};

#endif //GEO_NETWORK_CLIENT_GETNEIGHBORTRANSACTION_H
