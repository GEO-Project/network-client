#ifndef GEO_NETWORK_CLIENT_SENDERMESSAGE_H
#define GEO_NETWORK_CLIENT_SENDERMESSAGE_H


#include "Message.hpp"

#include "../../common/NodeUUID.h"
#include "../../common/serialization/BytesDeserializer.h"
#include "../../common/serialization/BytesSerializer.h"


/*
 * Abstract base class for messages that must contain sender node UUID.
 */
class SenderMessage:
    public Message {

public:
    const NodeUUID senderUUID;

public:
    SenderMessage(
        const NodeUUID &senderUUID)
        noexcept;

    SenderMessage(
        BytesShared buffer)
        noexcept;

    virtual pair<BytesShared, size_t> serializeToBytes() const
        noexcept(false);

protected:
    virtual const size_t kOffsetToInheritedBytes() const
        noexcept;
};

#endif //GEO_NETWORK_CLIENT_SENDERMESSAGE_H
