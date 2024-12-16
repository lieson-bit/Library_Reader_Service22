#ifndef JMAX_LIMCALC_H
#define JMAX_LIMCALC_H
#include "headers.h"

class Jmax_limcalc: public AbstractCalc
{
public:
    int getCost(Book_data *value) override;
};

#endif // JMAX_LIMCALC_H
