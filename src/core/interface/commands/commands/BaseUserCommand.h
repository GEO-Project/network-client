#ifndef GEO_NETWORK_CLIENT_COMMAND_H
#define GEO_NETWORK_CLIENT_COMMAND_H

#include <string>

#include "../CommandUUID.h"
#include "../../../common/NodeUUID.h"
#include "../../../transactions/TransactionUUID.h"
#include "../../results/CommandResult.h"

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <boost/uuid/uuid.hpp>

namespace uuids = boost::uuids;

typedef boost::posix_time::ptime Timestamp;

class BaseUserCommand {
public:
    static const constexpr char kCommandsSeparator = '\n';
    static const constexpr char kTokensSeparator = '\t';

protected:
    const CommandUUID mUUID;
    const Timestamp mTimestampAccepted;

private:
    const string mDerivedIdentifier;

public:
    BaseUserCommand(
        const CommandUUID &uuid,
        const string& identifier);

    const CommandUUID &uuid() const;

    const string &derivedIdentifier() const;

    const Timestamp &timestampAccepted() const;

    const CommandResult *unexpectedErrorResult();

protected:
    virtual void deserialize(
        const string &commandBuffer) = 0;

};


#endif //GEO_NETWORK_CLIENT_COMMAND_H
