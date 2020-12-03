import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class AdventOfCode {

	static int getNumberOfTrees(Vector<String> map, int right, int left) {
		int line = 0, column = 0, numberOfTrees = 0;
		int n = map.size(), m = map.elementAt(0).length();

		while (line < n) {
			if (map.elementAt(line).charAt(column % m) == '#') {
				numberOfTrees++;
			}

			column += right;
			line += left;
		}
		return numberOfTrees;
	}

	public static void main(String[] args) throws FileNotFoundException {

		File file = new File("D:\\Java\\AdventOfCode\\in.txt");
		Scanner cin = new Scanner(file);

		Vector<String> input = new Vector<String>();
		String inputLine;

		while (cin.hasNext()) {
			inputLine = cin.next();
			input.add(inputLine);
		}

		System.out.println("Part 1: " + getNumberOfTrees(input, 3, 1));
		System.out.println("Part 2: " + 1l * getNumberOfTrees(input, 1, 1) * getNumberOfTrees(input, 3, 1)
				* getNumberOfTrees(input, 5, 1) * getNumberOfTrees(input, 7, 1) * getNumberOfTrees(input, 1, 2));
	}
}
