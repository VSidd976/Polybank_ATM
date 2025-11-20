#include "BankServices.h"

string parseJsonEnv()
{
    string path = "../../env.json";
    ifstream inputFile(path);
    json data;
    if (!inputFile.is_open())
    {
        throw BadOperation("Bad opening", "could not open file");
    }
    inputFile >> data;
    return data["SERVER_ADDRESS"];
}

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

vector<DepositInfo> PolyBank::allDeposits(const string& token)
{
    cout << "SENDING REQ" << endl;
    cpr::Response r = cpr::Get(
        cpr::Url{ _baseUrl + "/api/deposit" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}}
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
    cout << "SENT" << endl;
    auto data = json::parse(r.text);
    vector<DepositInfo> deposits;
    for (int i = 0; i < data.size(); ++i)
    {
        deposits[i]._opened_at = data[i].at("opened_at");
        deposits[i]._closed_at = data[i].at("closed_at");
        deposits[i]._number = data[i].at("product_id");
        deposits[i]._balance = data[i].at("amount");
    }
    return deposits;
}

DepositInfo PolyBank::depositInfo(const string& number)
{
    cout << "SENDING REQ" << endl;
    cpr::Response r = cpr::Get(
        cpr::Url{ _baseUrl + "/api/deposit" },
        cpr::Header{{"Authorization", "Bearer " + number}, {"Accept", "application/json"}}
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
    auto data = json::parse(r.text);
    return {
        data.at("opened_at"),
        data.at("clossed_at"),
        data.at("number"),
        data.at("balance")
    };
}

void PolyBank::putOnDeposit(const string& number, const double& amount)
{
    json body;
    body["amount"] = amount;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/deposit/put" },
        cpr::Header{{"Authorization", "Bearer " + number}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
}
