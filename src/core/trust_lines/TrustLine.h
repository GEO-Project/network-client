#ifndef GEO_NETWORK_CLIENT_TRUSTLINE_H
#define GEO_NETWORK_CLIENT_TRUSTLINE_H


#include "../common/Types.h"
#include "../common/NodeUUID.h"
#include "../common/exceptions/RuntimeError.h"
#include "../common/exceptions/MemoryError.h"
#include "../common/exceptions/ValueError.h"

#include <vector>


using namespace std;

// todo: tests?
// todo: hsc: review the tests.
class TrustLine {
public:
    typedef shared_ptr<TrustLine> Shared;
    typedef shared_ptr<const TrustLine> SharedConst;

public:
    TrustLine(
        const NodeUUID &nodeUUID,
        const TrustLineAmount &incomingAmount,
        const TrustLineAmount &outgoingAmount,
        const TrustLineBalance &nodeBalance);

    TrustLine(
        const NodeUUID &nodeUUID,
        const TrustLineAmount &incomingAmount,
        const TrustLineAmount &outgoingAmount);

    TrustLine(
        const byte *buffer,
        const NodeUUID &contractorUUID);

    void setIncomingTrustAmount(
        const TrustLineAmount &amount);

    void setOutgoingTrustAmount(
        const TrustLineAmount &amount);

    void setBalance(
        const TrustLineBalance &balance);

    const NodeUUID& contractorNodeUUID() const;
    const TrustLineAmount& incomingTrustAmount() const;
    const TrustLineAmount& outgoingTrustAmount() const;
    const TrustLineBalance& balance() const;

    ConstSharedTrustLineAmount availableAmount() const;

    vector<byte> *serialize();
    void deserialize(
        const byte *buffer);

private:
    static const TrustLineBalance& kZeroBalance();
    static const TrustLineAmount& kZeroAmount();

private:
    void trustAmountToBytes(
        const TrustLineAmount &amount,
        vector<byte> *buffer);

    void balanceToBytes(
        const TrustLineBalance &balance,
        vector<byte> *buffer);

    void parseTrustAmount(
        const byte *buffer,
        TrustLineAmount &variable);

    void parseBalance(
        const byte *buffer);

private:
    const size_t kTrustAmountPartSize = 32;
    const size_t kBalancePartSize = 32;
    const size_t kSignBytePartSize = 1;
    const size_t kRecordSize =
        +kTrustAmountPartSize
        + kTrustAmountPartSize
        + kBalancePartSize
        + kSignBytePartSize;

private:
    NodeUUID mContractorNodeUuid;
    TrustLineAmount mIncomingTrustAmount;
    TrustLineAmount mOutgoingTrustAmount;
    TrustLineBalance mBalance;
};

#endif //GEO_NETWORK_CLIENT_TRUSTLINE_H
