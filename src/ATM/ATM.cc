#include "ATM.h"

void ATM::acceptCard(const json& req) {
    const CardCredentials cardCreds = _cardSlot.readCard(req);
    cout << cardCreds._cardNumber << endl;
}

void ATM::acceptPin(const json& req) {
    const CardCredentials cardCreds = _cardSlot.readCard(req);
    const string pin = json::parse(req)["pin"];
    const string token = "";
    _session = new Session{ token };
    cout << cardCreds._cardNumber << endl;
}

void ATM::returnCard() {
    cout << "Card returned" << endl;
    delete _session;
}

void ATM::putMoney(const double& amount)
{

}

void ATM::takeMoney(const double& amount)
{

}

void ATM::showInfo() const
{

}
