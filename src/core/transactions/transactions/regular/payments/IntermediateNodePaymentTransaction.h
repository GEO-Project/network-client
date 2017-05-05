﻿#ifndef INTERMEDIATENODEPAYMENTTRANSACTION_H
#define INTERMEDIATENODEPAYMENTTRANSACTION_H


#include "base/BasePaymentTransaction.h"


class IntermediateNodePaymentTransaction:
    public BasePaymentTransaction {

public:
    typedef shared_ptr<IntermediateNodePaymentTransaction> Shared;
    typedef shared_ptr<const IntermediateNodePaymentTransaction> ConstShared;

public:
    IntermediateNodePaymentTransaction(
        const NodeUUID &currentNodeUUID,
        IntermediateNodeReservationRequestMessage::ConstShared message,
        TrustLinesManager *trustLines,
        Logger *log);

    IntermediateNodePaymentTransaction(
        BytesShared buffer,
        TrustLinesManager* trustLines,
        Logger* log);

    TransactionResult::SharedConst run();

    pair<BytesShared, size_t> serializeToBytes();

protected:
    TransactionResult::SharedConst runPreviousNeighborRequestProcessingStage();
    TransactionResult::SharedConst runCoordinatorRequestProcessingStage();
    TransactionResult::SharedConst runNextNeighborResponseProcessingStage();
    TransactionResult::SharedConst runReservationProlongationStage();

protected:
    void deserializeFromBytes(
        BytesShared buffer);

    const string logHeader() const;

protected:
    IntermediateNodeReservationRequestMessage::ConstShared mMessage;

    TrustLineAmount mLastReservedAmount;
    NodeUUID mCoordinator;
    PathUUID mLastProcessedPath;
};


#endif // INTERMEDIATENODEPAYMENTTRANSACTION_H
