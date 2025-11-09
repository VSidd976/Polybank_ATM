#pragma once
#include "CardCredentials.h"
#include <nlohmann/json.hpp>

using namespace nlohmann;

class ICardSlot
{
public:
    virtual CardCredentials readCard(const string& input) = 0;
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
