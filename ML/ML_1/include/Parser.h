//
// Created by Timoniche on 3/14/2019.
//

#ifndef ML_1_PARSER_H
#define ML_1_PARSER_H

#include <string>
#include "IExpression.h"
#include "BinOp.h"
#include "Conjunction.h"
#include "Disjunction.h"
#include "Implication.h"
#include "Variable.h"
#include "Negate.h"

struct Parser
{
private:
    std::string exp;
    int pos = 0;
//_________________________________________________________
private:
    char next_char() {
        return (pos < exp.size() ? exp[pos++] : '%');
    }

//_________________________________________________________
    IExpression *variable() {
        char c;
        std::string res;
        while ((c = next_char()) != '%') {
            if (isdigit(c) || isalpha(c) || c == '\'') {
                res += c;
            } else {
                pos--;
                break;
            }
        }
        return new Variable(res);
    }

    IExpression *negate() {
        char c = next_char();
        if (c == '!') {
            return new Negate(negate());
        } else if (c == '(') {
            IExpression *ret = implication();
            pos++;
            return ret;
        }
        pos--;
        return variable();
    }

    IExpression *conjunction() {
        IExpression *ret = negate();
        char c;
        while ((c = next_char()) != '%') {
            if (c == '&') {
                ret = new Conjunction(ret, negate());
            } else {
                pos--;
                break;
            }
        }
        return ret;
    }

    IExpression *disjunction() {
        IExpression *ret = conjunction();
        char c;
        while ((c = next_char()) != '%') {
            if (c == '|') {
                ret = new Disjunction(ret, conjunction());
            } else {
                pos--;
                break;
            }
        }
        return ret;
    }

    IExpression *implication() {
        IExpression *ret = disjunction();
        char c;
        while ((c = next_char()) != '%') {
            if (c == '-') {
                pos++;
                ret = new Implication(ret, implication());
            } else {
                pos--;
                break;
            }
        }
        return ret;
    }
//_________________________________________________________
public:
    explicit Parser(std::string &exp) : exp(exp) {}

    std::string make_tree() {
        return implication()->evaluate();
    }
};


#endif //ML_1_PARSER_H

