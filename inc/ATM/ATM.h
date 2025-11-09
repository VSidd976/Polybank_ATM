#pragma once
#include <iostream>
#include "nlohmann/json.hpp"
#include "BankServices.h"
#include "CardSlot.h"
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
    ReceiptPrinter _receiptPrinter;
    Dispenser _dispenser;
    State _state = NON_ACTIVE;
    Session* _session = nullptr;

public:
    ATM(IBankService& bankService): _bankService(bankService) {};
    ~ATM() = default;

    ATM(const ATM&) = delete;
    ATM(ATM&&) = delete;

    ATM& operator=(const ATM&) = delete;
    ATM& operator=(ATM&&) = delete;

    void startMaintenance() {
        std::cout << "Start maintance" << std::endl;
        _state = MAINTENANCE;
    }
    void endMaintenance() {
        _state = NON_ACTIVE;
    }

    void acceptCard(const json&);
    void returnCard();

    void acceptPin(const json&, const string&);

    void printReceipt();

    void putMoney(const double&);
    void takeMoney(const double&);

    AccountInfo showInfo() const;
    // void showDpositInfo();
    // void showLeftOverInfo();

    // void putOnDeposit(const double&);
    void transferMoney(const double&, const string&);

    // void createAutoTransfer(const double&, const string&, const Frequency&);
    // void setLeftOverHandling(const LeftOverOption&, const Frequency&);
};
