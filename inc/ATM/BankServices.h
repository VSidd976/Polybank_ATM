#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "CardCredentials.h"
#include "BadOperation.h"
#include "Info.h"

using namespace nlohmann;

string parseJsonEnv(const string&);

class IBankService
{
public:
    virtual bool validateCard(const CardCredentials&) = 0;
    virtual string validateEntry(const CardCredentials&, const string&) = 0;

    virtual AccountInfo accountInfo(const string&) = 0;

    virtual void putMoney(const string&, const double&) = 0;
    virtual void getMoney(const string&, const double&) = 0;
    virtual void transferMoney(const string&, const string&, const double&) = 0;

    virtual vector<DepositInfo> allDeposits(const string&) = 0;
    virtual vector<DepositProductInfo> allDepositProducts(const string&) = 0;

    virtual void putOnDeposit(const string&, const int&, const double&) = 0;
    virtual void takeFromDeposit(const string&, const int&) = 0;

    virtual vector<CreditInfo> allCredits(const string&) = 0;
    virtual vector<CreditProductInfo> allCreditProducts(const string&) = 0;

    virtual void takeCredit(const string&, const int&, const double&) = 0;
    virtual void payCredit(const string&, const int&, const double&) = 0;

    virtual vector<CreditProtectionInfo> allCreditProtections(const string&) = 0;

    virtual void createCreditProtection(const string&, const double&) = 0;
    virtual void deleteCreditProtection(const string&, const int&) = 0;

    virtual vector<LeftOverInfo> allLeftOvers(const string&) = 0;

    virtual void createLeftOver(const string&, const string&, const double&) = 0;
    virtual void deleteLeftOver(const string&, const int&) = 0;

    virtual vector<AutoTransferinfo> allAutoTransfers(const string&) = 0;

    virtual void createAutoTransfer(const string&, const string&, const string&, const string&, const double&) = 0;
    virtual void deleteAutoTransfer(const string&, const int&) = 0;

    virtual ~IBankService() = default;
};

class PolyBank : public IBankService
{
private:
    string _baseUrl;
public:
    PolyBank() = default;
    ~PolyBank() = default;

    PolyBank(const string&);

    PolyBank(const PolyBank&) = delete;
    PolyBank(PolyBank&&) = delete;

    PolyBank& operator=(const PolyBank&) = delete;
    PolyBank& operator=(PolyBank&&) = delete;

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

    void takeCredit(const string&, const int&, const double&) override;
    void payCredit(const string&, const int&, const double&) override;

    vector<CreditProtectionInfo> allCreditProtections(const string&) override;

    void createCreditProtection(const string&, const double&) override;
    void deleteCreditProtection(const string&, const int&) override;

    vector<LeftOverInfo> allLeftOvers(const string&) override;

    void createLeftOver(const string&, const string&, const double&) override;
    void deleteLeftOver(const string&, const int&) override;

    vector<AutoTransferinfo> allAutoTransfers(const string&) override;

    void createAutoTransfer(const string&, const string&, const string&, const string&, const double&) override;
    void deleteAutoTransfer(const string&, const int&) override;
};
