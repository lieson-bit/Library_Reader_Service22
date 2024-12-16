#include "calculationfacade.h"


int CalculationFacade::getCost(Book_data *value, CalcFactory *factory)
{
    AbstractCalc *calculator = factory->createCalculator();
    int cost = calculator->getCost(value);
    delete calculator;
    return cost;
}
