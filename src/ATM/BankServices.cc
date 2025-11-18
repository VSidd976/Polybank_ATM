#include "BankServices.h"

bool PolyBank::validateCard(const CardCredentials& creds)
{
    json body;
    body["card"] = creds._cardNumber;
    cout << "SENDING REQ" << endl;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/auth/verify-credentials-without-pin" },
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad validation", r.text);
    }
    cout << "SENT" << endl;
    return true;
}

string PolyBank::validateEntry(const CardCredentials& creds, const string& pin)
{
    json body;
    body["card"] = creds._cardNumber;
    body["pin"] = pin;
    cout << "SENDING REQ" << endl;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/auth/verify-credentials-with-pin" },
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad validation", r.text);
    }
    cout << "SENT" << endl;
    auto data = nlohmann::json::parse(r.text);
    return data.at("token");
}

AccountInfo PolyBank::accountInfo(const string& token)
{
    cout << "SENDING REQ" << endl;
    cpr::Response r = cpr::Get(
        cpr::Url{ _baseUrl + "/api/account" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}}
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
    cout << "SENT" << endl;
    auto data = json::parse(r.text);
    return { data.at("balance") };
}

void PolyBank::putMoney(const string& token, const double& amount)
{
    json body;
    body["amount"] = amount;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/account/put" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
}

void PolyBank::getMoney(const string& token, const double& amount)
{
    json body;
    body["amount"] = amount;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/account/take" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
}

void PolyBank::transferMoney(const string& token, const string& number, const double& amount)
{
    json body;
    body["to"] = number;
    body["amount"] = amount;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/account/transfer" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
}
