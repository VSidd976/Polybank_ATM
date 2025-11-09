#include "ATM.h"

void ATM::acceptCard(const json& req) {
    const CardCredentials cardCreds = _cardSlot.readCard(req);
    cout << cardCreds._cardNumber << endl;
}

void ATM::acceptPin(const json& req, const string& pin) {
    const CardCredentials cardCreds = _cardSlot.readCard(req);
    const string token = _bankService.validateEntry(cardCreds, pin);
    _session = new Session{ token };
    cout << cardCreds._cardNumber << endl;
}

void ATM::returnCard() {
    cout << "Card returned" << endl;
    delete _session;
    _session = nullptr;
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

void ATM::transferMoney(const double& amount, const string& to) {

}
