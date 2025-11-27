#pragma once
#include <iostream>
using namespace std;

class CashAcceptor
{
public:
    CashAcceptor() = default;
    ~CashAcceptor() = default;

    CashAcceptor(const CashAcceptor&) = delete;
    CashAcceptor(CashAcceptor&&) = delete;

    CashAcceptor& operator=(const CashAcceptor&) = delete;
    CashAcceptor& operator=(CashAcceptor&&) = delete;

    void inline acceptCash(const double& amount) const { cout << "Accepted " << amount << " hryvnia" << endl; }
};
