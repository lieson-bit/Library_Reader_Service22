#ifndef GUAPCALC_H
#define GUAPCALC_H
#include "headers.h"

class Guapcalc: public AbstractCalc
{
public:
    int getCost(Book_data *value) override;
};

#endif // GUAPCALC_H
