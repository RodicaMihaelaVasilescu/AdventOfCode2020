import java.io.File;
import java.io.IOException;
import java.util.*;

class Point {
	public Point(int x, int y) {
		X = x;
		Y = y;
	}

	public int X;
	public int Y;
};

public class AdventOfCode {

	public static void main(String[] args) throws IOException {

		//       	  0  1  2  3
		//       	  E  S  W  N                          
		int lin[] = { 0, 1, 0, -1 };
		int col[] = { 1, 0, -1, 0 };

		Map<Character, Integer> CharToInt = new HashMap<Character, Integer>();
		CharToInt.put('E', 0);
		CharToInt.put('S', 1);
		CharToInt.put('W', 2);
		CharToInt.put('N', 3);		   
		
		File file = new File("D:\\Java\\AdventOfCode\\in.txt");
		Scanner cin = new Scanner(file);

		// The ship starts by facing east
		int direction = CharToInt.get('E');

		Point point1 = new Point(0, 0);
		Point point2 = new Point(0, 0);

		// the waypoint starts 1 unit north (-) and 10 units east (+)
		Point waypoint = new Point(-1, 10);

		char s;
		int n;
		while (cin.hasNext()) {
			String line = cin.next();
			s = line.charAt(0);
			n = Integer.valueOf(line.substring(1));
			if (s == 'F') {
				// ---------------- 1st part -------------------
				point1.X += n * lin[direction];
				point1.Y += n * col[direction];
				// ---------------- 2nd part -------------------
				point2.X += n * waypoint.X;
				point2.Y += n * waypoint.Y;
			} else if (s == 'E' || s == 'S' || s == 'W' || s == 'N') {
				// ---------------- 1st part -------------------
				point1.X += n * lin[CharToInt.get(s)];
				point1.Y += n * col[CharToInt.get(s)];
				// ---------------- 2nd part -------------------
				waypoint.X += n * lin[CharToInt.get(s)];
				waypoint.Y += n * col[CharToInt.get(s)];
			}
			// right rotation
			else if (s == 'R' && n == 90 || s == 'L' && n == 270) {
				// ---------------- 1st part -------------------
				++direction;
				direction %= 4;
				// ---------------- 2nd part -------------------
				waypoint.X *= -1;
				waypoint = new Point(waypoint.Y, waypoint.X);
			}
			// left rotation
			else if (s == 'L' && n == 90 || s == 'R' && n == 270) {
				// ---------------- 1st part -------------------
				if (--direction < 0) {
					direction = 3;
				}
				// ---------------- 2nd part -------------------
				waypoint.Y *= -1;
				waypoint = new Point(waypoint.Y, waypoint.X);
			}
			// 180 rotation
			else if (s == 'R' && n == 180 || s == 'L' && n == 180) {
				// ---------------- 1st part -------------------
				direction += 2;
				direction %= 4;
				// ---------------- 2nd part -------------------
				waypoint.X *= -1;
				waypoint.Y *= -1;
			}
		}

		System.out.println("Part 1: " + (Math.abs(point1.X) + Math.abs(point1.Y)));
		System.out.println("Part 2: " + (Math.abs(point2.X) + Math.abs(point2.Y)));
	}
}
