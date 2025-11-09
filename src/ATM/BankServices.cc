#include "BankServices.h"

bool PolyBank::validateCard(const CardCredentials& creds) {
    return true;
}

string PolyBank::validateEntry(const CardCredentials& creds, const string& pin) {

    return "";
}

AccountInfo PolyBank::accountInfo(const string& token) {
    return {
        0,0,0
    };
}

void PolyBank::putMoney(const string& token, double amount) {

}

void PolyBank::getMoney(const string& token, double amount) {

}
