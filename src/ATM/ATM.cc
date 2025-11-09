#include "ATM.h"

void ATM::acceptCard(const json& req) {
    const CardCredentials cardCreds = _cardSlot.readCard(req);
    cout << cardCreds._cardNumber << endl;
}

void ATM::acceptPin(const json& req, const string& pin) {
    std::cout << "Parsing card" << std::endl;
    const CardCredentials cardCreds = _cardSlot.readCard(req);
    const string token = _bankService.validateEntry(cardCreds, pin);
    std::cout << "Started session" << std::endl;
    _state = SESSION;
    _session = new Session{ token };
    cout << cardCreds._cardNumber << endl;
}

void ATM::returnCard() {
    cout << "Card returned" << endl;
    delete _session;
    _session = nullptr;
    _state = MAINTENANCE;
}

void ATM::putMoney(const double& amount)
{
    if (_session == nullptr) throw invalid_argument("Session is not started");
    _bankService.putMoney(_session->_token, amount);
}

void ATM::takeMoney(const double& amount)
{
    if (_session == nullptr) throw invalid_argument("Session is not started");
    _bankService.getMoney(_session->_token, amount);
}

AccountInfo ATM::showInfo() const
{
    if (_session == nullptr) throw invalid_argument("Session is not started");
    return _bankService.accountInfo(_session->_token);
}

void ATM::transferMoney(const double& amount, const string& to)
{
    if (_session == nullptr) throw invalid_argument("Session is not started");
    _bankService.transferMoney(_session->_token, to, amount);
}

void ATM::printReceipt()
{
    _receiptPrinter.printReceipt("something");
}
