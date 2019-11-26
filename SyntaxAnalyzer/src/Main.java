import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.nio.charset.Charset;
import java.text.ParseException;

public class Main {
    public static final String ANSI_BLUE = "\u001B[34m";
    public static final String ANSI_RESET = "\u001B[0m";

    static void dfs(Tree v) {
        if (v.children == null) {
            if (!v.node.equals("ε")) {
                System.out.print(ANSI_BLUE + v.node + " " + ANSI_RESET);
            }
            return;
        }
        for (Tree ch : v.children) {
            dfs(ch);
        }
    }

    static void testLexer(InputStream is) {
        try {
            LexicalAnalyzer lex = new LexicalAnalyzer(is);
            lex.nextToken();
            while (lex.curToken() != Token.END) {
                System.out.print(lex.curToken() + " ");
                lex.nextToken();
            }
        } catch (ParseException e) {
            System.out.println(e.getMessage());
        }

    }

    public static void main(String[] args) {
        String[] strings = {" (a and b) or not (c xor (a or not b))",
                "a and b", " a or c xor p and v", "((a and a))"};

        for (String string : strings) {
            InputStream inputStream = new ByteArrayInputStream(string.getBytes(Charset.forName("UTF-8")));
            try {
                Parser parser = new Parser();
                Tree root = parser.parse(inputStream);
                dfs(root);
                System.out.println();
                root.drawTree(2);
            } catch (ParseException e) {
                System.out.println(e.getMessage());
            }
            System.out.println(ANSI_BLUE + "____________________________________" + ANSI_RESET);
        }
    }
}
