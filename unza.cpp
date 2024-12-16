#include "unza.h"


int UNZA::getCost(Book_data *value)
{
    return value->getyear()/200+70;
}
