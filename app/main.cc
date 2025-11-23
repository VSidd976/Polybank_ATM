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
                data["list"][i]["id"] = allDeposits[i]._product_id;
                data["list"][i]["startDate"] = allDeposits[i]._opened_at;
                data["list"][i]["endDate"] = allDeposits[i]._closed_at;
                data["list"][i]["money"] = allDeposits[i]._balance;
                data["list"][i]["productName"] = "123";
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

    CROW_ROUTE(app, "/depsoit/put")
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
                data["list"][i]["id"] = allCredits[i]._product_id;
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
            atm.takeCredits(product_id, amount);
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

    app.port(8000).multithreaded().run();
}
