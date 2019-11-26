import java.io.IOException;
import java.io.InputStream;
import java.text.ParseException;

/**
 * Получает на вход строку и выдает последовательность терминалов (токенов)
 * S -> S or A | A
 * A -> A xor B | B
 * B -> B and C | C
 * C -> not D | D
 * D -> var | (S)
 * Терминалы: OR, XOR, AND, NOT, VAR, END
 */

enum Token {
    LPAREN, RPAREN, OR, XOR, AND, NOT, VAR, END
}

public class LexicalAnalyzer {
    private InputStream is;
    private int curChar;
    private char var;
    private int curPos;
    private Token curToken;

    public LexicalAnalyzer(InputStream is) throws ParseException {
        this.is = is;
        curPos = 0;
        nextChar();
    }

    private boolean isBlank(int c) {
        return c == ' ' || c == '\r' || c == '\n' || c == '\t';
    }

    private void nextChar() throws ParseException {
        curPos++;
        try {
            curChar = is.read();
        } catch (IOException e) {
            throw new ParseException(e.getMessage(), curPos);
        }
    }

    public void nextToken() throws ParseException {
        while (isBlank(curChar)) {
            nextChar();
        }
        switch (curChar) {
            case '(':
                nextChar();
                curToken = Token.LPAREN;
                break;
            case ')':
                nextChar();
                curToken = Token.RPAREN;
                break;
            case 'o':
                var = (char) curChar;
                nextChar();
                if (curChar == 'r') {
                    nextChar();
                    curToken = Token.OR;
                } else {
                    curToken = Token.VAR;
                }
                break;
            case 'x':
                var = (char) curChar;
                nextChar();
                if (curChar == 'o') {
                    nextChar();
                    nextChar();
                    curToken = Token.XOR;
                } else {
                    curToken = Token.VAR;
                }
                break;
            case 'a':
                var = (char) curChar;
                nextChar();
                if (curChar == 'n') {
                    nextChar();
                    nextChar();
                    curToken = Token.AND;
                } else {
                    curToken = Token.VAR;
                }
                break;
            case 'n':
                var = (char) curChar;
                nextChar();
                if (curChar == 'o') {
                    nextChar();
                    nextChar();
                    curToken = Token.NOT;
                } else {
                    curToken = Token.VAR;
                }
                break;
            case -1:
                curToken = Token.END;
                break;
            default:
                var = (char) curChar;
                nextChar();
                curToken = Token.VAR;
                if (curChar != '(' && curChar != ')' && !isBlank(curChar) && curChar != -1) {
                    throw new ParseException("Illegal character" + (char) curChar, curPos);
                }
        }
    }

    public Token curToken() {
        return curToken;
    }

    public int curPos() {
        return curPos;
    }

    public char getVar() {
        return var;
    }


}
