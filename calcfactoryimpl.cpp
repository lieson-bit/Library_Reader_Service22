#include "calcfactoryimpl.h"

CalcFactoryImpl::CalcFactoryImpl(AbstractCalc *calculator)
    : calculator(calculator)
{}

AbstractCalc* CalcFactoryImpl::createCalculator()
{
    return calculator;
}

