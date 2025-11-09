#include "ATM.h"

ATM::ATM() {}

void ATM::acceptCard(const std::string& req) {
    const CardCredentials cardCreds = _cardSlot.readCard(req);
    std::cout << cardCreds._cardNumber << std::endl;
}

void ATM::acceptPin(const std::string& req) {
    const CardCredentials cardCreds = _cardSlot.readCard(req);
    const std::string pin = json::parse(req)["pin"];
    const std::string token = "";
    _session = new Session{ token };
    std::cout << cardCreds._cardNumber << std::endl;
}

void ATM::returnCard() {
    std::cout << "Card returned" << std::endl;
    delete _session;
}

ATM::~ATM()
{
    delete _session;
}
