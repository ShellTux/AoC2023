import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.stream.Collectors;

public class Scratchcard {
	private int id;
	private ArrayList<Integer> winning;
	private ArrayList<Integer> numbers;


	public static void main (String[] args) {
		if (args.length < 1) return;

		File file = new File(args[0]);

		ArrayList<Scratchcard> scratchcards = new ArrayList<>();
		if(file.exists() && file.isFile()) {
			try {
				FileReader fileReader = new FileReader(file);
				BufferedReader bufferReader = new BufferedReader(fileReader);
				String line;
				while((line = bufferReader.readLine()) != null) {
					scratchcards.add(Scratchcard.parse(line));
				}
				bufferReader.close();
			} catch (FileNotFoundException ex) {
				System.out.println("Error opening file");
			} catch (IOException ex) {
				System.out.println("Error reading file");
			}
		} else {
			System.err.println("File doesn't exist");
		}

		printAll(scratchcards);

		int pilePoints = 0;
		for (Scratchcard scratchcard : scratchcards) {
			pilePoints += scratchcard.getScore();
		}

		System.out.println("Pile is worth: " + pilePoints);
	}

	private static void printAll(ArrayList<Scratchcard> scratchcards) {
		for (Scratchcard scratchcard : scratchcards) {
			System.out.println(scratchcard);
		}
	}

	public static Scratchcard parse(String line) {
		line = line.trim();

		String[] segments = line.split(":");
		int id = Integer.parseInt(segments[0].split(" +")[1]);

		String[] numbersSet = segments[1].trim().split("\\|");

		ArrayList<Integer> winning = new ArrayList<>();
		for (String number : numbersSet[0].split(" +")) {
			if (number.equals("")) continue;

			winning.add(Integer.parseInt(number));
		}

		ArrayList<Integer> numbers = new ArrayList<>();
		for (String number : numbersSet[1].split(" +")) {
			if (number.equals("")) continue;

			numbers.add(Integer.parseInt(number));
		}

		return new Scratchcard(id, winning, numbers);
	}

	private Scratchcard() {
		winning = new ArrayList<>();
		numbers = new ArrayList<>();
	}

	public Scratchcard(int id, ArrayList<Integer> winning, ArrayList<Integer> numbers) {
		this();
		this.id = id;
		this.winning = winning;
		this.numbers = numbers;
	}

	@Override
	public String toString() {
	    return String.format(
			    "Scratchpad: {\n" +
			    "\tid: %d,\n" +
			    "\tnumbers: %s,\n" +
			    "\twinning: %s,\n" +
			    "}",
			    id,
			    Arrays.toString(numbers.toArray()),
			    Arrays.toString(winning.toArray())
			    );
	}

	private ArrayList<Integer> getMatching() {
		ArrayList<Integer> matches = new ArrayList<>();

		for (Integer number : numbers) {
			Boolean included = false;
			for (Integer winningNumber : winning) {
				if (number != winningNumber) continue;

				included = true;
				break;
			}

			if (included) matches.add(number);
		}

		return matches;
	}

	private int getScore() {
		ArrayList<Integer> matches = getMatching();

		if (matches.size() == 0) return 0;

		return 1 << (matches.size() - 1);
	}
}
