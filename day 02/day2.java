import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class AdventOfCode {
	public static void main(String[] args) throws FileNotFoundException {

		File file = new File("D:\\Java\\AdventOfCode\\in.txt");
		Scanner cin = new Scanner(file);

		int solutionPart1 = 0, solutionPart2 = 0;
		int lowest, highest;
		char passwordPolicy;
		String password, numbers;

		while (cin.hasNext()) {

			numbers = cin.next();
			int index = numbers.indexOf('-');
			lowest = Integer.parseInt((String) numbers.subSequence(0, index));
			highest = Integer.parseInt((String) numbers.subSequence(index + 1, numbers.length()));
			passwordPolicy = (cin.next()).charAt(0);
			password = cin.next();

			int count = 0;
			for (int i = 0; i < password.length(); i++) {
				if (password.charAt(i) == passwordPolicy) {
					count++;
				}
			}

			if (count >= lowest && count <= highest) {
				solutionPart1++;
			}

			if (password.charAt(lowest - 1) == passwordPolicy && password.charAt(highest - 1) != passwordPolicy
					|| password.charAt(lowest - 1) != passwordPolicy
							&& password.charAt(highest - 1) == passwordPolicy) {
				solutionPart2++;
			}
		}

		System.out.println("Part 1: " + solutionPart1);
		System.out.println("Part 2: " + solutionPart2);
	}
}
