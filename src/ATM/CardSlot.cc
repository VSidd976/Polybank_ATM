#include "CardSlot.h"

CardCredentials CardSlot::readCard(const json &data)
{
    return CardCredentials {
        data["ownerName"],
        data["cardNumber"],
        data["bankName"],
        data["cvv"],
        data["expirationDate"],
    };;
}
