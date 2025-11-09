#include "BankServices.h"

bool PolyBank::validateCard(const CardCredentials& creds) {
    return true;
}

std::string PolyBank::validateEntry(const CardCredentials& creds, const string& pin) {
    return "";
}

AccountInfo PolyBank::accountInfo(string& token) {
    return {
        0,0,0
    };
}

void PolyBank::putMoney(string& token, double amount) {

}

void PolyBank::getMoney(string& token, double amount) {

}
