import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.Random;
import java.util.Scanner;

public class CommonTester {
	public static void main(String[] args) throws Exception {
		String fileName = "fileName";
		int n = 5;
		int m = 5;
		Random rnd = new Random(225756123);
		for (int k = 0;; k++) {
			PrintWriter out = new PrintWriter(new FileWriter(fileName + ".in"));
			// генерация тестов
			out.close();

			long start = System.nanoTime();
			firstClass.main(null);
			System.out.println("first program " + ((double) System.nanoTime() - start) / 1_000_000_000);

			start = System.nanoTime();
			secondClass.main(null);
			System.out.println("second program " + ((double) System.nanoTime() - start) / 1_000_000_000);

			System.out.println();

			Scanner in = new Scanner(new File(fileName + ".out"));
			Scanner in1 = new Scanner(new File(fileName + "1.out"));
			for (int counter = 0;; counter++) {
				if (in.hasNextLine() && in1.hasNextLine()) {
					String s = in.nextLine();
					String s1 = in1.nextLine();
					if (in.nextLine().equals(in1.nextLine())) {
						System.out.println("error: line " + counter + " is different");
						System.exit(0);
					}
				} else if (in.hasNextLine() || in1.hasNextLine()) {
					System.out.println("error: one of the files is shorter then the other (" + counter + " line)");
					System.exit(0);
				}
			}
			in.close();
			in1.close();
		}
	}
}
