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
    virtual std::string validateEntry(const CardCredentials&, const std::string&) = 0;

    virtual AccountInfo accountInfo(std::string& token) = 0;

    virtual void putMoney(std::string& token, double amount) = 0;
    virtual void getMoney(std::string& token, double amount) = 0;

    virtual ~IBankService() = default;
};

class TestBank : public IBankService {
private:
    const std::string mockToken = "mock-token";
public:

    TestBank() = default;
    ~TestBank() = default;

    TestBank(const TestBank&) = delete;
    TestBank(TestBank&&) = delete;

    TestBank& operator=(const TestBank&) = delete;
    TestBank& operator=(TestBank&&) = delete;

    bool validateCard(const CardCredentials&) override {
        return true;
    }

    std::string validateEntry(const CardCredentials& creds, const std::string& pin) override {
        if (pin != "1234") throw std::invalid_argument("invalid pin");
        return mockToken;
    }

    AccountInfo accountInfo(std::string& token) override {
        if (token != mockToken) throw std::invalid_argument("Wrong token");
        return AccountInfo{
            200,
            500,
            200
        };
    }

    void putMoney(std::string& token, double amount) override {
        if (token != mockToken) throw std::invalid_argument("Wrong token");
        std::cout << "Added " << amount << " to balance" << std::endl;
    }

    void getMoney(std::string& token, double amount) override {
        if (token != mockToken) throw std::invalid_argument("Wrong token");
        if (amount > 200) throw std::invalid_argument("More than limit");
        std::cout << "Took " << amount << " from to balance" << std::endl;
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

    bool validateCard(const CardCredentials&) override {
        return true;
    }

    std::string validateEntry(const CardCredentials&, const std::string&) override {
        return "";
    }

    AccountInfo accountInfo(std::string& token) override {
        return AccountInfo{
            200,
            500,
            200
        };
    }

    void putMoney(std::string& token, double amount) override {
        std::cout << "Added " << amount << " to balance" << std::endl;
    }

    void getMoney(std::string& token, double amount) override {
        std::cout << "Took " << amount << " from to balance" << std::endl;
    }
};

