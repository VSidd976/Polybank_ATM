set(ATM_SOURCES
    ATM.cc
    CardSlot.cc
    ReceiptPrinter.cc
    BankServices.cc
    Dispenser.cc
)

add_library(ATM STATIC ${ATM_SOURCES})
target_link_libraries(ATM PUBLIC Crow nlohmann_json)
