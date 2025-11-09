#include "CardSlot.h"

CardCredentials CardSlot::readCard(const json &data)
{
    return CardCredentials {
        data.at("ownerName"),
        data.at("cardNumber"),
        data.at("bankName"),
        data.at("cvv"),
        data.at("expirationDate"),
    };;
}
