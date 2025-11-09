#pragma once
#include "CardCredentials.h"

class ICardSlot
{
public:
    virtual CardCredentials readCard(const string& input);
    virtual ~ICardSlot() = default;
};

class CardSlot : public ICardSlot
{
private:
    string secret = "secret-key";
public:
    CardSlot() = default;

    CardSlot(const CardSlot&) = delete;
    CardSlot(CardSlot&&) = delete;

    ~CardSlot() override = default;
    CardSlot& operator=(CardSlot&&) = delete;
    CardSlot& operator=(const CardSlot&) = delete;

    CardCredentials readCard(const string& input) override;

private:
    string decryptHex(const string& encoded);
};
