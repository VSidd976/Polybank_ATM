#pragma once
#include <string>
#include <exception>
#include <iostream>
#include "CardCredentials.h"

struct AccountInfo {
    double balance;
    double creditLimit;
    double depositBalance;
};

class IBankService {
public:
    virtual bool validateCard(const CardCredentials&) = 0;
    virtual string validateEntry(const CardCredentials&, const string&) = 0;

    virtual AccountInfo accountInfo(string& token) = 0;

    virtual void putMoney(string& token, const double& amount) = 0;
    virtual void getMoney(string& token, const double& amount) = 0;
    virtual void trasnferMoney(string& token, const double& amount) = 0;

    virtual ~IBankService() = default;
};

class TestBank : public IBankService {
private:
    const string mockToken = "mock-token";
public:

    TestBank() = default;
    ~TestBank() = default;

    TestBank(const TestBank&) = delete;
    TestBank(TestBank&&) = delete;

    TestBank& operator=(const TestBank&) = delete;
    TestBank& operator=(TestBank&&) = delete;

    inline bool validateCard(const CardCredentials&) override {
        return true;
    }

    inline string validateEntry(const CardCredentials& creds, const string& pin) override {
        if (pin != "1234") throw invalid_argument("invalid pin");
        return mockToken;
    }

    inline AccountInfo accountInfo(string& token) override {
        if (token != mockToken) throw invalid_argument("Wrong token");
        return AccountInfo{
            200,
            500,
            200
        };
    }

    inline void putMoney(string& token, const double& amount) override {
        if (token != mockToken) throw invalid_argument("Wrong token");
        cout << "Added " << amount << " to balance" << endl;
    }

    inline void getMoney(string& token, const double& amount) override {
        if (token != mockToken) throw invalid_argument("Wrong token");
        if (amount > 200) throw invalid_argument("More than limit");
        cout << "Took " << amount << " from to balance" << endl;
    }
};

class PolyBank : public IBankService {
public:
    PolyBank() = default;
    ~PolyBank() = default;

    PolyBank(const PolyBank&) = delete;
    PolyBank(PolyBank&&) = delete;

    PolyBank& operator=(const PolyBank&) = delete;
    PolyBank& operator=(PolyBank&&) = delete;

    bool validateCard(const CardCredentials&) override;

    string validateEntry(const CardCredentials&, const string&) override;

    AccountInfo accountInfo(string& token) override;

    void putMoney(string& token, double amount) override;

    void getMoney(string& token, double amount) override;
};
