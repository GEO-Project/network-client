#include "StorageHandler.h"

StorageHandler::StorageHandler(
    const string &directory,
    const string &dataBaseName,
    Logger *logger):

    mDirectory(directory),
    mDataBaseName(dataBaseName),
    mRoutingTablesHandler(buildDataBasePath(directory, dataBaseName), kRT2TableName, kRT3TableName, logger),
    mTrustLineHandler(buildDataBasePath(directory, dataBaseName), kTrustLineTableName, logger),
    mPaymentOperationStateHandler(buildDataBasePath(directory, dataBaseName), kPaymentOperationStateTableName, logger),
    mLog(logger) {

    sqlite3_config(SQLITE_CONFIG_SINGLETHREAD);
}

StorageHandler::~StorageHandler() {

    closeConnections();
}

RoutingTablesHandler* StorageHandler::routingTablesHandler() {

    return &mRoutingTablesHandler;
}

TrustLineHandler* StorageHandler::trustLineHandler() {

    return &mTrustLineHandler;
}

PaymentOperationStateHandler *StorageHandler::paymentOperationStateHandler() {

    return &mPaymentOperationStateHandler;
}

void StorageHandler::closeConnections() {

    mRoutingTablesHandler.closeConnections();
    mTrustLineHandler.closeConnection();
    mPaymentOperationStateHandler.closeConnection();
}

string StorageHandler::buildDataBasePath(
    const string &directory,
    const string &dataBaseName) {

    string dataBasePath = directory + "/" + dataBaseName;
    if (!fs::is_directory(fs::path(directory))){
        fs::create_directories(
            fs::path(directory));
    }
    return dataBasePath;
}

LoggerStream StorageHandler::info() const {
    if (nullptr == mLog)
        throw Exception("logger is not initialised");
    return mLog->info(logHeader());
}

const string StorageHandler::logHeader() const {
    stringstream s;
    s << "[StorageHandler]";
    return s.str();
}
