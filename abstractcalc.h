#ifndef ABSTRACTCALC_H
#define ABSTRACTCALC_H

#include "book_data.h"

class AbstractCalc
{
public:
    virtual ~AbstractCalc() {}
    virtual int getCost(Book_data *value) = 0;
};

#endif // ABSTRACTCALC_H
