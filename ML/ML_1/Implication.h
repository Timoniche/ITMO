//
// Created by Timoniche on 3/16/2019.
//

#ifndef ML_1_IMPLICATION_H
#define ML_1_IMPLICATION_H

#include "BinOp.h"

struct Implication : BinOp
{
    Implication(IExpression *lhs, IExpression *rhs)
            : BinOp(lhs, rhs) {}

    std::string evaluate() override {
        return "(->," +
               m_left->evaluate() + "," +
               m_right->evaluate() + ")";
    }
};

#endif //ML_1_IMPLICATION_H
