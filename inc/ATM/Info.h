#pragma once

struct AccountInfo
{
    double _balance;
};

struct DepositInfo
{
    string _opened_at;
    string _closed_at;
    string _product_name;
    double _balance;
    int _product_id;
    int _id;
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
    string _product_name;
    double _amount;
    double _remaining_amount;
    double _interest_accured;
    int _product_id;
    int _id;
};

struct CreditProductInfo
{
    string _name;
    double _interest_rate;
    int _term_months;
    int _id;
};

struct CreditProtectionInfo
{
    string _backup_card;
    double _min_balance;
    int _id;
    bool _active;
};

struct LeftOverInfo
{
    string _target_card;
    double _threshold;
    int _id;
    // bool _active;
};

struct AutoTransferinfo
{
    string _target_card;
    string _frequency;
    string _next_date;
    double _amount;
    int _id;
    bool _active;
};
