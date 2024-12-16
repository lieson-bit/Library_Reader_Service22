#include "jmax_limcalc.h"

int Jmax_limcalc::getCost(Book_data *value)
{
    return value->getyear() / 10 +50 ;
}
