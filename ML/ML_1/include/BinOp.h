//
// Created by Timoniche on 3/16/2019.
//

#ifndef ML_1_BINOP_H
#define ML_1_BINOP_H

#include "IExpression.h"

#include <memory>

struct BinOp : IExpression
{
protected:
    IExpression *m_left;
    IExpression *m_right;
public:
    BinOp(IExpression *lhs, IExpression *rhs) : m_left(lhs), m_right(rhs) {}
};

#endif //ML_1_BINOP_H
