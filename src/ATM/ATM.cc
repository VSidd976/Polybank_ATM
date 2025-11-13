#include "ATM.h"

ATM::ATM(IBankService& bankSerivce): _bankService(bankSerivce) {}

void ATM::acceptCard(const json& req) const
{
    const CardCredentials cardCreds = _cardSlot.readCard(req);
    cout << cardCreds._cardNumber << endl;
}

void ATM::acceptPin(const json& req, const string& pin)
{
    cout << "Parsing card" << endl;
    const CardCredentials cardCreds = _cardSlot.readCard(req);
    const string token = _bankService.validateEntry(cardCreds, pin);
    cout << "Started session" << endl;
    _state = SESSION;
    _session = new Session{ token };
    cout << cardCreds._cardNumber << endl;
}

void ATM::returnCard()
{
    _cardSlot.returnCard();
    delete _session;
    _session = nullptr;
    _state = MAINTENANCE;
}

void ATM::putMoney(const double& amount) const
{
    if (_session == nullptr) throw invalid_argument("Session is not started");
    _cashAcceptor.acceptCash(amount);
    _bankService.putMoney(_session->_token, amount);
}

void ATM::takeMoney(const double& amount) const
{
    if (_session == nullptr) throw invalid_argument("Session is not started");
    _bankService.getMoney(_session->_token, amount);
    _dispenser.returnMoney(amount);
}

AccountInfo ATM::showInfo() const
{
    if (_session == nullptr) throw invalid_argument("Session is not started");
    return _bankService.accountInfo(_session->_token);
}

void ATM::transferMoney(const double& amount, const string& to) const
{
    if (_session == nullptr) throw invalid_argument("Session is not started");
    _bankService.transferMoney(_session->_token, to, amount);
}

void ATM::printReceipt() const
{
    _receiptPrinter.printReceipt("something");
}
