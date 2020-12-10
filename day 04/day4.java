import java.io.File;
import java.io.IOException;
import java.util.*;

public class AdventOfCode {

	static String myFind1(String value, String inputLine, String fieldName) {
		if (!value.equals("")) {
			return value;
		}
		int fieldValuePosition = inputLine.indexOf(fieldName);
		if (fieldValuePosition != -1) {
			fieldValuePosition += fieldName.length() + 1;
			int delimiterPosition = inputLine.indexOf(" ", fieldValuePosition);
			return inputLine.substring(fieldValuePosition, delimiterPosition);
		} else
			return "";
	}

	static String myFind2(String value, String inputLine, String fieldName) {
		if (!value.equals("")) {
			return value;
		}

		int fieldValuePosition = inputLine.indexOf(fieldName);

		if (fieldValuePosition != -1) {
			fieldValuePosition += fieldName.length() + 1;
			int delimiterPosition = inputLine.indexOf(" ", fieldValuePosition);
			value = inputLine.substring(fieldValuePosition, delimiterPosition);

			if (fieldName == "byr") {
				// byr(Birth Year) - four digits; at least 1920 and at most 2002.
				int year;
				try {
					year = Integer.valueOf(value);
				} catch (NumberFormatException nfe) {
					return "";
				}
				return year >= 1920 && year <= 2002 ? value : "";
			} else if (fieldName == "iyr") {
				// iyr(Issue Year) - four digits; at least 2010 and at most 2020.
				int year;
				try {
					year = Integer.valueOf(value);
				} catch (NumberFormatException nfe) {
					return "";
				}
				return year >= 2010 && year <= 2020 ? value : "";
			}
			if (fieldName == "eyr") {
				// eyr(Expiration Year) - four digits; at least 2020 and at most 2030.
				int year;
				try {
					year = Integer.valueOf(value);
				} catch (NumberFormatException nfe) {
					return "";
				}
				return year >= 2020 && year <= 2030 ? value : "";
			}
			if (fieldName == "hgt") {
				// hgt(Height) - a number followed by either cm or in:
				// If cm, the number must be at least 150 and at most 193.
				// If in, the number must be at least 59 and at most 76.
				if (value.length() < 4) {
					return "";
				}
				String unit = value.substring(value.length() - 2, value.length());
				if (!unit.equals("cm") && !unit.equals("in")) {
					return "";
				}
				int height;
				try {
					height = Integer.valueOf(value.substring(0, value.length() - 2));
				} catch (NumberFormatException nfe) {
					return "";
				}
				if (unit.equals("cm") && height >= 150 && height <= 193
						|| unit.equals("in") && height >= 59 && height <= 76) {
					return value;
				}

				return "";
			} else if (fieldName == "hcl") {
				// hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
				if (value.charAt(0) != '#' || value.length() != 7) {
					return "";
				}

				for (int i = 1; i < value.length(); i++) {
					char ch = value.charAt(i);
					if (!(ch >= '0' && ch <= '9') && !(ch >= 'a' && ch <= 'f')) {
						return "";
					}
					return value;
				}
			} else if (fieldName == "ecl") {
				// ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
				if (!value.equals("amb") && !value.equals("blu") && !value.equals("brn") && !value.equals("gry")
						&& !value.equals("grn") && !value.equals("hzl") && !value.equals("oth")) {
					return "";
				}
				return value;
			} else if (fieldName == "pid") {
				// pid(Passport ID) - a nine - digit number, including leading zeroes.
				if (value.length() != 9) {
					return "";
				}
				for (char ch : value.toCharArray()) {
					if (ch < '0' || ch > '9') {
						return "";
					}
				}

				return value;
			}
			return value;
		} else
			return "";
	}

	public static void main(String[] args) throws IOException {

		File file = new File("D:\\Java\\AdventOfCode\\in.txt");
		Scanner cin = new Scanner(file);

		String inputLine;
		Map<String, String> PassportPart1 = new HashMap<String, String>();
		Map<String, String> PassportPart2 = new HashMap<String, String>();

		Vector<String> passportFields = new Vector<String>();

		passportFields.add("byr");
		passportFields.add("iyr");
		passportFields.add("eyr");
		passportFields.add("hgt");
		passportFields.add("hcl");
		passportFields.add("ecl");
		passportFields.add("pid");
		passportFields.add("cid");

		int solution1 = 0, solution2 = 0;
		while (cin.hasNext()) {
			{
				inputLine = cin.nextLine();
				if (!inputLine.equals("")) {
					inputLine += " ";
					for (String p : passportFields) {
						PassportPart1.put(p, myFind1(PassportPart1.getOrDefault(p, ""), inputLine, p));
						PassportPart2.put(p, myFind2(PassportPart2.getOrDefault(p, ""), inputLine, p));
					}
				} else {
					boolean isValid1 = true, isValid2 = true;

					for (String field : passportFields) {
						if (field != "cid") {
							if (PassportPart1.get(field) == "") {
								isValid1 = false;
							}
							if (PassportPart2.get(field) == "") {
								isValid2 = false;
							}
						}
					}

					if (isValid1) {
						solution1++;
					}
					if (isValid2) {
						solution2++;
					}
					PassportPart1.clear();
					PassportPart2.clear();
				}
			}
		}
		System.out.println("Part 1: " + solution1);
		System.out.println("Part 2: " + solution2);
	}
}
