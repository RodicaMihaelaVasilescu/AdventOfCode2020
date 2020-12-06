import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class AdventOfCode {
	
	public static void main(String[] args) throws IOException {

		File file = new File("D:\\Java\\AdventOfCode\\in.txt");
		BufferedReader cin = new BufferedReader(new FileReader(file));

		 String inputLine="";
		  Set<Character> allQuestions = new HashSet<Character>(); 
		  Map<Character, Integer> questionsFrequencyPerGroup = new HashMap<Character, Integer> (); 
		  int numberOfAllQuestions = 0;
		  int numberOfAllQuestionsPerGroup = 0;
		  int numberOfAllAnsweredQuestions = 0;
		  
		  inputLine =  cin.readLine();
		  while (inputLine!=null)
		  {
		    if (!inputLine.isEmpty())
		    {
		      for (char c : inputLine.toCharArray())
		      {
		        allQuestions.add(c);
		        questionsFrequencyPerGroup.put(c, questionsFrequencyPerGroup.getOrDefault(c, 0)+1);
		      }
		      numberOfAllQuestionsPerGroup++;
		    }
		    else
		    {
		      // questions to which anyone answered "yes";
		      numberOfAllQuestions += allQuestions.size();

		      for (Map.Entry<Character, Integer> questionFrequency : questionsFrequencyPerGroup.entrySet())
		      {
		        if (questionFrequency.getValue() == numberOfAllQuestionsPerGroup)
		        {
		          // questions to which everyone answered "yes"!
		          numberOfAllAnsweredQuestions++;
		        }
		      }

		      numberOfAllQuestionsPerGroup = 0;
		      questionsFrequencyPerGroup.clear();
		      allQuestions.clear();
		    }

			inputLine =  cin.readLine();
		  }

		  // questions to which anyone answered "yes";
		  numberOfAllQuestions += allQuestions.size();

		  for (Map.Entry<Character, Integer> questionFrequency : questionsFrequencyPerGroup.entrySet())
		  {
		    if (questionFrequency.getValue() == numberOfAllQuestionsPerGroup)
		    {
		      // questions to which everyone answered "yes"!
		      numberOfAllAnsweredQuestions++;
		    }
		  }

		System.out.println("Part 1: " + numberOfAllQuestions);
		System.out.println("Part 2: " + numberOfAllAnsweredQuestions);
	}
}
