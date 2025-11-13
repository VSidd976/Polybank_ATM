#include "BankServices.h"

string PolyBank::validateEntry(const CardCredentials& creds, const string& pin) {
    json body;
    body["card"] = creds._cardNumber;
    body["pin"] = pin;
    cout << "SENDING REQ" << endl;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/auth/verify-credentials" },
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200) {
        cout << "ERROR " << r.status_code << endl;
        throw runtime_error("Failed to validate: " + r.text);
    }
    cout << "SENT" << endl;
    auto data = nlohmann::json::parse(r.text);
    return data.at("token");
}

AccountInfo PolyBank::accountInfo(const string& token) {
    cout << "SENDING REQ" << endl;
    cpr::Response r = cpr::Get(
        cpr::Url{ _baseUrl + "/api/account" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}}
    );
    if (r.status_code != 200) {
        cout << "ERROR " << r.status_code << endl;
        throw runtime_error("Failed to show info: " + r.text);
    }
    cout << "SENT" << endl;
    auto data = json::parse(r.text);
    return {
        data.at("balance"),
        0,
        0
    };
}

void PolyBank::putMoney(const string& token, const double& amount) {
    json body;
    body["amount"] = amount;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/account/put" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200) {
        throw runtime_error("Failed to put money: " + r.text);
    }
}

void PolyBank::getMoney(const string& token, const double& amount) {
    json body;
    body["amount"] = amount;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/account/take" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200) {
        throw runtime_error("Failed to get money: " + r.text);
    }
}

void PolyBank::transferMoney(const string& token, const string& number, const double& amount) {
    json body;
    body["to"] = number;
    body["amount"] = amount;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/account/transfer" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200) {
        throw runtime_error("Failed to transfer money: " + r.text);
    }
}
