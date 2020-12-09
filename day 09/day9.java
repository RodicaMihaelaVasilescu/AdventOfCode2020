import java.io.File;
import java.io.IOException;
import java.util.*;

public class AdventOfCode {

	public static void main(String[] args) throws IOException {

		File file = new File("D:\\Java\\AdventOfCode\\in.txt");
		Scanner cin = new Scanner(file);

		int preamble = 25;
		Vector<Integer> numbers = new Vector<Integer>();
		int n, offset = 0, solution = 0;

		for (int i = 0; i < preamble; i++) {
			n = cin.nextInt();
			numbers.add(n);
		}

		offset = 0;
		while (cin.hasNextInt()) {
			{
				n = cin.nextInt();

				boolean valid = false;
				for (int i = offset; i < numbers.size(); i++) {
					for (int j = i + 1; j < numbers.size(); j++) {
						if (numbers.get(i) + numbers.get(j) == n) {
							valid = true;
						}
					}
				}

				offset++;
				numbers.add(n);

				if (!valid) {
					System.out.println("Part 1: " + n);
					solution = n;
				}
			}

			for (int i = 0; i < numbers.size(); i++) {
				int sum = 0, Min = 1999999999, Max = 0;
				for (int j = i; j < numbers.size() && sum < solution; j++) {
					Min = Math.min(numbers.get(j), Min);
					Max = Math.max(numbers.get(j), Max);
					sum += numbers.get(j);
					if (sum == solution && numbers.get(j) != solution) {
						System.out.println("Part 2: " + (Min + Max));
						System.exit(0);
					}
				}
			}
		}

	}
}
