#pragma once
#include "BankServices.h"
#include "CardSlot.h"
#include "CashAcceptor.h"
#include "ReceiptPrinter.h"
#include "Dispenser.h"
#include "State.h"
#include "Session.h"
#include "Frequency.h"
#include "LeftOverOption.h"

class ATM
{
private:
    IBankService& _bankService;
    CardSlot _cardSlot;
    CashAcceptor _cashAcceptor;
    ReceiptPrinter _receiptPrinter;
    Dispenser _dispenser;
    State _state = NON_ACTIVE;
    Session* _session = nullptr;

public:
    ATM(IBankService&);
    ~ATM() = default;

    ATM(const ATM&) = delete;
    ATM(ATM&&) = delete;

    ATM& operator=(const ATM&) = delete;
    ATM& operator=(ATM&&) = delete;

    inline void startMaintenance()
    {
        cout << "Start maintance" << endl;
        _state = MAINTENANCE;
    }

    inline void endMaintenance()
    {
        cout << "Ending maintenance" << endl;
        _state = NON_ACTIVE;
    }

    void acceptCard(const json&) const;
    void returnCard();

    void acceptPin(const json&, const string&);

    void printReceipt() const;

    void putMoney(const double&) const;
    void takeMoney(const double&) const;

    AccountInfo showInfo() const;
    // void showDpositInfo();
    // void showLeftOverInfo();

    // void putOnDeposit(const double&);
    void transferMoney(const double&, const string&) const;

    // void createAutoTransfer(const double&, const string&, const Frequency&);
    // void setLeftOverHandling(const LeftOverOption&, const Frequency&);
};
