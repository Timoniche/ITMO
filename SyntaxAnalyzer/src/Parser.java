import java.io.InputStream;
import java.text.ParseException;

public class Parser {
    LexicalAnalyzer lex;

    Tree S() throws ParseException {
        switch (lex.curToken()) {
            case NOT:
            case VAR:
            case LPAREN:
                return new Tree("S", B(), SPrime());
            case END:
                return new Tree("S", new Tree("ε"));
            default:
                throw new ParseException("Wrong token: " + lex.curToken() +
                        ", Offset: ", lex.curPos());
        }
    }

//    Tree SPrime() throws ParseException {
//        switch (lex.curToken()) {
//            case OR:
//                lex.nextToken();
//                return new Tree("S'", new Tree("or"), A(), SPrime());
//            case END:
//            case RPAREN:
//                return new Tree("S'", new Tree("ε"));
//            default:
//                throw new ParseException("Wrong token: " + lex.curToken() +
//                        ", Offset: ", lex.curPos());
//        }
//    }

    Tree SPrime() throws ParseException {
    switch (lex.curToken()) {
        case OR:
            lex.nextToken();
            return new Tree("S'", new Tree("or"), B(), SPrime());
        case XOR:
            lex.nextToken();
            return new Tree("S'", new Tree("xor"), B(), SPrime());
        case END:
        case RPAREN:
            return new Tree("S'", new Tree("ε"));
        default:
            throw new ParseException("Wrong token: " + lex.curToken() +
                    ", Offset: ", lex.curPos());
    }
}

//    Tree A() throws ParseException {
//        switch (lex.curToken()) {
//            case NOT:
//            case VAR:
//            case LPAREN:
//                return new Tree("A", B(), APrime());
//            default:
//                throw new ParseException("Wrong token: " + lex.curToken() +
//                        ", Offset: ", lex.curPos());
//        }
//    }

//    Tree APrime() throws ParseException {
//        switch (lex.curToken()) {
//            case XOR:
//                lex.nextToken();
//                return new Tree("A'", new Tree("xor"), B(), APrime());
//            case END:
//            case RPAREN:
//            case OR:
//                return new Tree("A'", new Tree("ε"));
//            default:
//                throw new ParseException("Wrong token: " + lex.curToken() +
//                        ", Offset: ", lex.curPos());
//        }
//    }


    Tree B() throws ParseException {
        switch (lex.curToken()) {
            case NOT:
            case VAR:
            case LPAREN:
                return new Tree("B", C(), BPrime());
            default:
                throw new ParseException("Wrong token: " + lex.curToken() +
                        ", Offset: ", lex.curPos());
        }
    }

    Tree BPrime() throws ParseException {
        switch (lex.curToken()) {
            case AND:
                lex.nextToken();
                return new Tree("B'", new Tree("and"), C(), BPrime());
            case END:
            case RPAREN:
            case OR:
            case XOR:
                return new Tree("B'", new Tree("ε"));
            default:
                throw new ParseException("Wrong token: " + lex.curToken() +
                        ", Offset: ", lex.curPos());
        }
    }

    Tree C() throws ParseException {
        switch (lex.curToken()) {
            case NOT:
                lex.nextToken();
                return new Tree("C", new Tree("not"), D());
            case VAR:
            case LPAREN:
                return new Tree("C", D());
            default:
                throw new ParseException("Wrong token: " + lex.curToken() +
                        ", Offset: ", lex.curPos());
        }
    }

    Tree D() throws ParseException {
        switch (lex.curToken()) {
            case VAR:
                char var = lex.getVar();
                lex.nextToken();
                return new Tree("D", new Tree(Character.toString(var)));
            case LPAREN:
                Tree lBr = new Tree("(");
                lex.nextToken();
                Tree nextS = S();

                //and (a or b [?]
                if (lex.curToken() != Token.RPAREN) {
                    throw new ParseException("Wrong token: " + lex.curToken() +
                            ", Offset: ", lex.curPos());
                }

                Tree rBr = new Tree(")");
                lex.nextToken();
                return new Tree("D", lBr, nextS, rBr);
            default:
                throw new ParseException("Wrong token: " + lex.curToken() +
                        ", Offset: ", lex.curPos());
        }
    }


    Tree parse(InputStream is) throws ParseException {
        lex = new LexicalAnalyzer(is);
        lex.nextToken();
        Tree ret = S();
        if (lex.curToken() == Token.END) {
            return ret;
        }
        throw new ParseException("Expected end " +
                "Offset: ", lex.curPos());
    }
}
