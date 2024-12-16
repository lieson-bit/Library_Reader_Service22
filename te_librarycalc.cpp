#include "te_librarycalc.h"


int Te_librarycalc::getCost(Book_data *value)
{
    return value->getyear()/120+20;
}
