#include <iostream>

#include "Parser.h"

/**
!A&!B->!(A|B)
(->,(&,(!A),(!B)),(!(|,A,B)))
_____________________________________________________
P1'->!QQ->!R10&S|!T&U&V
(->,P1',(->,(!QQ),(|,(&,(!R10),S),(&,(&,(!T),U),V))))
_____________________________________________________
*/
int main() {
    std::string expression;
    std::cin >> expression;
    Parser p(expression);
    std::cout << p.make_tree();
    return 0;
}