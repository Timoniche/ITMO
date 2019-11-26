import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.nio.charset.Charset;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static final String ANSI_BLUE = "\u001B[34m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_PURPLE = "\u001B[35m";
    public static final String ANSI_RESET = "\u001B[0m";

    static void dfs(Tree v, StringBuilder sb) {
        if (v.children == null) {
            if (!v.node.equals("ε")) {
                if (v.node.equals("(")) sb.append(v.node);
                else if (v.node.equals(")")) {
                    sb.deleteCharAt(sb.length() - 1);
                    sb.append(v.node).append(" ");
                } else sb.append(v.node).append(" ");
            }
            return;
        }
        for (Tree ch : v.children) {
            dfs(ch, sb);
        }
    }

//    static void dfsBrackets(Tree v, StringBuilder sb) {
//        if (v.children == null) {
//            if (!v.node.equals("ε")) {
//                sb.append(v.node).append(" ");
//            }
//            return;
//        }
//        for (Tree ch : v.children) {
//            sb.append(ch.node).append(" ");
//            sb.append("( ");
//            dfs(ch, sb);
//            sb.append(" )");
//        }
//    }

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
//        String[] strings = {"", "a and b and c", " (a and b) or not (c xor (a or not b))",
//                "a and b", " a or c xor p and v", "((a and a)", "(b and e))",
//                " a and ", " and b", "and", "or v", "v or"};
        String[] strings = {"a or b xor c", "a xor b or c"};

        for (String string : strings) {
            ArrayList<String> tokens = new ArrayList<String>();
            InputStream inputStream = new ByteArrayInputStream(string.getBytes(Charset.forName("UTF-8")));
            try {
                Parser parser = new Parser();
                Tree root = parser.parse(inputStream);
                Scanner tokenize = new Scanner(string);
                while (tokenize.hasNext()) {
                    tokens.add(tokenize.next());
                }
                StringBuilder builderAns = new StringBuilder();
                for (String str : tokens) {
                    builderAns.append(str).append(" ");
                }
                System.out.println(ANSI_GREEN + builderAns.toString() + ANSI_RESET);
                StringBuilder builderDfs = new StringBuilder();
                dfs(root, builderDfs);
                System.out.println(ANSI_BLUE + builderDfs.toString() + ANSI_RESET);
                if (builderAns.toString().equals(builderDfs.toString())) {
                    System.out.println(ANSI_PURPLE + "test passed" + ANSI_RESET);
                } else {
                    System.out.println(ANSI_RED + "test not passed" + ANSI_RESET);
                }
                //StringBuilder builderDfsBrackets = new StringBuilder();
                //dfsBrackets(root, builderDfsBrackets);
                //System.out.println(builderDfsBrackets.toString());
                System.out.println();

                root.drawTree(2);
            } catch (ParseException e) {
                System.out.println(e.getMessage() + e.getErrorOffset());
            }
        }
    }
}
