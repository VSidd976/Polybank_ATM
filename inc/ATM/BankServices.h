#pragma once
#include <exception>
#include <iostream>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "CardCredentials.h"

using namespace nlohmann;

struct AccountInfo
{
    double _balance;
    double _creditLimit;
    double _depositBalance;
};

class IBankService
{
public:
    virtual string validateEntry(const CardCredentials&, const string&) = 0;

    virtual AccountInfo accountInfo(const string&) = 0;

    virtual void putMoney(const string&, const double&) = 0;
    virtual void getMoney(const string&, const double&) = 0;
    virtual void transferMoney(const string&, const string&, const double&) = 0;

    virtual ~IBankService() = default;
};

class PolyBank : public IBankService
{
private:
    string _baseUrl = "http://16.170.29.95:18973";
public:
    PolyBank() = default;
    ~PolyBank() = default;

    PolyBank(const PolyBank&) = delete;
    PolyBank(PolyBank&&) = delete;

    PolyBank& operator=(const PolyBank&) = delete;
    PolyBank& operator=(PolyBank&&) = delete;

    string validateEntry(const CardCredentials&, const string&) override;

    AccountInfo accountInfo(const string&) override;

    void putMoney(const string&, const double&) override;

    void getMoney(const string&, const double&) override;

    void transferMoney(const string&, const string&, const double&) override;
};
