#pragma once
#include "ATM.h"

class TestBank : public IBankService
{
private:
    const string mockToken = "mock-token";
    const string mockNumber = "4556727619519847";
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
};
