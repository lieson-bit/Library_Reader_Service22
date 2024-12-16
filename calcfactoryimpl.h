// calcfactoryimpl.h
#ifndef CALCFACTORYIMPL_H
#define CALCFACTORYIMPL_H

#include "headers.h"

class CalcFactoryImpl : public CalcFactory
{
public:
    CalcFactoryImpl(AbstractCalc *calculator);
    AbstractCalc* createCalculator() override;

private:
    AbstractCalc *calculator;
};

#endif // CALCFACTORYIMPL_H
