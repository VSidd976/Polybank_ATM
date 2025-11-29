#include "CashStorage.h"

CashStorage::CashStorage()
{
    string inPath = "../../saved_cash.json";
    if (filesystem::exists(inPath))
    {
        ifstream inFile(inPath);
        json data;
        inFile >> data;
        _amount = data["SAVED_CASH"];
        inFile.close();
    }
}

CashStorage::~CashStorage()
{
    ofstream outFile("../../saved_cash.json");
    json data;
    data["SAVED_CASH"] = _amount;
    outFile << data.dump();
    outFile.close();
}
