set(ATM_SOURCES
    ATM.cc
    CardSlot.cc
    ReceiptPrinter.cc
    CashAcceptor.cc
    Dispenser.cc
)

add_library(ATM STATIC ${ATM_SOURCES})
