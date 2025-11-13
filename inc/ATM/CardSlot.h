#pragma once
#include "CardCredentials.h"
#include <nlohmann/json.hpp>
#include <iostream>
using namespace std;
using namespace nlohmann;

class CardSlot
{
public:
    CardSlot() = default;
    ~CardSlot() = default;

    CardSlot(const CardSlot&) = delete;
    CardSlot(CardSlot&&) = delete;

    CardSlot& operator=(CardSlot&&) = delete;
    CardSlot& operator=(const CardSlot&) = delete;

    CardCredentials readCard(const json&) const;

    inline void returnCard() const { cout << "Returned card" << endl; }
};
