#include "TransactionsManager.h"
#include "../../network/messages/incoming/routing_tables/FirstLevelRoutingTableIncomingMessage.h"

/*!
 *
 * Throws RuntimeError in case if some internal components can't be initialised.
 */
TransactionsManager::TransactionsManager(
    NodeUUID &nodeUUID,
    as::io_service &IOService,
    TrustLinesManager *trustLinesManager,
    ResultsInterface *resultsInterface,
    Logger *logger) :

    mNodeUUID(nodeUUID),
    mIOService(IOService),
    mTrustLines(trustLinesManager),
    mResultsInterface(resultsInterface),
    mLog(logger),

    mStorage(new storage::UUIDMapBlockStorage(
        "io/transactions",
        "transactions.dat")
    ),

    mScheduler(new TransactionsScheduler(
        mIOService,
        mStorage.get(),
        mLog)
    ) {

    subscribeForCommandResult(mScheduler->commandResultIsReadySignal);

    try {
        loadTransactions();

    } catch (exception &e) {
        throw RuntimeError(e.what());
    }
}

/*!
 *
 * Throws ValueError in case if command is unexpected.
 */
void TransactionsManager::processCommand(
    BaseUserCommand::Shared command) {

    if (command->identifier() == OpenTrustLineCommand::identifier()) {
        launchOpenTrustLineTransaction(
            static_pointer_cast<OpenTrustLineCommand>(
                command));

    } else if (command->identifier() == CloseTrustLineCommand::identifier()) {
        launchCloseTrustLineTransaction(
            static_pointer_cast<CloseTrustLineCommand>(
                command));

    } else if (command->identifier() == SetTrustLineCommand::identifier()) {
        launchSetTrustLineTransaction(
            static_pointer_cast<SetTrustLineCommand>(
                command));

    } else if (command->identifier() == CreditUsageCommand::identifier()) {
        launchCoordinatorPaymentTransaction(
            static_pointer_cast<CreditUsageCommand>(
                command));

    } else {
        throw ValueError(
            "TransactionsManager::processCommand: "
                "unexpected command identifier.");
    }
}

void TransactionsManager::processMessage(
    Message::Shared message) {

    if (message->typeID() == Message::MessageTypeID::AcceptTrustLineMessageType) {
        launchAcceptTrustLineTransaction(
            static_pointer_cast<AcceptTrustLineMessage>(
                message
            )
        );

    } else if (message->typeID() == Message::MessageTypeID::RejectTrustLineMessageType) {
        launchRejectTrustLineTransaction(
            static_pointer_cast<RejectTrustLineMessage>(
                message
            )
        );

    } else if (message->typeID() == Message::MessageTypeID::UpdateTrustLineMessageType) {
        launchUpdateTrustLineTransaction(
            static_pointer_cast<UpdateTrustLineMessage>(
                message
            )
        );

    } else if (message->typeID() == Message::MessageTypeID::FirstLevelRoutingTableIncomingMessageType) {
        FirstLevelRoutingTableIncomingMessage::Shared routingTableMessage = static_pointer_cast<FirstLevelRoutingTableIncomingMessage>(message);
        launchAcceptRoutingTablesTransaction(
            static_pointer_cast<FirstLevelRoutingTableIncomingMessage>(
                message
            )
        );

    } else if (message->typeID() == Message::MessageTypeID::SecondLevelRoutingTableIncomingMessageType) {
        mScheduler->handleMessage(message);

    }else {
        mScheduler->handleMessage(message);
    }
}

void TransactionsManager::loadTransactions() {

    auto uuidKeys = unique_ptr<const vector<storage::uuids::uuid>>(mStorage->keys());
    if (uuidKeys->size() == 0) {
        return;
    }

    for (auto const &uuidKey : *uuidKeys) {
        try {
            auto record = mStorage->readByUUID(uuidKey);

            BytesShared transactionBuffer = tryCalloc(record->bytesCount());
            memcpy(
                transactionBuffer.get(),
                const_cast<byte *> (record->data()),
                record->bytesCount()
            );

            BaseTransaction::SerializedTransactionType *type = new (transactionBuffer.get()) BaseTransaction::SerializedTransactionType;
            BaseTransaction::TransactionType transactionType = (BaseTransaction::TransactionType) *type;

            BaseTransaction *transaction;
            switch (transactionType) {
                case BaseTransaction::TransactionType::OpenTrustLineTransactionType: {
                    transaction = new OpenTrustLineTransaction(
                        transactionBuffer,
                        mScheduler.get(),
                        mTrustLines
                    );
                    break;
                }

                case BaseTransaction::TransactionType::SetTrustLineTransactionType: {
                    transaction = new SetTrustLineTransaction(
                        transactionBuffer,
                        mScheduler.get(),
                        mTrustLines
                    );
                    break;
                }

                case BaseTransaction::TransactionType::CloseTrustLineTransactionType: {
                    transaction = new CloseTrustLineTransaction(
                        transactionBuffer,
                        mScheduler.get(),
                        mTrustLines
                    );
                    break;
                }

                case BaseTransaction::TransactionType::AcceptTrustLineTransactionType: {
                    transaction = new AcceptTrustLineTransaction(
                        transactionBuffer,
                        mScheduler.get(),
                        mTrustLines
                    );
                    break;
                }

                case BaseTransaction::TransactionType::UpdateTrustLineTransactionType: {
                    transaction = new UpdateTrustLineTransaction(
                        transactionBuffer,
                        mScheduler.get(),
                        mTrustLines
                    );
                    break;
                }

                case BaseTransaction::TransactionType::RejectTrustLineTransactionType: {
                    transaction = new RejectTrustLineTransaction(
                        transactionBuffer,
                        mScheduler.get(),
                        mTrustLines
                    );
                    break;
                }

                default: {
                    throw RuntimeError(
                        "TrustLinesManager::loadTransactions. "
                            "Unexpected transaction type identifier.");
                }
            }

            subscribeForOutgoingMessages(
                transaction->outgoingMessageIsReadySignal);

            mScheduler->scheduleTransaction(
                BaseTransaction::Shared(transaction));

        } catch(IndexError &e) {
            throw RuntimeError(
                string(
                    "TransactionsManager::loadTransactions: "
                        "Internal error: ") + e.what());

        } catch (IOError &e) {
            throw RuntimeError(
                string(
                    "TransactionsManager::loadTransactions: "
                        "Internal error: ") + e.what());

        } catch (bad_alloc &) {
            throw MemoryError(
                "TransactionsManager::loadTransactions: "
                    "Bad alloc.");
        }
    }
}

/*!
 *
 * Throws MemoryError.
 */
void TransactionsManager::launchOpenTrustLineTransaction(
    OpenTrustLineCommand::Shared command) {

    try {
        auto transaction = make_shared<OpenTrustLineTransaction>(
            mNodeUUID,
            command,
            mScheduler.get(),
            mTrustLines
        );

        subscribeForOutgoingMessages(transaction->outgoingMessageIsReadySignal);

        mScheduler->scheduleTransaction(transaction);

    } catch (bad_alloc &) {
        throw MemoryError(
            "TransactionsManager::launchOpenTrustLineTransaction: "
                "Can't allocate memory for transaction instance.");
    }
}

/*!
 *
 * Throws MemoryError.
 */
void TransactionsManager::launchSetTrustLineTransaction(
    SetTrustLineCommand::Shared command) {

    try {
        auto transaction = make_shared<SetTrustLineTransaction>(
            mNodeUUID,
            command,
            mScheduler.get(),
            mTrustLines
        );

        subscribeForOutgoingMessages(transaction->outgoingMessageIsReadySignal);

        mScheduler->scheduleTransaction(transaction);

    } catch (bad_alloc &) {
        throw MemoryError(
            "TransactionsManager::launchSetTrustLineTransaction: "
                "Can't allocate memory for transaction instance.");
    }
}

/*!
 *
 * Throws MemoryError.
 */
void TransactionsManager::launchCloseTrustLineTransaction(
    CloseTrustLineCommand::Shared command) {

    try {
        auto transaction = make_shared<CloseTrustLineTransaction>(
            mNodeUUID,
            command,
            mScheduler.get(),
            mTrustLines
        );

        subscribeForOutgoingMessages(transaction->outgoingMessageIsReadySignal);

        mScheduler->scheduleTransaction(transaction);

    } catch (bad_alloc &) {
        throw MemoryError(
            "TransactionsManager::launchCloseTrustLineTransaction: "
                "Can't allocate memory for transaction instance.");
    }
}

/*!
 *
 * Throws MemoryError.
 */
void TransactionsManager::launchAcceptTrustLineTransaction(
    AcceptTrustLineMessage::Shared message) {

    try {
        auto transaction = make_shared<AcceptTrustLineTransaction>(
            mNodeUUID,
            message,
            mScheduler.get(),
            mTrustLines
        );

        subscribeForOutgoingMessages(transaction->outgoingMessageIsReadySignal);

        mScheduler->scheduleTransaction(transaction);

    } catch (bad_alloc &) {
        throw MemoryError(
            "TransactionsManager::launchAcceptTrustLineTransaction: "
                "Can't allocate memory for transaction instance.");
    }
}

void TransactionsManager::launchUpdateTrustLineTransaction(
    UpdateTrustLineMessage::Shared message) {

    try {
        auto transaction = make_shared<UpdateTrustLineTransaction>(
            mNodeUUID,
            message,
            mScheduler.get(),
            mTrustLines
        );

        subscribeForOutgoingMessages(transaction->outgoingMessageIsReadySignal);

        mScheduler->scheduleTransaction(transaction);

    } catch (bad_alloc &) {
        throw MemoryError(
            "TransactionsManager::launchUpdateTrustLineTransaction: "
                "can't allocate memory for transaction instance.");
    }
}

/*!
 *
 * Throws MemoryError.
 */
void TransactionsManager::launchRejectTrustLineTransaction(
    RejectTrustLineMessage::Shared message) {

    try {
        auto transaction = make_shared<RejectTrustLineTransaction>(
            mNodeUUID,
            message,
            mScheduler.get(),
            mTrustLines
        );

        subscribeForOutgoingMessages(transaction->outgoingMessageIsReadySignal);

        mScheduler->scheduleTransaction(transaction);

    } catch (bad_alloc &) {
        throw MemoryError(
            "TransactionsManager::launchRejectTrustLineTransaction: "
                "Can't allocate memory for transaction instance.");
    }
}

/*!
 *
 * Throws MemoryError.
 */
void TransactionsManager::launchCoordinatorPaymentTransaction(
    CreditUsageCommand::Shared command) {

    try {
        auto transaction = make_shared<CoordinatorPaymentTransaction>(
            mNodeUUID,
            command,
            mTrustLines,
            mLog);

        subscribeForOutgoingMessages(
            transaction->outgoingMessageIsReadySignal);

        mScheduler->scheduleTransaction(
            transaction);

    } catch (bad_alloc &) {
        throw MemoryError(
            "TransactionsManager::launchCoordinatorPaymentTransaction: "
                "can't allocate memory for transaction instance.");
    }
}

/*!
 *
 * Throws MemoryError.
 */
void TransactionsManager::launchReceiverPaymentTransaction(
    ReceiverInitPaymentMessage::Shared message) {

    try {
        auto transaction = make_shared<ReceiverPaymentTransaction>(
            message,
            mTrustLines,
            mLog);

        subscribeForOutgoingMessages(
            transaction->outgoingMessageIsReadySignal);

        mScheduler->scheduleTransaction(
            transaction);

    } catch (bad_alloc &) {
        throw MemoryError(
            "TransactionsManager::launchReceiverPaymentTransaction: "
                "can't allocate memory for transaction instance.");
    }
}

/*!
 *
 * Throws MemoryError.
 */
void TransactionsManager::launchRoutingTablePropagationTransaction(
    const NodeUUID &contractorUUID,
    const TrustLineUUID &trustLineUUID) {

    try {

        auto transaction = make_shared<PropagationRoutingTablesTransaction>(
            mNodeUUID,
            contractorUUID,
            trustLineUUID,
            mScheduler.get(),
            mTrustLines
        );

        subscribeForOutgoingMessages(
            transaction->outgoingMessageIsReadySignal);

        mScheduler->postponeTransaction(
            transaction,
            5000);

    } catch (bad_alloc &) {
        throw MemoryError(
            "TransactionsManager::launchRoutingTablePropagationTransaction: "
                "can't allocate memory for transaction instance.");
    }
}

void TransactionsManager::launchAcceptRoutingTablesTransaction(
    FirstLevelRoutingTableIncomingMessage::Shared message) {

    try {

        auto transaction = make_shared<AcceptRoutingTablesTransaction>(
            mNodeUUID,
            message,
            mScheduler.get()
        );

        subscribeForOutgoingMessages(
            transaction->outgoingMessageIsReadySignal);

        mScheduler->scheduleTransaction(
            transaction);

    } catch (bad_alloc &) {
        throw MemoryError(
            "TransactionsManager::launchRoutingTablePropagationTransaction: "
                "can't allocate memory for transaction instance.");
    }
}

void TransactionsManager::subscribeForOutgoingMessages(
    BaseTransaction::SendMessageSignal &signal) {

    signal.connect(
        boost::bind(
            &TransactionsManager::onTransactionOutgoingMessageReady,
            this,
            _1,
            _2)
    );
}

void TransactionsManager::subscribeForCommandResult(
    TransactionsScheduler::CommandResultSignal &signal) {

    signal.connect(
        boost::bind(
            &TransactionsManager::onCommandResultReady,
            this,
            _1
        )
    );
}

void TransactionsManager::onTransactionOutgoingMessageReady(
    Message::Shared message,
    const NodeUUID &contractorUUID) {

    transactionOutgoingMessageReadySignal(
        message,
        contractorUUID);
}

/*!
 * Writes received result to the outgoing results fifo.
 *
 * Throws RuntimeError - in case if result can't be processed.
 */
void TransactionsManager::onCommandResultReady(
    CommandResult::SharedConst result) {

    try {
        auto message = result->serialize();

        mLog->logSuccess(
            "Transactions manager::onCommandResultReady",
            message
        );

        mResultsInterface->writeResult(
            message.c_str(),
            message.size()
        );

    } catch (...) {
        throw RuntimeError(
            "TransactionsManager::onCommandResultReady: "
                "Error occurred when command result has accepted");
    }
}