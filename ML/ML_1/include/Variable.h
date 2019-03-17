//
// Created by Timoniche on 3/16/2019.
//

#ifndef ML_1_VARIABLE_H
#define ML_1_VARIABLE_H

#include <string>
#include "IExpression.h"

struct Variable : IExpression
{
private:
    std::string variable;
public:
    explicit Variable(std::string &variable) : variable(variable) {}

    std::string evaluate() override {
        return variable;
    }
};

#endif //ML_1_VARIABLE_H
