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

vector<DepositProductInfo> ATM::getAllDepositProducts() const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    return _bankService.allDepositProducts(_session->_token);
}

void ATM::putOnDeposit(const int& product_id, const double& amount) const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    _bankService.putOnDeposit(_session->_token, product_id, amount);
}

void ATM::takeFromDeposit(const int& product_id) const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    _bankService.takeFromDeposit(_session->_token, product_id);
}

void ATM::takeCredit(const int& product_id, const double& amount) const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    _bankService.takeCredit(_session->_token, product_id, amount);
}

void ATM::payCredit(const int& product_id, const double& amount) const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    _bankService.payCredit(_session->_token, product_id, amount);
}

vector<CreditInfo> ATM::getAllCredits() const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    return _bankService.allCredits(_session->_token);
}

vector<CreditProductInfo> ATM::getAllCreditProducts() const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    return _bankService.allCreditProducts(_session->_token);
}

vector<CreditProtectionInfo> ATM::getAllCreditProtections() const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    return _bankService.allCreditProtections(_session->_token);
}

void ATM::createCreditProtection(const double& amount) const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    _bankService.createCreditProtection(_session->_token, amount);
}

void ATM::deleteCreditProtection(const int& id) const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    _bankService.deleteCreditProtection(_session->_token, id);
}

vector<LeftOverInfo> ATM::getAllLeftOvers() const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    return _bankService.allLeftOvers(_session->_token);
}

void ATM::createLeftOver(const string& target_card, const double& treshold) const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    _bankService.createLeftOver(_session->_token, target_card, treshold);
}

void ATM::deleteLeftOver(const int& id) const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    _bankService.deleteLeftOver(_session->_token, id);
}

vector<AutoTransferinfo> ATM::getAllAutoTransfers() const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    return _bankService.allAutoTransfers(_session->_token);
}

void ATM::createAutoTransfer(const string& target_card, const string& frequency, const string& next_date, const double& amount) const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    _bankService.createAutoTransfer(_session->_token, target_card, frequency, next_date, amount);
}

void ATM::deleteAutoTransfer(const int& id) const
{
    if (_session == nullptr)
    {
        throw BadOperation("Bad request", "Session is not started");
    }
    _bankService.deleteAutoTransfer(_session->_token, id);
}
