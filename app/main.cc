#include <crow.h>
#include "crow/middlewares/cors.h"
#include <nlohmann/json.hpp>
#include "ATM.h"
using namespace nlohmann;

int main() {
    crow::App<crow::CORSHandler> app;
    ATM atm {};

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

        std::cout << req.body << std::endl;
        atm.acceptCard(req.body);

        crow::response res(200, "123456");
        return res;
    });

    CROW_ROUTE(app, "/card/pin")
    .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req){
        if (req.method == crow::HTTPMethod::OPTIONS) {
            return crow::response(204);
        }

        std::cout << req.body << std::endl;
        atm.acceptPin(req.body);

        crow::response res(200, "123456");
        return res;
    });

    CROW_ROUTE(app, "/card/return")
    .methods(crow::HTTPMethod::PUT, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req){
        if (req.method == crow::HTTPMethod::OPTIONS) {
            return crow::response(204);
        }

        std::cout << req.body << std::endl;
        atm.returnCard();

        crow::response res(200, "123456");
        return res;
    });

    CROW_ROUTE(app, "/account/put")
    .methods(crow::HTTPMethod::POST, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req){
        if (req.method == crow::HTTPMethod::OPTIONS) {
            return crow::response(204);
        }

        std::cout << req.body << std::endl;
        const double amount = json::parse(req.body)["cash"];
        atm.putMoney(amount);

        crow::response res(200, "123456");
        return res;
    });

     CROW_ROUTE(app, "/account/take")
    .methods(crow::HTTPMethod::PUT, crow::HTTPMethod::OPTIONS)
    ([&atm](const crow::request& req){
        if (req.method == crow::HTTPMethod::OPTIONS) {
            return crow::response(204);
        }

        std::cout << req.body << std::endl;
        const double amount = json::parse(req.body)["cash"];
        atm.takeMoney(amount);

        crow::response res(200, "123456");
        return res;
    });

    app.port(8000).multithreaded().run();
}
