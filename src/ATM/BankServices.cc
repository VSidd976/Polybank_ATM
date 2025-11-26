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
        deposits[i]._id = data[i]["id"];
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

void PolyBank::putOnDeposit(const string& token, const int& product_id, const double& amount)
{
    json body;
    body["product_id"] = product_id;
    body["amount"] = amount;
    cout << body << endl;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/deposit/put" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
}

void PolyBank::takeFromDeposit(const string& token, const int& product_id)
{
    json body;
    body["deposit_id"] = product_id;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/deposit/put" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
}

vector<CreditInfo> PolyBank::allCredits(const string& token)
{
    cout << "SENDING REQ" << endl;
    cpr::Response r = cpr::Get(
        cpr::Url{ _baseUrl + "/api/credit" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}}
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
    cout << "SENT" << endl;
    auto data = json::parse(r.text).at("credits");
    vector<CreditInfo> credits(data.size());
    cout << data << endl;
    for (int i = 0; i < data.size(); ++i)
    {
        credits[i]._opened_at = data[i]["opened_at"];
        credits[i]._closed_at = data[i]["closed_at"];
        credits[i]._product_name = data[i]["product_name"];
        credits[i]._amount = data[i]["amount"];
        credits[i]._remaining_amount = data[i]["remaining_amount"];
        credits[i]._interest_accured = data[i]["interest_accured"];
        credits[i]._product_id = data[i]["product_id"];
        credits[i]._id = data[i]["id"];
    }
    return credits;
}

vector<CreditProductInfo> PolyBank::allCreditProducts(const string& token)
{
    cout << "SENDING REQ" << endl;
    cpr::Response r = cpr::Get(
        cpr::Url{ _baseUrl + "/api/credit/products" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}}
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
    cout << "SENT" << endl;
    auto data = json::parse(r.text).at("credit_products");
    vector<CreditProductInfo> creditProducts(data.size());
    for (int i = 0; i < data.size(); ++i)
    {
        creditProducts[i]._name = data[i]["name"];
        creditProducts[i]._interest_rate = data[i]["interest_rate"];
        creditProducts[i]._term_months = data[i]["term_months"];
        creditProducts[i]._id = data[i]["id"];
    }
    return creditProducts;
}

void PolyBank::takeCredit(const string& token, const int& product_id, const double& amount)
{
    json body;
    body["product_id"] = product_id;
    body["amount"] = amount;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/credit/take" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
}

void PolyBank::payCredit(const string& token, const int& product_id, const double& amount)
{
    json body;
    body["credit_id"] = product_id;
    body["amount"] = amount;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/credit/pay" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
}

vector<CreditProtectionInfo> PolyBank::allCreditProtections(const string& token)
{
    cout << "SENDING REQ" << endl;
    cpr::Response r = cpr::Get(
        cpr::Url{ _baseUrl + "/api/daemon/credit-protection" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}}
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
    cout << "SENT" << endl;
    auto data = json::parse(r.text).at("credit_protection_rules");
    vector<CreditProtectionInfo> creditProtections(data.size());
    for (int i = 0; i < data.size(); ++i)
    {
        creditProtections[i]._backup_card = data[i]["backup_card"];
        creditProtections[i]._min_balance = data[i]["min_balance"];
        creditProtections[i]._id = data[i]["id"];
        creditProtections[i]._active = data[i]["active"];
    }
    return creditProtections;
}

void PolyBank::createCreditProtection(const string& token, const double& amount)
{
    json body;
    body["amount"] = amount;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/daemon/credit-protection" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
}

void PolyBank::deleteCreditProtection(const string& token, const int& id)
{
    json body;
    body["id"] = id;
    cpr::Response r = cpr::Delete(
        cpr::Url{ _baseUrl + "/api/daemon/credit-protection/" + to_string(id) },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
}

vector<LeftOverInfo> PolyBank::allLeftOvers(const string& token)
{
    cout << "SENDING REQ" << endl;
    cpr::Response r = cpr::Get(
        cpr::Url{ _baseUrl + "/api/daemon/leftover-rule" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}}
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
    cout << "SENT" << endl;
    auto data = json::parse(r.text).at("leftover_rules");
    vector<LeftOverInfo> leftOvers(data.size());
    for (int i = 0; i < data.size(); ++i)
    {
        leftOvers[i]._target_card = data[i]["trg_card"];
        leftOvers[i]._threshold = data[i]["threshold"];
        leftOvers[i]._id = data[i]["id"];
        leftOvers[i]._active = data[i]["active"];
    }
    return leftOvers;
}

void PolyBank::createLeftOver(const string& token, const string& target_card, const double& threshold)
{
    json body;
    body["trg_card"] = target_card;
    body["threshold"] = threshold;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/daemon/leftover-rule" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
}

void PolyBank::deleteLeftOver(const string& token, const int& id)
{
    json body;
    body["id"] = id;
    cpr::Response r = cpr::Delete(
        cpr::Url{ _baseUrl + "/api/daemon/leftover-rule/" + to_string(id) },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
}

vector<AutoTransferinfo> PolyBank::allAutoTransfers(const string& token)
{
    cout << "SENDING REQ" << endl;
    cpr::Response r = cpr::Get(
        cpr::Url{ _baseUrl + "/api/daemon/auto-transfer" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}}
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
    cout << "SENT" << endl;
    auto data = json::parse(r.text).at("auto_transfers");
    vector<AutoTransferinfo> autoTransfers(data.size());
    for (int i = 0; i < data.size(); ++i)
    {
        autoTransfers[i]._target_card = data[i]["trg_card"];
        autoTransfers[i]._frequency = data[i]["periodicity"];
        autoTransfers[i]._next_date = data[i]["next_run_date"];
        autoTransfers[i]._amount = data[i]["amount"];
        autoTransfers[i]._id = data[i]["id"];
        autoTransfers[i]._active = data[i]["active"];
    }
    return autoTransfers;
}

void PolyBank::createAutoTransfer(const string& token, const string& target_card, const string& frequency, const double& amount)
{
    json body;
    body["trg_card"] = target_card;
    body["periodicity"] = frequency;
    body["amount"] = amount;
    cpr::Response r = cpr::Post(
        cpr::Url{ _baseUrl + "/api/daemon/auto-transfer" },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
}

void PolyBank::deleteAutoTransfer(const string& token, const int& id)
{
    json body;
    body["id"] = id;
    cpr::Response r = cpr::Delete(
        cpr::Url{ _baseUrl + "/api/daemon/auto-transfer/" + to_string(id) },
        cpr::Header{{"Authorization", "Bearer " + token}, {"Accept", "application/json"}},
        cpr::Body{ body.dump() }
    );
    if (r.status_code != 200)
    {
        cout << "ERROR " << r.status_code << endl;
        throw BadOperation("Bad request", r.text);
    }
}
