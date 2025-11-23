#include "BankServices.h"

string parseJsonEnv(const string& path)
{
    ifstream inputFile(path);
    json data;
    if (!inputFile.is_open())
    {
        throw BadOperation("Bad opening", "could not open file");
    }
    inputFile >> data;
    return data["SERVER_ADDRESS"];
}

PolyBank::PolyBank(const string& path): _baseUrl(parseJsonEnv(path)) {}

bool PolyBank::validateCard(const CardCredentials& creds)
{
    json body;
    body["card"] = creds._cardNumber;
    cout << "SENDING REQ" << endl;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/auth/verify-card" },
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
        cpr::Url{ _baseUrl + "/api/auth/verify-credentials" },
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
    auto data = json::parse(r.text).at("deposits");
    vector<DepositInfo> deposits(data.size());
    for (int i = 0; i < data.size(); ++i)
    {
        deposits[i]._opened_at = data[i]["opened_at"];
        deposits[i]._closed_at = data[i]["closed_at"];
        deposits[i]._balance = data[i]["amount"];
        deposits[i]._product_id = data[i]["product_id"];
    }
    return deposits;
}

vector<DepositProductInfo> PolyBank::allDepositProducts(const string& token)
{
    cout << "SENDING REQ" << endl;
    cpr::Response r = cpr::Get(
        cpr::Url{ _baseUrl + "/api/deposit/products" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}}
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
    cout << "SENT" << endl;
    auto data = json::parse(r.text).at("deposit_products");
    vector<DepositProductInfo> depositProducts(data.size());
    for (int i = 0; i < data.size(); ++i)
    {
        depositProducts[i]._name = data[i]["name"];
        depositProducts[i]._interest_rate = data[i]["interest_rate"];
        depositProducts[i]._term_months = data[i]["term_months"];
        depositProducts[i]._id = data[i]["id"];
    }
    return depositProducts;
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
