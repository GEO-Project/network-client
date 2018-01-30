#ifndef GEO_NETWORK_CLIENT_CYCLESIXNODESINBETWEENMESSAGE_H
#define GEO_NETWORK_CLIENT_CYCLESIXNODESINBETWEENMESSAGE_H

#include "base/CyclesBaseFiveOrSixNodesInBetweenMessage.h"

class CyclesSixNodesInBetweenMessage: public CycleBaseFiveOrSixNodesInBetweenMessage {
public:
    typedef shared_ptr<CyclesSixNodesInBetweenMessage> Shared;
public:
    CyclesSixNodesInBetweenMessage(){};
    CyclesSixNodesInBetweenMessage(
        vector<NodeUUID> &path):CycleBaseFiveOrSixNodesInBetweenMessage(path){};
    CyclesSixNodesInBetweenMessage(
        BytesShared buffer):CycleBaseFiveOrSixNodesInBetweenMessage(buffer){};

    const MessageType typeID() const {
        return Message::MessageType::Cycles_SixNodesMiddleware;
    };
};
#endif //GEO_NETWORK_CLIENT_CYCLESIXNODESINBETWEENMESSAGE_H