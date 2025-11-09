#include "ATM.h"

ATM::ATM() {}

void ATM::acceptCard(const std::string& creds) {
    const CardCredentials cardCreds = _cardSlot.readCard(creds);
    std::cout << cardCreds._cardNumber << std::endl;
}

ATM::~ATM()
{
    delete _session;
}
