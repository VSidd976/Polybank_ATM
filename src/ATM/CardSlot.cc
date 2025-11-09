#include "CardSlot.h"

CardCredentials CardSlot::readCard(const string &input)
{
    const json data = json::parse(input);
    CardCredentials creds {
        data["ownerName"],
        data["cardNumber"],
        data["bankName"],
        data["cvv"],
        data["expirationDate"],
    };
    return creds;
}
