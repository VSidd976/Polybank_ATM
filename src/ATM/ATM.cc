#include "ATM.h"

ATM::ATM() {}

ATM::~ATM()
{
    delete _session;
}
