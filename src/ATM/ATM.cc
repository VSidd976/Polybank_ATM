#include "ATM.h"

ATM::ATM(IBankService& bankSerivce): _bankService(bankSerivce) {}

void ATM::acceptCard(const json& req) const
{
    const CardCredentials cardCreds = _cardSlot.readCard(req);
    if (!_bankService.validateCard(cardCreds))
    {
        throw BadOperation("Bad validation", "could not validate card");
    }
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

void ATM::putMoney(const double& amount)
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    _cashAcceptor.acceptCash(amount);
    _bankService.putMoney(_session->_token, amount);
    _cashStorage._amount += amount;
}

void ATM::takeMoney(const double& amount)
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    if (_cashStorage._amount < amount)
    {
        throw BadOperation("Bad request", "We don't have that much cash");
    }
    _bankService.getMoney(_session->_token, amount);
    _cashStorage._amount -= amount;
    _dispenser.returnMoney(amount);
}

AccountInfo ATM::getInfo() const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    return _bankService.accountInfo(_session->_token);
}

void ATM::transferMoney(const double& amount, const string& to) const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    _bankService.transferMoney(_session->_token, to, amount);
}

void ATM::printReceipt() const
{
    _receiptPrinter.printReceipt("something");
}

vector<DepositInfo> ATM::getAllDeposits() const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    return _bankService.allDeposits(_session->_token);
}

DepositInfo ATM::getDpositInfo(const string& number) const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    return _bankService.depositInfo(number);
}

void ATM::putOnDeposit(const string& number, const double& amount) const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    _bankService.putOnDeposit(number, amount);
}
