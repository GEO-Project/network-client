#include "CyclesFourNodesInitTransaction.h"

CyclesFourNodesInitTransaction::CyclesFourNodesInitTransaction(
    const NodeUUID &nodeUUID,
    const NodeUUID &debtorContractorUUID,
    const NodeUUID &creditorContractorUUID,
    TrustLinesManager *manager,
    RoutingTablesHandler *routingTablesHandler,
    Logger *logger) :

    BaseTransaction(
        BaseTransaction::TransactionType::Cycles_FourNodesInitTransaction,
        nodeUUID,
        logger),
    mTrustLinesManager(manager),
    mRoutingTablesHandler(routingTablesHandler),
    mDebtorContractorUUID(debtorContractorUUID),
    mCreditorContractorUUID(creditorContractorUUID)
{}

TransactionResult::SharedConst CyclesFourNodesInitTransaction::run() {
    switch (mStep) {
        case Stages::CollectDataAndSendMessage:
            return runCollectDataAndSendMessageStage();

        case Stages::ParseMessageAndCreateCycles:
            return runParseMessageAndCreateCyclesStage();

        default:
            throw RuntimeError(
                "CycleThreeNodesInitTransaction::run(): "
                "Invalid transaction step.");
    }
}

TransactionResult::SharedConst CyclesFourNodesInitTransaction::runCollectDataAndSendMessageStage() {

    set<NodeUUID> neighbors = commonNeighborsForDebtorAndCreditorNodes();
    if (neighbors.size() == 0){
        info() << "CyclesFourNodesInitTransaction::runCollectDataAndSendMessageStage: "
               << "No common neighbors. Exit Transaction" << endl;
        return resultDone();
    }
    sendMessage<CyclesFourNodesBalancesRequestMessage>(
        mDebtorContractorUUID,
        mNodeUUID,
        currentTransactionUUID(),
        neighbors);

    sendMessage<CyclesFourNodesBalancesRequestMessage>(
        mCreditorContractorUUID,
        mNodeUUID,
        currentTransactionUUID(),
        neighbors);

    mStep = Stages::ParseMessageAndCreateCycles;
    return resultAwaikAfterMilliseconds(
            mkWaitingForResponseTime);
}

TransactionResult::SharedConst CyclesFourNodesInitTransaction::runParseMessageAndCreateCyclesStage() {
    if (mContext.size() != 2) {
        info() << "No responses messages are present. Can't create cycles paths;";

        return resultDone();
    }
    const auto firstMessage = static_pointer_cast<CyclesFourNodesBalancesResponseMessage>(*mContext.begin());
    const auto secondMessage = static_pointer_cast<CyclesFourNodesBalancesResponseMessage>(*(mContext.end()-1));
    const auto firstContractorUUID = firstMessage->senderUUID;
    const auto secondContractorUUID = secondMessage->senderUUID;

    const TrustLineBalance zeroBalance = 0;
    TrustLineBalance firstContractorBalance = mTrustLinesManager->balance(firstContractorUUID);
    TrustLineBalance secondContractorBalance = mTrustLinesManager->balance(secondContractorUUID);

    // In case if some payment operation was done and balances on the nodes was changed -
    // this check prevents redundant cycles closing operations.
    if ((firstContractorBalance > zeroBalance and secondContractorBalance > zeroBalance) or
        (firstContractorBalance < zeroBalance and secondContractorBalance < zeroBalance) or
        (firstContractorBalance == zeroBalance and secondContractorBalance == zeroBalance)) {

        info() << "Balances between initiator node and (" << firstContractorUUID <<  "), or "
                  "between initiator node and (" << secondContractorUUID << ") was changed. "
                  "Cannot create cycles.";
        return resultDone();
    }
    #ifdef TESTS
        vector<vector<NodeUUID>> ResultCycles;
    #endif
    for (auto &kNodeUUIDFirstMessage: firstMessage->NeighborsUUID()){
        for (auto &kNodeUUIDSecondMessage: secondMessage->NeighborsUUID()){
            if (kNodeUUIDSecondMessage == kNodeUUIDFirstMessage){
                vector<NodeUUID> stepPath = {
                    mNodeUUID,
                    mDebtorContractorUUID,
                    kNodeUUIDSecondMessage,
                    mCreditorContractorUUID};
                // Run transaction to close cycle
                auto sCycle = make_shared<vector<NodeUUID>>(stepPath);
                closeCycleSignal(sCycle);
                #ifdef TESTS
                    ResultCycles.push_back(stepPath);
                #endif
            }
        }
    }

    #ifdef TESTS
        cout << "CyclesThreeNodesInitTransaction::ResultCyclesCount " << to_string(ResultCycles.size()) << endl;
        for (vector<NodeUUID> KCyclePath: ResultCycles){
            stringstream ss;
            copy(KCyclePath.begin(), KCyclePath.end(), ostream_iterator<NodeUUID>(ss, ","));
            cout << "CyclesThreeNodesInitTransaction::CyclePath " << ss.str() << endl;
        }
        cout << "CyclesThreeNodesInitTransaction::End" << endl;
    #endif
    return resultDone();
}

set<NodeUUID> CyclesFourNodesInitTransaction::commonNeighborsForDebtorAndCreditorNodes() {
    const auto creditorsNeighbors = mRoutingTablesHandler->neighborsOfOnRT2(
        mCreditorContractorUUID);
    const auto debtorsNeighbors = mRoutingTablesHandler->neighborsOfOnRT2(
        mDebtorContractorUUID);
    set<NodeUUID> commonNeighbors;
    set_intersection(
        creditorsNeighbors.begin(),
        creditorsNeighbors.end(),
        debtorsNeighbors.begin(),
        debtorsNeighbors.end(),
        std::inserter(
            commonNeighbors,
            commonNeighbors.begin()));

    return commonNeighbors;
}

const string CyclesFourNodesInitTransaction::logHeader() const
{
    stringstream s;
    s << "[CyclesFourNodesInitTransactionTA: " << currentTransactionUUID() << "] ";

    return s.str();
}
