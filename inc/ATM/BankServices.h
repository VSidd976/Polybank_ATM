#pragma once
#include <string>
#include "CardCredentials.h"

struct AccountInfo {
    double balance;
    double creditLimit;
    double depositBalance;
};

class IBankService {
    virtual bool validateCard(CardCredentials) = 0;
    virtual std::string validateEntry(CardCredentials, std::string) = 0;

    virtual AccountInfo accountInfo(std::string& token) = 0;

    virtual void putMoney(std::string& token, double amount) = 0;
    virtual void getMoney(std::string& token, double amount) = 0;

    virtual ~IBankService() = default;
};
