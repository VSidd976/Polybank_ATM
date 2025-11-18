#include "BadOperation.h"

BadOperation::BadOperation(const string& error_type, const string& reason):
_error_type(error_type), _reason(reason) {}

ostream& operator<<(ostream& os, const BadOperation& bo)
{
    os << bo._error_type << ": " << bo._reason << endl;
    return os;
}
