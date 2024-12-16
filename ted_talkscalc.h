#ifndef TED_TALKSCALC_H
#define TED_TALKSCALC_H

#include "headers.h"

class Ted_talkscalc : public AbstractCalc
{
public:
     int getCost(Book_data *value) override;
};

#endif // TED_TALKSCALC_H
