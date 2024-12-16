#ifndef UNZA_H
#define UNZA_H

#include "abstractcalc.h"

class UNZA : public AbstractCalc
{
public:
    int getCost(Book_data *value) override;
};

#endif // UNZA_H
