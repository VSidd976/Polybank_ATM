#pragma once

struct AccountInfo
{
    double _balance;
};

struct DepositInfo
{
    string _opened_at;
    string _closed_at;
    double _balance;
    int _product_id;
};

struct DepositProductInfo
{
    string _name;
    double _interest_rate;
    int _term_months;
    int _id;
};

struct CreditInfo
{
    double _debt;
};
