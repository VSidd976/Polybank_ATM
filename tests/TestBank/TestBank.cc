#include "TestBank.h"

bool TestBank::validateCard(const CardCredentials& creds)
{
    return true;
}

string TestBank::validateEntry(const CardCredentials& creds, const string& pin)
{
    if (pin != "1234")
    {
        throw BadOperation("Bad validation", "invalid pin");
    }
    return mockToken;
}

AccountInfo TestBank::accountInfo(const string& token)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid tocken");
    }
    return AccountInfo { 200 };
}

void TestBank::putMoney(const string& token, const double& amount)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid tocken");
    }
}

void TestBank::getMoney(const string& token, const double& amount)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid tocken");
    }
    if (amount > 200)
    {
        throw BadOperation("Bad request", "more than limit");
    }
}

void TestBank::transferMoney(const string& token, const string& number, const double& amount)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid tocken");
    }
    if (number != mockNumber)
    {
        throw BadOperation("Bad request", "invalid number");
    }
}

vector<DepositInfo> TestBank::allDeposits(const string& token)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid tocken");
    }
    return _myDeposits;
}

vector<DepositProductInfo> TestBank::allDepositProducts(const string& token)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid tocken");
    }
    return _depositProducts;
}

void TestBank::putOnDeposit(const string& token, const int& product_id, const double& amount)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid tocken");
    }
    if (product_id < 1 || product_id > 3)
    {
        throw BadOperation("Bad request", "invalid product id");
    }
}

void TestBank::takeFromDeposit(const string& token, const int& id)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid tocken");
    }
    if (id < 1)
    {
        throw BadOperation("Bad request", "invalid id");
    }
}

vector<CreditInfo> TestBank::allCredits(const string& token)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid token");
    }
    return _myCredits;
}

vector<CreditProductInfo> TestBank::allCreditProducts(const string& token)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid token");
    }
    return _creditProducts;
}

void TestBank::takeCredit(const string& token, const int& product_id, const double& amount)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid token");
    }
    if (product_id < 1 || product_id > 3)
    {
        throw BadOperation("Bad request", "invalid product id");
    }
}

void TestBank::payCredit(const string& token, const int& id, const double& amount)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid token");
    }
    if (id < 1)
    {
        throw BadOperation("Bad request", "invalid id");
    }
}

vector<CreditProtectionInfo> TestBank::allCreditProtections(const string& token)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid token");
    }
    return _myCreditProtections;
}

void TestBank::createCreditProtection(const string& token, const double& threshold)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid token");
    }
}

void TestBank::deleteCreditProtection(const string& token, const int& id)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid token");
    }
    if (id < 1)
    {
        throw BadOperation("Bad request", "invalid id");
    }
}

vector<LeftOverInfo> TestBank::allLeftOvers(const string& token)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid token");
    }
    return _myLeftOvers;
}

void TestBank::createLeftOver(const string& token, const string& target_card, const double& threshold)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid token");
    }
    if (target_card != mockNumber)
    {
        throw BadOperation("Bad request", "invalid number");
    }
}

void TestBank::deleteLeftOver(const string& token, const int& id)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid token");
    }
    if (id < 1)
    {
        throw BadOperation("Bad request", "invalid id");
    }
}

vector<AutoTransferinfo> TestBank::allAutoTransfers(const string& token)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid token");
    }
    return _myAutoTransfers;
}

void TestBank::createAutoTransfer(const string& token, const string& target_card,
    const string& frequency, const string& next_date, const double& amount)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid token");
    }
    if (target_card != mockNumber)
    {
        throw BadOperation("Bad request", "invalid number");
    }
    if (frequency != "once" && frequency != "weekly" && frequency != "monthly")
    {
        throw BadOperation("Bad request", "invalid frequency");
    }
    if (next_date != "tommorrow" && next_date != "next_week" && next_date != "next_month")
    {
        throw BadOperation("Bad request", "invalid next date");
    }
}

void TestBank::deleteAutoTransfer(const string& token, const int& id)
{
    if (token != mockToken)
    {
        throw BadOperation("Bad validation", "invalid token");
    }
    if (id < 1)
    {
        throw BadOperation("Bad request", "invalid id");
    }
}
