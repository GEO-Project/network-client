#include "TransactionState.h"

/*!
 * Returns TransactionState with awakening timestamp set to current UTC;
 */
TransactionState::Shared TransactionState::awakeAsFastAsPossible() {
    auto t = datetime::microsec_clock::universal_time();
    return make_shared<TransactionState>(
        timestampFromTheGEOEpoch(
            t));
}

/*!
 * Returns TransactionState with awakening timestamp set to current UTC + timeout;
 */
TransactionState::Shared TransactionState::awakeAfterMilliseconds(
    uint16_t milliseconds) {

    auto t = datetime::microsec_clock::universal_time() + datetime::microseconds(milliseconds*1000);
    return make_shared<TransactionState>(
        timestampFromTheGEOEpoch(
            t));
}

TransactionState::TransactionState(
    uint64_t awakeTimestamp,
    bool flushToPermanentStorage) :

    mAwakeningTimestamp(awakeTimestamp) {

    mFlushToPermanentStorage = flushToPermanentStorage;
}

TransactionState::TransactionState(
    Message::MessageTypeID requiredMessageType,
    bool flushToPermanentStorage) {

    mRequiredMessageTypes.push_back(requiredMessageType);
    mFlushToPermanentStorage = flushToPermanentStorage;
}

TransactionState::TransactionState(
    uint64_t awakeTimestamp,
    Message::MessageTypeID requiredMessageType,
    bool flushToPermanentStorage) :

        mAwakeningTimestamp(awakeTimestamp) {

    mRequiredMessageTypes.push_back(requiredMessageType);
    mFlushToPermanentStorage = flushToPermanentStorage;
}

TransactionState::~TransactionState() {
}

const uint64_t TransactionState::awakeningTimestamp() const {
    return mAwakeningTimestamp;
}

const vector<Message::MessageTypeID>& TransactionState::acceptedMessagesTypes() const {
    return mRequiredMessageTypes;
}

const bool TransactionState::needSerialize() const {
    return mFlushToPermanentStorage;
}



datetime::ptime &TransactionState::GEOEpoch() {
    static boost::posix_time::ptime GEOEpoch(
        boost::gregorian::date(2015, boost::gregorian::Feb, 2));

    return GEOEpoch;
}

TransactionState::AwakeTimestamp TransactionState::timestampFromTheGEOEpoch(
    datetime::ptime &timestamp) {

    datetime::time_duration diff = (timestamp - GEOEpoch());

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"
    return diff.total_microseconds();
#pragma clang diagnostic pop
}




