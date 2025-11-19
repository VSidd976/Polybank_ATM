#pragma once

struct AccountInfo
{
    double _balance;
};

struct DepositInfo
{
    string _opened_at;
    string _closed_at;
    double _number;
    double _balance;
    int _id;
};

struct CreditInfo
{
    double _debt;
};
