import java.io.File;
import java.io.IOException;
import java.util.*;

public class AdventOfCode {

	public static void main(String[] args) throws IOException {

		File file = new File("D:\\Java\\AdventOfCode\\in.txt");
		Scanner cin = new Scanner(file);

		String inputLine;
		int Max = 0, Min = 1000;
		int[] SeatIDsFrequency = new int[1000];

		while (cin.hasNext()) {
			inputLine = cin.next();
			int front = 0, back = 127;
			int left = 0, right = 7;
			char lastFrontBack = 0, lastLeftRight = 0;

			for (char direction : inputLine.toCharArray()) {
				if (direction == 'F') {
					back = (front + back) / 2;
					lastFrontBack = direction;
				} else if (direction == 'B') {
					front = ((front + back) / 2 + 1);
					lastFrontBack = direction;
				}
				if (direction == 'L') {
					right = (left + right) / 2;
					lastLeftRight = direction;
				} else if (direction == 'R') {
					left = ((left + right) / 2 + 1);
					lastLeftRight = direction;
				}
			}

			int seatID = 8; // the 8 columns
			seatID *= lastFrontBack == 'F' ? front : back; // row
			seatID += lastLeftRight == 'L' ? left : right; // column

			SeatIDsFrequency[seatID]++;

			Min = Math.min(seatID, Min);
			Max = Math.max(seatID, Max);
		}

		System.out.println("Part 1: " + Max);
		for (int i = Min; i <= Max; i++) {
			if (SeatIDsFrequency[i] == 0) {
				System.out.println("Part 2: " + i);
			}
		}
	}
}
