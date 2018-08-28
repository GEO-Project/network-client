/**
 * This file is part of GEO Protocol.
 * It is subject to the license terms in the LICENSE.md file found in the top-level directory
 * of this distribution and at https://github.com/GEO-Protocol/GEO-network-client/blob/master/LICENSE.md
 *
 * No part of GEO Protocol, including this file, may be copied, modified, propagated, or distributed
 * except according to the terms contained in the LICENSE.md file.
 */

#ifndef GEO_NETWORK_CLIENT_GETFIRSTLEVELCONTRACTORSBALANCESTRANSACTION_H
#define GEO_NETWORK_CLIENT_GETFIRSTLEVELCONTRACTORSBALANCESTRANSACTION_H

#include "../base/BaseTransaction.h"
#include "../../../interface/commands_interface/commands/trust_lines_list/GetTrustLinesCommand.h"
#include "../../../trust_lines/manager/TrustLinesManager.h"


class GetFirstLevelContractorsBalancesTransaction :
    public BaseTransaction {

public:
    typedef shared_ptr<GetFirstLevelContractorsBalancesTransaction> Shared;

public:
    GetFirstLevelContractorsBalancesTransaction(
        NodeUUID &nodeUUID,
        GetTrustLinesCommand::Shared command,
        TrustLinesManager *manager,
        Logger &logger)
    noexcept;

    GetTrustLinesCommand::Shared command() const;

    TransactionResult::SharedConst run();

protected:
    const string logHeader() const;

private:
    GetTrustLinesCommand::Shared mCommand;
    TrustLinesManager *mTrustLinesManager;
};

#endif //GEO_NETWORK_CLIENT_GETFIRSTLEVELCONTRACTORSBALANCESTRANSACTION_H
