#ifndef GEO_NETWORK_CLIENT_MAXFLOWCALCULATIONCACHEUPDATETRANSACTION_H
#define GEO_NETWORK_CLIENT_MAXFLOWCALCULATIONCACHEUPDATETRANSACTION_H

#include "../../../logger/Logger.h"
#include "../base/BaseTransaction.h"
#include "../../../max_flow_calculation/cashe/MaxFlowCalculationCacheManager.h"

class MaxFlowCalculationCacheUpdateTransaction : public BaseTransaction {

public:
    typedef shared_ptr<MaxFlowCalculationCacheUpdateTransaction> Shared;

public:

    MaxFlowCalculationCacheUpdateTransaction(
        NodeUUID &nodeUUID,
        MaxFlowCalculationCacheManager *maxFlowCalculationCacheManager,
        Logger *logger);

    TransactionResult::SharedConst run();

private:

    MaxFlowCalculationCacheManager *mMaxFlowCalculationCacheManager;
    Logger *mLog;

};


#endif //GEO_NETWORK_CLIENT_MAXFLOWCALCULATIONCACHEUPDATETRANSACTION_H
