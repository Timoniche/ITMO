import java.util.Arrays;
import java.util.List;


public class Tree {
    String node;
    List<Tree> children;
    //__________________________________________________
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_BLACK = "\u001B[30m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_YELLOW = "\u001B[33m";
    public static final String ANSI_BLUE = "\u001B[34m";
    public static final String ANSI_PURPLE = "\u001B[35m";
    public static final String ANSI_CYAN = "\u001B[36m";
    public static final String ANSI_WHITE = "\u001B[37m";
    //__________________________________________________

    public static String fixedLengthString(String string, int length) {
        return String.format("%1$" + length + "s", string);
    }

    public Tree(String node) {
        this.node = node;
    }

    public Tree(String node, Tree... children) {
        this.node = node;
        this.children = Arrays.asList(children);
    }

    public void drawTree(int indent) {
        String whiteSpaces = fixedLengthString("", indent);
        String edge = "∟--";
        if (children != null) {
            for (Tree ch : children) {
                System.out.print(whiteSpaces);
                System.out.print(edge);
                if (ch.node.equals("ε")) {
                    System.out.println(ANSI_YELLOW + ch.node + ANSI_RESET);
                } else if (ch.children == null) {
                    System.out.println(ANSI_GREEN + ch.node + ANSI_RESET);
                } else {
                    System.out.println(ANSI_RED + ch.node + ANSI_RESET);
                }
                ch.drawTree(indent + 3);
            }
        }

    }
}
