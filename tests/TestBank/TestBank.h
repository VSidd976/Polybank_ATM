#pragma once
#include "ATM.h"

class TestBank : public IBankService
{
private:
    const string mockToken = "mock-token";
    const string mockNumber = "4556727619519847";
    vector<DepositInfo> _myDeposits;
    vector<DepositProductInfo> _depositProducts;
    vector<CreditInfo> _myCredits;
    vector<CreditProductInfo> _creditProducts;
    vector<CreditProtectionInfo> _myCreditProtections;
    vector<LeftOverInfo> _myLeftOvers;
    vector<AutoTransferinfo> _myAutoTransfers;

public:
    TestBank() = default;
    ~TestBank() = default;

    TestBank(const TestBank&) = delete;
    TestBank(TestBank&&) = delete;

    TestBank& operator=(const TestBank&) = delete;
    TestBank& operator=(TestBank&&) = delete;

    bool validateCard(const CardCredentials&) override;
    string validateEntry(const CardCredentials&, const string&) override;

    AccountInfo accountInfo(const string&) override;

    void putMoney(const string&, const double&) override;
    void getMoney(const string&, const double&) override;
    void transferMoney(const string&, const string&, const double&) override;

    vector<DepositInfo> allDeposits(const string&) override;
    vector<DepositProductInfo> allDepositProducts(const string&) override;

    void putOnDeposit(const string&, const int&, const double&) override;
    void takeFromDeposit(const string&, const int&) override;

    vector<CreditInfo> allCredits(const string&) override;
    vector<CreditProductInfo> allCreditProducts(const string&) override;

    vector<CreditProtectionInfo> allCreditProtections(const string&) override;

    void createCreditProtection(const string&, const double&) override;
    void deleteCreditProtection(const string&, const int&) override;

    void takeCredit(const string&, const int&, const double&) override;
    void payCredit(const string&, const int&, const double&) override;

    vector<LeftOverInfo> allLeftOvers(const string&) override;

    void createLeftOver(const string&, const string&, const double&) override;
    void deleteLeftOver(const string&, const int&) override;

    vector<AutoTransferinfo> allAutoTransfers(const string&) override;

    void createAutoTransfer(const string&, const string&, const string&, const string&, const double&) override;
    void deleteAutoTransfer(const string&, const int&) override;
};
