import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class AdventOfCode {
	public static void main(String[] args) throws FileNotFoundException {
		
		File file = new File("D:\\Java\\AdventOfCode\\in.txt");
		Scanner cin = new Scanner(file);
		Set<Integer> numbers = new HashSet<>();
		int n;
		while (cin.hasNextInt()) {
			n = cin.nextInt();
			if (numbers.contains(2020 - n)) {
				System.out.println("Part 1: " + n * (2020 - n));
			}
			numbers.add(n);
		}

		for (Integer i : numbers) {
			for (Integer j : numbers) {
				if (numbers.contains(2020 - i - j)) {
					System.out.println("Part 2: " + i * j * (2020 - i - j));
					System.exit(0);
				}
			}
		}
	}
}
