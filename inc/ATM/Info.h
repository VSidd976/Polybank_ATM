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
    string _opened_at;
    string _closed_at;
    string _product_name;
    double _amount;
    double _remaining_amount;
    double _interest_accured;
    int _product_id;
};

struct CreditProductinfo
{
    string _name;
    double _interest_rate;
    int _term_months;
    int _id;
};
