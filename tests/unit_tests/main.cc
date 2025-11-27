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

    REQUIRE_NOTHROW(atm.getInfo());

    REQUIRE_NOTHROW(atm.getAllDeposits());
    REQUIRE_NOTHROW(atm.getAllDepositProducts());

    REQUIRE_NOTHROW(atm.putOnDeposit(1, 200));
    REQUIRE_NOTHROW(atm.takeFromDeposit(1));

    REQUIRE_NOTHROW(atm.getAllCredits());
    REQUIRE_NOTHROW(atm.getAllCreditProducts());

    REQUIRE_NOTHROW(atm.takeCredit(1, 200));
    REQUIRE_NOTHROW(atm.payCredit(1, 200));

    REQUIRE_NOTHROW(atm.getAllCreditProtections());

    REQUIRE_NOTHROW(atm.createCreditProtection(200));
    REQUIRE_NOTHROW(atm.deleteCreditProtection(1));

    REQUIRE_NOTHROW(atm.getAllLeftOvers());

    REQUIRE_NOTHROW(atm.createLeftOver("4556727619519847", 200));
    REQUIRE_NOTHROW(atm.deleteLeftOver(1));

    REQUIRE_NOTHROW(atm.getAllAutoTransfers());

    REQUIRE_NOTHROW(atm.createAutoTransfer("4556727619519847", "once", "tommorrow", 200));
    REQUIRE_NOTHROW(atm.deleteAutoTransfer(1));

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

    REQUIRE_THROWS(atm.acceptPin(card, "1111"));

    REQUIRE_THROWS(atm.takeMoney(240));
    REQUIRE_THROWS(atm.transferMoney(200, "0987654321123456"));

    REQUIRE_THROWS(atm.putOnDeposit(6, 200));
    REQUIRE_THROWS(atm.takeFromDeposit(6));

    REQUIRE_THROWS(atm.takeCredit(6, 200));
    REQUIRE_THROWS(atm.payCredit(6, 200));

    REQUIRE_THROWS(atm.deleteCreditProtection(6));

    REQUIRE_THROWS(atm.createLeftOver("0987654321123456", 200));
    REQUIRE_THROWS(atm.deleteLeftOver(6));

    REQUIRE_THROWS(atm.createAutoTransfer("0987654321123456", "never", "yestersday", 200));
    REQUIRE_THROWS(atm.deleteAutoTransfer(6));
}
