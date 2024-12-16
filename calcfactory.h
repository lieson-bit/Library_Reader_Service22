// calcfactory.h
#ifndef CALCFACTORY_H
#define CALCFACTORY_H

class AbstractCalc;

class CalcFactory
{
public:
    virtual AbstractCalc* createCalculator() = 0;
    virtual ~CalcFactory() {}
};

#endif // CALCFACTORY_H
