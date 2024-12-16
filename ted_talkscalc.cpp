#include "ted_talkscalc.h"

int Ted_talkscalc::getCost(Book_data *value)
{
      return value->getyear()/5 +20;
}
