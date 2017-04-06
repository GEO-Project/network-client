#ifndef GEO_NETWORK_CLIENT_PATHSMANAGER_H
#define GEO_NETWORK_CLIENT_PATHSMANAGER_H

#include "../trust_lines/manager/TrustLinesManager.h"
#include "../network/messages/find_path/ResultRoutingTablesMessage.h"
#include "../io/storage/StorageHandler.h"
#include "lib/Path.h"
#include "lib/PathsCollection.h"
#include "../logger/Logger.h"

#include <vector>
#include <unordered_map>
#include <set>

class PathsManager {

public:

    PathsManager(
        const NodeUUID &nodeUUID,
        TrustLinesManager *trustLinesManager,
        StorageHandler* storageHandler,
        Logger *logger);

    void findPaths(
        const NodeUUID &contractorUUID,
        vector<NodeUUID> &contractorRT1,
        unordered_map<NodeUUID, vector<NodeUUID>> &contractorRT2,
        unordered_map<NodeUUID, vector<NodeUUID>> &contractorRT3);

    void findPathsOnSelfArea(
        const NodeUUID &contractorUUID);

    // TODO : test
    void findPathsTest(
        const NodeUUID &contractorUUID,
        vector<NodeUUID> &contractorRT1,
        unordered_map<NodeUUID, vector<NodeUUID>> &contractorRT2,
        unordered_map<NodeUUID, vector<NodeUUID>> &contractorRT3);

    PathsCollection::Shared pathCollection() const;

private:

    void findDirectPath();

    void findPathsOnSecondLevel();

    void findPathsOnThirdLevel();

    void findPathsOnForthLevel(
        vector<NodeUUID> &contractorRT1);

    void findPathsOnFifthLevel(
        unordered_map<NodeUUID, vector<NodeUUID>> &contractorRT2);

    void findPathsOnSixthLevel(
        unordered_map<NodeUUID, vector<NodeUUID>> &contractorRT3,
        unordered_map<NodeUUID, vector<NodeUUID>> &contractorRT2);

    vector<NodeUUID> intermediateNodesOnContractorFirstLevel(
        const NodeUUID &thirdLevelSourceNode,
        vector<NodeUUID> &intermediateNodes,
        unordered_map<NodeUUID, vector<NodeUUID>> &contractorRT2) const;

    // test
    void findPathsOnSecondLevelTest();

    void findPathsOnThirdLevelTest();

    void findPathsOnForthLevelTest(
        vector<NodeUUID> &contractorRT1);

    void findPathsOnFifthLevelTest(
        unordered_map<NodeUUID, vector<NodeUUID>> &contractorRT2);

    void findPathsOnSixthLevelTest(
        unordered_map<NodeUUID, vector<NodeUUID>> &contractorRT3,
        unordered_map<NodeUUID, vector<NodeUUID>> &contractorRT2);

    vector<NodeUUID> intermediateNodesOnContractorFirstLevelTest(
        const NodeUUID &thirdLevelSourceNode,
        unordered_map<NodeUUID, vector<NodeUUID>> &contractorRT2) const;

    bool isPathValid(const Path &path);
    //test end

    LoggerStream info() const;

    const string logHeader() const;

    // TODO : remove after testing
    void fillRoutingTables();
    void fillBigRoutingTables();
    string nodeUUIDName(uint32_t number);
    NodeUUID* getPtrByNodeNumber(
        uint32_t number,
        vector<NodeUUID*> nodeUUIDPtrs);

    // TODO: remove after testing
    void testStorageHandler();
    void testTrustLineHandler();
    void testPaymentStateOperationsHandler();

private:

    TrustLinesManager *mTrustLinesManager;
    StorageHandler *mStorageHandler;
    Logger *mLog;
    PathsCollection::Shared mPathCollection;
    NodeUUID mNodeUUID;

    NodeUUID mContractorUUID;

};


#endif //GEO_NETWORK_CLIENT_PATHSMANAGER_H
