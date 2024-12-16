// calculationfacade.h
#ifndef CALCULATIONFACADE_H
#define CALCULATIONFACADE_H

class AbstractCalc;
class CalcFactory;
#include "headers.h"
class Book_data;
class CalculationFacade
{
public:
    static int getCost(Book_data *value, CalcFactory *factory);
};

#endif // CALCULATIONFACADE_H
