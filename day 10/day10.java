import java.io.File;
import java.io.IOException;
import java.util.*;

public class AdventOfCode {

	public static void main(String[] args) throws IOException {

		File file = new File("D:\\Java\\AdventOfCode\\in.txt");
		Scanner cin = new Scanner(file);

		Vector<Integer> jolts = new Vector<Integer>();
		jolts.add(0);

		int adapter, MaxAdapter = 0;

		while (cin.hasNextInt()) {
			adapter = cin.nextInt();
			MaxAdapter = Math.max(MaxAdapter, adapter);
			jolts.add(adapter);
		}

		jolts.add(MaxAdapter + 3);
		Collections.sort(jolts);

		int oneJoltDiff = 0, threeJoltsDiff = 0;
		for (int i = 1; i < jolts.size(); i++) {
			if (jolts.get(i) - jolts.get(i - 1) == 1) {
				oneJoltDiff++;
			} else if (jolts.get(i) - jolts.get(i - 1) <= 3) {
				threeJoltsDiff++;
			}
		}

		System.out.println("Part 1: " + oneJoltDiff * threeJoltsDiff);

		jolts.add(jolts.get(jolts.size() - 1) + 3);

		// number of distinct ways you can arrange the adapters
		Map<Integer, Long> numberOfDistinctWays = new HashMap<Integer, Long>();
		numberOfDistinctWays.put(0, 1l * 1);

		for (int i = 0; i < jolts.size(); i++) {
			for (int j = i + 1; j < jolts.size() && jolts.get(j) - jolts.get(i) <= 3; j++) {
				Long valNumberWaysI = numberOfDistinctWays.getOrDefault(i,1l*0);
				Long valNumberWaysJ = numberOfDistinctWays.getOrDefault(j,1l*0);
				numberOfDistinctWays.put(j, valNumberWaysI + valNumberWaysJ);
			}
		}
		
		System.out.println("Part 2: " + numberOfDistinctWays.get(jolts.size() - 1));
	}
}
