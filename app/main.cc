#include <crow.h>
#include "crow/middlewares/cors.h"
#include <nlohmann/json.hpp>
#include "ATM.h"
using namespace nlohmann;

int main()
{
    crow::App<crow::CORSHandler> app;
    PolyBank polyBank("../../env.json");
    ATM atm(polyBank);

    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors.global()
        .origin("*")
        .methods("POST"_method, "GET"_method, "PUT"_method, "OPTIONS"_method)
        .headers("Content-Type", "X-Custom-Header");

    CROW_ROUTE(app, "/card/accept")
    .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req){
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        const json data = json::parse(req.body);
        crow::response res;
        try
        {
            atm.acceptCard(data);
            res.code = 200;
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/card/pin")
    .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req){
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        const json data = json::parse(req.body);
        const string pin = data["pin"];
        crow::response res;
        try
        {
            atm.acceptPin(data, pin);
            res.code = 200;
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/card/return")
    .methods(crow::HTTPMethod::PUT, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req){
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        atm.returnCard();
        crow::response res(200);
        return res;
    });

    CROW_ROUTE(app, "/account/put")
    .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req){
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        const double amount = json::parse(req.body)["cash"];
        crow::response res;
        try
        {
            atm.putMoney(amount);
            res.code = 200;
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/account/take")
    .methods(crow::HTTPMethod::PUT, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req){
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        const double amount = json::parse(req.body)["cash"];
        crow::response res;
        try
        {
            atm.takeMoney(amount);
            res.code = 200;
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/account/info")
    .methods(crow::HTTPMethod::GET, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req){
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        crow::response res;
        try
        {
            const AccountInfo i = atm.getInfo();
            json data;
            data["balance"] = i._balance;
            res.code = 200;
            res.set_header("Content-Type", "application/json");
            res.write(data.dump());
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/account/transfer")
    .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req){
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        const double amount = json::parse(req.body)["cash"];
        const string number = json::parse(req.body)["number"];
        crow::response res;
        try
        {
            atm.transferMoney(amount, number);
            res.code = 200;
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/cash/info")
    .methods(crow::HTTPMethod::GET, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        json data;
        data["amount"] = atm.getCashInfo();
        crow::response res(200);
        res.set_header("Content-Type", "application/json");
        res.write(data.dump());
        return res;
    });

    CROW_ROUTE(app, "/deposit")
    .methods(crow::HTTPMethod::GET, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        crow::response res;
        try
        {
            const vector<DepositInfo> allDeposits = atm.getAllDeposits();
            json data;
            data["list"] = json::array();
            for (int i = 0; i < allDeposits.size(); ++i)
            {
                data["list"][i]["id"] = allDeposits[i]._id;
                data["list"][i]["startDate"] = allDeposits[i]._opened_at;
                data["list"][i]["endDate"] = allDeposits[i]._end_date;
                data["list"][i]["money"] = allDeposits[i]._balance;
                data["list"][i]["productName"] = allDeposits[i]._product_name;
            }
            res.code = 200;
            res.set_header("Content-type", "application/json");
            res.write(data.dump());
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/deposit/products")
    .methods(crow::HTTPMethod::GET, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        crow::response res;
        try
        {
            const vector<DepositProductInfo> allDepositProducts = atm.getAllDepositProducts();
            json data;
            data["list"] = json::array();
            for (int i = 0; i < allDepositProducts.size(); ++i)
            {
                data["list"][i]["id"] = allDepositProducts[i]._id;
                data["list"][i]["name"] = allDepositProducts[i]._name;
                data["list"][i]["interestRate"] = allDepositProducts[i]._interest_rate;
                data["list"][i]["termMonths"] = allDepositProducts[i]._term_months;
            }
            res.code = 200;
            res.set_header("Content-type", "application/json");
            res.write(data.dump());
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/deposit/put")
    .methods(crow::HTTPMethod::PUT, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        json data = json::parse(req.body);
        const int product_id = data["productId"];
        const double amount = data["amount"];
        crow::response res;
        try
        {
            atm.putOnDeposit(product_id, amount);
            res.code = 200;
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/deposit/take")
    .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        const int product_id = json::parse(req.body)["productId"];
        crow::response res;
        try
        {
            atm.takeFromDeposit(product_id);
            res.code = 200;
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/credit")
    .methods(crow::HTTPMethod::GET, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        crow::response res;
        try
        {
            const vector<CreditInfo> allCredits = atm.getAllCredits();
            json data;
            data["list"] = json::array();
            for (int i = 0; i < allCredits.size(); ++i)
            {
                data["list"][i]["id"] = allCredits[i]._id;
                data["list"][i]["productName"] = allCredits[i]._product_name;
                data["list"][i]["openedAt"] = allCredits[i]._opened_at;
                data["list"][i]["remainingAmount"] = allCredits[i]._remaining_amount;
            }
            res.code = 200;
            res.set_header("Content-type", "application/json");
            res.write(data.dump());
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/credit/products")
    .methods(crow::HTTPMethod::GET, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        crow::response res;
        try
        {
            const vector<CreditProductInfo> allCreditProducts = atm.getAllCreditProducts();
            json data;
            data["list"] = json::array();
            for (int i = 0; i < allCreditProducts.size(); ++i)
            {
                data["list"][i]["id"] = allCreditProducts[i]._id;
                data["list"][i]["name"] = allCreditProducts[i]._name;
                data["list"][i]["interestRate"] = allCreditProducts[i]._interest_rate;
                data["list"][i]["termMonths"] = allCreditProducts[i]._term_months;
            }
            res.code = 200;
            res.set_header("Content-type", "application/json");
            res.write(data.dump());
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/credit/take")
    .methods(crow::HTTPMethod::PUT, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        json data = json::parse(req.body);
        const int product_id = data["productId"];
        const double amount = data["amount"];
        crow::response res;
        try
        {
            atm.takeCredit(product_id, amount);
            res.code = 200;
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/credit/pay")
    .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        auto data = json::parse(req.body);
        const int product_id = data["productId"];
        const double amount = data["amount"];
        crow::response res;
        try
        {
            atm.payCredit(product_id, amount);
            res.code = 200;
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/daemon/credit-protection")
    .methods(crow::HTTPMethod::GET, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        crow::response res;
        try
        {
            const vector<CreditProtectionInfo> allCreditProtections = atm.getAllCreditProtections();
            json data;
            data["list"] = json::array();
            for (int i = 0; i < allCreditProtections.size(); ++i)
            {
                data["list"][i]["id"] = allCreditProtections[i]._id;
                data["list"][i]["backupCard"] = allCreditProtections[i]._backup_card;
                data["list"][i]["minBalance"] = allCreditProtections[i]._min_balance;            }
            res.code = 200;
            res.set_header("Content-type", "application/json");
            res.write(data.dump());
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/daemon/credit-protection/create")
    .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        auto data = json::parse(req.body);
        const double amount = data["amount"];
        crow::response res;
        try
        {
            atm.createCreditProtection(amount);
            res.code = 200;
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/daemon/credit-protection/delete")
    .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        auto data = json::parse(req.body);
        const double id = data["id"];
        crow::response res;
        try
        {
            atm.deleteCreditProtection(id);
            res.code = 200;
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/daemon/leftover")
    .methods(crow::HTTPMethod::GET, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        crow::response res;
        try
        {
            const vector<LeftOverInfo> allLeftOvers = atm.getAllLeftOvers();
            json data;
            data["list"] = json::array();
            for (int i = 0; i < allLeftOvers.size(); ++i)
            {
                data["list"][i]["id"] = allLeftOvers[i]._id;
                data["list"][i]["targetCard"] = allLeftOvers[i]._target_card;
                data["list"][i]["threshold"] = allLeftOvers[i]._threshold;
            }
            res.code = 200;
            res.set_header("Content-type", "application/json");
            res.write(data.dump());
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/daemon/leftover/create")
    .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        auto data = json::parse(req.body);
        const string target_card = data["targetCard"];
        const double treshold = data["threshold"];
        crow::response res;
        try
        {
            atm.createLeftOver(target_card, treshold);
            res.code = 200;
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/daemon/leftover/delete")
    .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        auto data = json::parse(req.body);
        const double id = data["id"];
        crow::response res;
        try
        {
            atm.deleteLeftOver(id);
            res.code = 200;
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/daemon/auto-transfer")
    .methods(crow::HTTPMethod::GET, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        crow::response res;
        try
        {
            const vector<AutoTransferinfo> allAutoTransfers = atm.getAllAutoTransfers();
            json data;
            data["list"] = json::array();
            for (int i = 0; i < allAutoTransfers.size(); ++i)
            {
                data["list"][i]["id"] = allAutoTransfers[i]._id;
                data["list"][i]["targetCard"] = allAutoTransfers[i]._target_card;
                data["list"][i]["frequency"] = allAutoTransfers[i]._frequency;
                data["list"][i]["nextDate"] = allAutoTransfers[i]._next_date;
                data["list"][i]["amount"] = allAutoTransfers[i]._amount;
            }
            res.code = 200;
            res.set_header("Content-type", "application/json");
            res.write(data.dump());
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/daemon/auto-transfer/create")
    .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        auto data = json::parse(req.body);
        const string target_card = data["targetCard"];
        const string frequency = data["frequency"];
        const string next_date = data["nextDate"];
        const double amount = data["amount"];
        crow::response res;
        try
        {
            atm.createAutoTransfer(target_card, frequency, next_date, amount);
            res.code = 200;
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    CROW_ROUTE(app, "/daemon/auto-transfer/delete")
    .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req) {
        if (req.method == crow::HTTPMethod::OPTIONS)
        {
            return crow::response(204);
        }
        cout << req.body << endl;
        auto data = json::parse(req.body);
        const double id = data["id"];
        crow::response res;
        try
        {
            atm.deleteAutoTransfer(id);
            res.code = 200;
        }
        catch(const BadOperation& bo)
        {
            cout << bo << endl;
            res.code = 404;
        }
        return res;
    });

    app.port(8000).multithreaded().run();
}
