#include <crow.h>
#include "crow/middlewares/cors.h"
#include <nlohmann/json.hpp>
#include "ATM.h"
using namespace nlohmann;

int main() {
    crow::App<crow::CORSHandler> app;
    PolyBank polyBank;
    ATM atm(polyBank);

    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors.global()
        .origin("*")
        .methods("POST"_method, "GET"_method, "PUT"_method, "OPTIONS"_method)
        .headers("Content-Type", "X-Custom-Header");

    CROW_ROUTE(app, "/card/accept")
    .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req){
        if (req.method == crow::HTTPMethod::OPTIONS) {
            return crow::response(204);
        }

        cout << req.body << endl;
        const json data = json::parse(req.body);
        atm.acceptCard(data);

        crow::response res(200);
        return res;
    });

    CROW_ROUTE(app, "/card/pin")
    .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req){
        if (req.method == crow::HTTPMethod::OPTIONS) {
            return crow::response(204);
        }

        cout << req.body << endl;
        const json data = json::parse(req.body);
        const std::string pin = data["pin"];
        atm.acceptPin(data, pin);

        crow::response res(200);
        return res;
    });

    CROW_ROUTE(app, "/card/return")
    .methods(crow::HTTPMethod::PUT, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req){
        if (req.method == crow::HTTPMethod::OPTIONS) {
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
        if (req.method == crow::HTTPMethod::OPTIONS) {
            return crow::response(204);
        }

        cout << req.body << endl;
        const double amount = json::parse(req.body)["cash"];
        atm.putMoney(amount);

        crow::response res(200);
        return res;
    });

    CROW_ROUTE(app, "/account/take")
    .methods(crow::HTTPMethod::PUT, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req){
        if (req.method == crow::HTTPMethod::OPTIONS) {
            return crow::response(204);
        }

        cout << req.body << endl;
        const double amount = json::parse(req.body)["cash"];
        atm.takeMoney(amount);

        crow::response res(200);
        return res;
    });

    CROW_ROUTE(app, "/account/info")
    .methods(crow::HTTPMethod::Get, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req){
        if (req.method == crow::HTTPMethod::OPTIONS) {
            return crow::response(204);
        }

        cout << req.body << endl;
        const AccountInfo i = atm.showInfo();
        json data;
        data["balance"] = i.balance;

        crow::response res(200);
        res.set_header("Content-Type", "application/json");
        res.write(data.dump());
        return res;
    });

    app.port(8000).multithreaded().run();
}
