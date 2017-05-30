#ifndef GEO_NETWORK_CLIENT_SETTRUSTLINETRANSACTION_H
#define GEO_NETWORK_CLIENT_SETTRUSTLINETRANSACTION_H

#include "../base/BaseTransaction.h"

#include "../../../common/Types.h"
#include "../../../common/time/TimeUtils.h"
#include "../../../common/memory/MemoryUtils.h"

#include "../../../io/storage/StorageHandler.h"
#include "../../../io/storage/record/trust_line/TrustLineRecord.h"

#include "../../../interface/commands_interface/commands/trust_lines/SetTrustLineCommand.h"

#include "../../../network/messages/Message.hpp"
#include "../../../network/messages/trust_lines/SetTrustLineMessage.h"
#include "../../../network/messages/trust_lines/UpdateTrustLineMessage.h"

#include "UpdateTrustLineTransaction.h"

#include "../../../trust_lines/manager/TrustLinesManager.h"

#include "../../../common/exceptions/ConflictError.h"

#include <memory>
#include <utility>
#include <cstdint>

class SetTrustLineTransaction:
    public BaseTransaction {

public:
    typedef shared_ptr<SetTrustLineTransaction> Shared;

public:
    SetTrustLineTransaction(
        const NodeUUID &nodeUUID,
        SetTrustLineCommand::Shared command,
        TrustLinesManager *manager,
        StorageHandler *storageHandler,
        Logger &logger);

    TransactionResult::SharedConst run();

protected:
    TransactionResult::SharedConst resultOk();

    TransactionResult::SharedConst resultTrustlineIsAbsent();

    TransactionResult::SharedConst resultProtocolError();

protected:
    const string logHeader() const
    noexcept;

    void updateHistory(
        IOTransaction::Shared ioTransaction);

protected:
    SetTrustLineCommand::Shared mCommand;
    TrustLinesManager *mTrustLines;
    StorageHandler *mStorageHandler;
};


#endif //GEO_NETWORK_CLIENT_SETTRUSTLINETRANSACTION_H
