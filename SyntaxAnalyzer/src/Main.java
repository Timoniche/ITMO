import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.nio.charset.Charset;
import java.text.ParseException;

public class Main {
    public static void main(String[] args) {
        String string = " (a and b) or not (c xor (a or not b))";
        InputStream inputStream = new ByteArrayInputStream(string.getBytes(Charset.forName("UTF-8")));
        try {
            LexicalAnalyzer LA = new LexicalAnalyzer(inputStream);
            LA.nextToken();
            while (LA.curToken() != Token.END) {
                System.out.print(LA.curToken() + " ");
                LA.nextToken();
            }
        } catch (ParseException e) {
            System.out.println(e.getMessage());
        }
    }
}
