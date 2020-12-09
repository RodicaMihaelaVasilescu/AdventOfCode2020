import java.io.File;
import java.io.IOException;
import java.util.*;

class Pair {
	public Pair(String instr, int value) {
		Instr = instr;
		Value = value;
	}

	public String Instr;
	public Integer Value;
};

public class AdventOfCode {

	static long run(Vector<Pair> v) {
		Vector<Integer> visited = new Vector<Integer>();/* (v.size(), 0); */
		for (int i = 0; i < v.size(); i++) {
			visited.add(0);
		}
		Long acc = (long) 0;
		for (int i = 0; i != v.size(); i++) {
			if (visited.get(i) != 0) {
				return acc;
			}
			visited.set((i), 1);

			String instr = v.get(i).Instr;
			int val = v.get(i).Value;

			if (instr == "nop") {
				continue;
			} else if (instr.equals("acc")) {
				acc += val;
			} else if (instr.equals("jmp")) {
				i += val - 1;
			}
		}
		System.out.println("Part 2: " + acc);
		return acc;
	}

	public static void main(String[] args) throws IOException {

		File file = new File("D:\\Java\\AdventOfCode\\in.txt");
		Scanner cin = new Scanner(file);

		String instr;
		int value;
		Vector<Pair> instructions = new Vector<Pair>();
		while (cin.hasNext()) {

			instr = cin.next();

			value = cin.nextInt();

			instructions.add(new Pair(instr, value));
		}
		System.out.println("Part 1: " + run(instructions));

		for (Pair i : instructions) {
			if (i.Instr.equals("jmp")) {
				i.Instr = "nop";
			} else if (i.Instr.equals("nop")) {
				i.Instr = "jmp";
			}

			run(instructions);

			if (i.Instr.equals("jmp")) {
				i.Instr = "nop";
			} else if (i.Instr.equals("nop")) {
				i.Instr = "jmp";
			}
		}

	}
}
