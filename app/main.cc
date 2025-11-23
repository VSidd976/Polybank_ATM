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
            for (int i = 0; i < allDepositProducts.size(); ++i)
            {
                data[i]["id"] = allDepositProducts[i]._id;
                data[i]["name"] = allDepositProducts[i]._name;
                data[i]["interestRate"] = allDepositProducts[i]._interest_rate;
                data[i]["termMonths"] = allDepositProducts[i]._term_months;
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
            const vector<DepositProductInfo> allDepositProducts = atm.getAllDepositProducts();
            json data;
            for (int i = 0; i < allDeposits.size(); ++i)
            {
                data[i]["id"] = allDeposits[i]._product_id;
                data[i]["startDate"] = allDeposits[i]._opened_at;
                data[i]["endDate"] = allDeposits[i]._closed_at;
                data[i]["money"] = allDeposits[i]._balance;
                data[i]["productName"] = "123";
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

    // CROW_ROUTE(app, "/deposit/info")
    // .methods(crow::HTTPMethod::GET, crow::HTTPMethod::OPTIONS)
    // ([&atm](const crow::request& req) {
    //     if (req.method == crow::HTTPMethod::OPTIONS)
    //     {
    //         return crow::response(204);
    //     }
    //     cout << req.body << endl;
    //     const json req_data = json::parse(req.body);
    //     crow::response res;
    //     try
    //     {
    //         const DepositInfo info = atm.getDpositInfo(req_data["number"]);
    //         json data;
    //         data["number"] = info._number;
    //         data["balance"] = info._balance;
    //         data["opened_at"] = info._opened_at;
    //         data["closed_at"] = info._closed_at;
    //         res.code = 200;
    //         res.set_header("Content-type", "application/json");
    //         res.write(data.dump());
    //     }
    //     catch(const BadOperation& bo)
    //     {
    //         cout << bo << endl;
    //         res.code = 404;
    //     }
    //     return res;
    // });

    // CROW_ROUTE(app, "/deposit/put")
    // .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    // ([&atm](const crow::request& req) {
    //     if (req.method == crow::HTTPMethod::OPTIONS)
    //     {
    //         return crow::response(204);
    //     }
    //     cout << req.body << endl;
    //     json data = json::parse(req.body);
    //     const string number = data["number"];
    //     const double amount = data["cash"];
    //     crow::response res;
    //     try
    //     {
    //         atm.putOnDeposit(number, amount);
    //         res.code = 200;
    //     }
    //     catch(const BadOperation& bo)
    //     {
    //         cout << bo << endl;
    //         res.code = 404;
    //     }
    //     return res;
    // });

    app.port(8000).multithreaded().run();
}
