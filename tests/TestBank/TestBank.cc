#include "TestBank.h"

string TestBank::validateEntry(const CardCredentials& creds, const string& pin) {
    if (pin != "1234") throw invalid_argument("invalid pin");
    return mockToken;
}

AccountInfo TestBank::accountInfo(const string& token) {
    if (token != mockToken) throw invalid_argument("Wrong token");
    return AccountInfo {
        200,
        500,
        200
    };
}

void TestBank::putMoney(const string& token, const double& amount) {
    if (token != mockToken) throw invalid_argument("Wrong token");
    cout << "Added " << amount << " to balance" << endl;
}

void TestBank::getMoney(const string& token, const double& amount) {
    if (token != mockToken) throw invalid_argument("Wrong token");
    if (amount > 200) throw invalid_argument("More than limit");
    cout << "Took " << amount << " from to balance" << endl;
}

void TestBank::transferMoney(const string& token, const string& number, const double& amount) {
    if (token != mockToken) throw invalid_argument("Wrong tocken");
    if (number != mockNumber) throw invalid_argument("Wrong number");
    if (amount > 200) throw invalid_argument("More than limit");
    cout << "Transfered " << amount << " to " << token << " balance" << endl;
}
