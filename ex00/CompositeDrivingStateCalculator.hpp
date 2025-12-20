#pragma once

#include "IDrivingStateCalculationFormula.hpp"

#include <vector>

class CompositeDrivingStateCalculator : public IDrivingStateCalculationFormula
{
    typedef std::vector<IDrivingStateCalculationFormula *> FormulaList;
    FormulaList formulas;

public:
    CompositeDrivingStateCalculator() {}
    ~CompositeDrivingStateCalculator() {}
    CompositeDrivingStateCalculator(const CompositeDrivingStateCalculator &other) : formulas(other.formulas) {}

public:
    void addFormula(IDrivingStateCalculationFormula &formula)
    {
        formulas.push_back(&formula);
    }

    DrivingState calculate(const DrivingState &state, double deltaTime)
    {
        DrivingState currentState;
        FormulaList::iterator it = formulas.begin();
        FormulaList::iterator ite = formulas.end();

        currentState = state;
        while (it != ite)
        {
            currentState = (*it)->calculate(currentState, deltaTime);
            it++;
        }
        return currentState;
    }

public:
    CompositeDrivingStateCalculator &operator=(const CompositeDrivingStateCalculator &other)
    {
        if (this != &other)
        {
            formulas = other.formulas;
        }
        return *this;
    }
};
