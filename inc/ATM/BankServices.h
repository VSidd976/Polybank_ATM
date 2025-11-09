#pragma once
#include <string>
#include <exception>
#include <iostream>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "CardCredentials.h"

using namespace nlohmann;

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
    virtual void transferMoney(string& token, const double& amount) = 0;

    virtual ~IBankService() = default;
};

class TestBank : public IBankService {
private:
    const string mockToken = "mock-token";
    const string milTocken = "mil-tocken";
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

    inline void transferMoney(string& token, const double& amount) override {
        if (token != milTocken) throw invalid_argument("Wrong tocken");
        if (amount > 200) throw invalid_argument("More than limit");
        cout << "Transfered " << amount << " to " << token << " balance" << endl;
    }
};

class PolyBank : public IBankService {
private:
    string baseUrl = "http://16.170.29.95:18973";
public:
    PolyBank() = default;
    ~PolyBank() = default;

    PolyBank(const PolyBank&) = delete;
    PolyBank(PolyBank&&) = delete;

    PolyBank& operator=(const PolyBank&) = delete;
    PolyBank& operator=(PolyBank&&) = delete;

    bool validateCard(const CardCredentials&) override {
        return true;
    }

    string validateEntry(const CardCredentials&, const string&) override {
        return "";
    }

    AccountInfo accountInfo(string& token) override {
        return {
            0,0,0
        };
    }

    void putMoney(string& token, const double& amount) override {
        nlohmann::json body;
        body["amount"] = amount;
        cpr::Response r = cpr::Post(
            cpr::Url{ baseUrl + "/api/account/put" },
            cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
            cpr::Body{ body.dump() }
        );
        if (r.status_code != 200) {
            throw std::runtime_error("Failed to put money: " + r.text);
        }
    }

    void getMoney(string& token, const double& amount) override {

    }

    inline void transferMoney(string& token, const double& amount) override {

    }
};
