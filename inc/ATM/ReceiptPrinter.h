#pragma once
#include <string>

class ReceiptPrinter
{
public:
    ReceiptPrinter() = default;
    ~ReceiptPrinter() = default;

    ReceiptPrinter(const ReceiptPrinter&) = delete;
    ReceiptPrinter(ReceiptPrinter&&) = delete;

    ReceiptPrinter& operator=(const ReceiptPrinter&) = delete;
    ReceiptPrinter& operator=(ReceiptPrinter&&) = delete;

    inline void printReceipt(const string& message) const { cout << "Printed receipt" << message << endl; }
};
