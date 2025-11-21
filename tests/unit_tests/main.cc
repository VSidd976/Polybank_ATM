#include <catch2/catch_test_macros.hpp>
#include "TestBank.h"

TEST_CASE("Base flow")
{
    TestBank bank;
    ATM atm(bank);
    json card;

    card["ownerName"] = "John Doe";
    card["cardNumber"] = "1234567890123456";
    card["bankName"] = "OpenAI Bank";
    card["cvv"] = "123";
    card["expirationDate"] = "12/26";

    REQUIRE_NOTHROW(atm.acceptCard(card));
    REQUIRE_NOTHROW(atm.acceptPin(card, "1234"));

    REQUIRE_NOTHROW(atm.putMoney(235));
    REQUIRE_NOTHROW(atm.takeMoney(115));

    REQUIRE_NOTHROW(atm.transferMoney(25, "4556727619519847"));

    REQUIRE_NOTHROW(atm.returnCard());
}

TEST_CASE("Exceptional flow")
{
    TestBank bank;
    ATM atm(bank);
    json card;

    card["ownerName"] = "John Doe";
    card["cardNumber"] = "1234567890123456";
    card["bankName"] = "OpenAI Bank";
    card["expirationDate"] = "12/26";
    card["cvv"] = "123";

    REQUIRE_THROWS(atm.acceptCard(card));

    REQUIRE_THROWS(atm.takeMoney(240));

    REQUIRE_NOTHROW(atm.acceptCard(card));

    REQUIRE_THROWS(atm.acceptPin(card, "1111"));

    REQUIRE_NOTHROW(atm.acceptPin(card, "1234"));

    REQUIRE_THROWS(atm.takeMoney(240));
}
