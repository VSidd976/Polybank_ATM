#include "BankServices.h"

bool PolyBank::validateCard(const CardCredentials& creds) {
    return true;
}

string PolyBank::validateEntry(const CardCredentials& creds, const string& pin) {

    return "";
}

AccountInfo PolyBank::accountInfo(string& token) {
    return {
        0,0,0
    };
}

void PolyBank::putMoney(string& token, const double& amount) {

}

void PolyBank::getMoney(string& token, const double& amount) {

}
