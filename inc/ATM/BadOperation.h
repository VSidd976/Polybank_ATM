#pragma once
#include <iostream>
using namespace std;

struct BadOperation
{
    string _error_type;
    string _reason;

    BadOperation(const string&, const string&);
};

ostream& operator<<(ostream& os, const BadOperation&);
