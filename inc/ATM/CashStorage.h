#pragma once
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
using namespace std;
using namespace nlohmann;

struct CashStorage
{
    double _amount{0};

    CashStorage();
    ~CashStorage();
};
