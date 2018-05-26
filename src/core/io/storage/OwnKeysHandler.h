#ifndef GEO_NETWORK_CLIENT_OWNKEYSHANDLER_H
#define GEO_NETWORK_CLIENT_OWNKEYSHANDLER_H

#include "../../logger/Logger.h"
#include "record/crypto_keys/CryptoKeyRecord.h"
#include "../../common/exceptions/IOError.h"

#include "../../../libs/sqlite3/sqlite3.h"

class OwnKeysHandler {

public:
    OwnKeysHandler(
        sqlite3 *dbConnection,
        const string &tableName,
        Logger &logger);

    void saveKey(
        CryptoKeyRecord::Shared cryptoKeyRecord,
        const TrustLineID trustLineID);

private:
    LoggerStream info() const;

    LoggerStream warning() const;

    const string logHeader() const;

private:
    sqlite3 *mDataBase = nullptr;
    string mTableName;
    Logger &mLog;
};


#endif //GEO_NETWORK_CLIENT_OWNKEYSHANDLER_H
