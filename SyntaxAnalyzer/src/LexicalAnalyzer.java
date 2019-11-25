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
            //OR, XOR, AND, NOT, VAR, END
            case '(':
                nextChar();
                curToken = Token.LPAREN;
                break;
            case ')':
                nextChar();
                curToken = Token.RPAREN;
                break;
            case 'o':
                nextChar();
                if (curChar == 'r') {
                    nextChar();
                    curToken = Token.OR;
                } else {
                    curToken = Token.VAR;
                }
                break;
            case 'x':
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
                nextChar();
                curToken = Token.VAR;
                if (curChar != '(' && curChar != ')' && !isBlank(curChar)) {
                    throw new ParseException("Illegal character" + (char) curChar, curPos);
                }
        }
    }

    public Token curToken() {
        return curToken;
    }

    public int curPos() {
        return curPos();
    }


}
