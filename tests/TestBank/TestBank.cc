#include "TestBank.h"

bool TestBank::validateCard(const CardCredentials& creds)
{
    return true;
}

string TestBank::validateEntry(const CardCredentials& creds, const string& pin)
{
    if (pin != "1234")
    {
        throw BadOperation("Invalid argument", "Invalid pin");
    }
    return mockToken;
}

AccountInfo TestBank::accountInfo(const string& token)
{
    if (token != mockToken)
    {
        throw BadOperation("Invalid argument", "Invalid tocken");
    }
    return AccountInfo { 200 };
}

void TestBank::putMoney(const string& token, const double& amount)
{
    if (token != mockToken)
    {
        throw BadOperation("Invalid argument", "Invalid tocken");
    }
    cout << "Added " << amount << " to balance" << endl;
}

void TestBank::getMoney(const string& token, const double& amount)
{
    if (token != mockToken)
    {
        throw BadOperation("Invalid argument", "Invalid tocken");
    }
    if (amount > 200)
    {
        throw BadOperation("Invalid request", "More than limit");
    }
    cout << "Took " << amount << " from to balance" << endl;
}

void TestBank::transferMoney(const string& token, const string& number, const double& amount)
{
    if (token != mockToken)
    {
        throw BadOperation("Invalid argument", "Invalid tocken");
    }
    if (number != mockNumber)
    {
        throw BadOperation("Invalid argument", "Invalid number");
    }
    if (amount > 200)
    {
        throw BadOperation("Invalid request", "More than limit");
    }
    cout << "Transfered " << amount << " to " << token << " balance" << endl;
}

vector<DepositInfo> TestBank::allDeposits(const string& token)
{
    if (token != mockToken)
    {
        throw BadOperation("Invalid argument", "Invalid tocken");
    }
    return _myDeposits;
}

vector<DepositProductInfo> TestBank::allDepositProducts(const string& token)
{
    if (token != mockToken)
    {
        throw BadOperation("Invalid argument", "Invalid tocken");
    }
    return _depositProducts;
}

void TestBank::putOnDeposit(const string& token, const int& product_id, const double& amount)
{
    if (token != mockToken)
    {
        throw BadOperation("Invalid argument", "Invalid tocken");
    }
    _myDeposits.push_back({"now", "never", amount, product_id});
}

void TestBank::takeFromDeposit(const string& token, const int& id)
{
    if (token != mockToken)
    {
        throw BadOperation("Invalid argument", "Invalid tocken");
    }
    _myDeposits.pop_back();
}
