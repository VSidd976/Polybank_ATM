#include "CardSlot.h"

string CardSlot::decryptHex(const string& encoded=)
{
    std::string out;
    for (size_t i=0; i < encoded.size(); i+=2) {
        unsigned char const byte = std::stoi(encoded.substr(i,2), nullptr, 16);
        out += byte ^ secret[(i/2) % secret.size()];
    }
    return out;
}

CardCredentials CardSlot::readCard(const string &input)
{
    const string decrypted = decryptHex(input);
    const json data = json::parse(decrypted);
    CardCredentials creds {
        data["ownerName"],
        data["cardNumber"],
        data["bankName"],
        data["cvv"],
        data["expirationDate"],
    };
    return creds;
}