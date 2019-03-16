//
// Created by Timoniche on 3/16/2019.
//

#ifndef ML_1_NEGATE_H
#define ML_1_NEGATE_H

#include "IExpression.h"

struct Negate : IExpression
{
private:
    IExpression *m_expr;
public:
    explicit Negate(IExpression *expr) : m_expr(expr) {}

    std::string evaluate() override {
        return "(!" + m_expr->evaluate() + ")";
    }
};

#endif //ML_1_NEGATE_H
