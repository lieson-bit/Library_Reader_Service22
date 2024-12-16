#include "guapcalc.h"


int Guapcalc::getCost(Book_data *value)
{
    return value->getyear()/30+9;
}
