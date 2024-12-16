#ifndef TE_LIBRARYCALC_H
#define TE_LIBRARYCALC_H

#include "headers.h"

class Te_librarycalc : public AbstractCalc
{
public:
    int getCost(Book_data *value) override;
};

#endif // TE_LIBRARYCALC_H
