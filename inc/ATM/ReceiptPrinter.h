#pragma once
#include <string>

class IReceiptPrinter
{
    public:
    virtual void printReceipt(string&) = 0;
    virtual ~IReceiptPrinter() = default;
};

class ReceiptPrinter : public IReceiptPrinter
{
public:
    ReceiptPrinter() = default;
    ReceiptPrinter(const ReceiptPrinter&) = delete;
    ReceiptPrinter(ReceiptPrinter&&) = delete;

    ReceiptPrinter& operator=(const ReceiptPrinter&) = delete;
    ReceiptPrinter& operator=(ReceiptPrinter&&) = delete;

    void printReceipt(string&) {}
};
