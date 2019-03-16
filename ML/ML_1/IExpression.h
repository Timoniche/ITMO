//
// Created by Timoniche on 3/15/2019.
//

#ifndef ML_1_EXPRESSIONINT_H
#define ML_1_EXPRESSIONINT_H

#include <string>
#include <memory>

struct IExpression
{
public:
    virtual std::string evaluate() = 0;

};

#endif //ML_1_EXPRESSIONINT_H
