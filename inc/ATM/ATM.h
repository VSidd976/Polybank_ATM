#pragma once
#include "BankServices.h"
#include "CardSlot.h"
#include "CashAcceptor.h"
#include "ReceiptPrinter.h"
#include "Dispenser.h"
#include "CashStorage.h"
#include "State.h"
#include "Session.h"

class ATM
{
private:
    IBankService& _bankService;
    CardSlot _cardSlot;
    CashAcceptor _cashAcceptor;
    ReceiptPrinter _receiptPrinter;
    Dispenser _dispenser;
    CashStorage _cashStorage;
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
        cout << "End maintenance" << endl;
        _state = NON_ACTIVE;
    }

    inline const double& getCashInfo() { return _cashStorage._amount; }

    void acceptCard(const json&) const;
    void returnCard();

    void acceptPin(const json&, const string&);

    void printReceipt() const;

    void putMoney(const double&);
    void takeMoney(const double&);

    AccountInfo getInfo() const;

    vector<DepositInfo> getAllDeposits() const;
    vector<DepositProductInfo> getAllDepositProducts() const;

    void putOnDeposit(const int&, const double&) const;
    void takeFromDeposit(const int&) const;
    void transferMoney(const double&, const string&) const;

    vector<CreditInfo> getAllCredits() const;
    vector<CreditProductInfo> getAllCreditProducts() const;

    void takeCredit(const int&, const double&) const;
    void payCredit(const int&, const double&) const;

    vector<CreditProtectionInfo> getAllCreditProtections() const;

    void createCreditProtection(const double&) const;
    void deleteCreditProtection(const int&) const;

    vector<LeftOverInfo> getAllLeftOvers() const;

    void createLeftOver(const string&, const double&) const;
    void deleteLeftOver(const int&) const;

    vector<AutoTransferinfo> getAllAutoTransfers() const;

    void createAutoTransfer(const string&, const string&, const string&, const double&) const;
    void deleteAutoTransfer(const int&) const;
};
