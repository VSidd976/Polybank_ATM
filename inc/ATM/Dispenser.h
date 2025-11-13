#pragma once

class Dispenser
{
public:
    Dispenser() = default;
    ~Dispenser() = default;

    Dispenser(const Dispenser&) = delete;
    Dispenser(Dispenser&&) = delete;

    Dispenser& operator=(const Dispenser&) = delete;
    Dispenser& operator=(Dispenser&&) = delete;

    inline void returnMoney(const double& amount) const { cout << "Returned " << amount << " hryvnia" << endl; }
};
