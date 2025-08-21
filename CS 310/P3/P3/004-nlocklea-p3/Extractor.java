import java.util.StringTokenizer;
import java.lang.String;
import java.util.ArrayList;
import java.util.List;
import java.io.*;

/**
 *  A helper class containing functions that you should use in SimilrSounds.java
 *  Note that in your implementations you could use StringTokenizer and String.split()
 *
 */
 
class Extractor
{
	// **************//
	// DO NO CHANGE
	
	/**
	 *  Reads a text file one line at a time and returns the lines in a List.
	 *  This function is provided to you, no need to change it
	 *  @param fileName file name
	 *  @return return
	 */
	public static List<String> readFile(String fileName) {
		
		File file = new File(fileName);
        ArrayList<String> list = new ArrayList<String>();
			
		try {
			BufferedReader br = new BufferedReader(new FileReader(file));
			String st;
			while ((st = br.readLine()) != null) {
				list.add(st);
			}
		} catch (IOException e) {
			System.out.println(e);
		}
		return list;
	}
	// DO NO CHANGE
	// **************//
	
	
	
	/**
	 * Given a line of text, this method must return the first token  
	 * In the context of this project, it will return the Word. For Example: 
	 * Input:	"moderated M AA1 D ER0 EY2 T IH0 D"
	 * Return: 	"moderated"
	 * Input:	""
	 * Return: 	""
	 * @param line line
	 * @return string
	 */
	public static String extractWordFromLine(String line) { ;
		String[] splitLine = line.split(" ");
		//System.out.println("Length: " + splitLine.length);
		return splitLine[0];
	}
	
	
	/**
	 * Given a line of text, this method must return all tokens except the first one. 
	 * In the context of this project, it will return the Sound (sequence of unisounds). For Example: 
	 * Input:	"moderated M AA1 D ER0 EY2 T IH0 D"
	 * Return: 	"M AA1 D ER0 EY2 T IH0 D"
	 * Input:	""
	 * Return: 	""
	 * @param line line
	 * @return string
	 */
	public static String extractSoundFromLine(String line) { 
		String[] splitLine = line.split(" ",2);
		if(splitLine.length == 1){
			return splitLine[0];
		}
		//System.out.println(splitLine.length);
		//System.out.println(splitLine[0] + " " + splitLine[1]);
		if(splitLine.length >= 2){
			//System.out.println("|" + splitLine[1] + "|");
			return splitLine[1].trim();
		}
		else{
			return splitLine[0];
		}
	}
	
	
	/**
	 * Given a string representing the sound of a word (sequence of unisounds), 
	 * this method must return the sound-group, i.e., "the trailing sequence of unisounds starting 
	 * from the last occurring most emphasized unisound". For Example: 
	 * Input:	""M AA1 D ER0 EY2 T IH0 D""
	 * Return: 	"EY2 T IH0 D"
	 * Input:	"S EY1 N T M AA1 R T IH0 N"
	 * Return: 	"AA1 R T IH0 N"
	 * Input:	""
	 * Return: 	""
	 * @param sound sound
	 * @return string
	 */
	public static String extractSoundGroupFromSound(String sound) { 
		String[] splitLine = sound.split(" ");
		boolean check = false;
		int index = 0;
		int highest = 0;
		int current = 0;
		//System.out.println("Length: " + splitLine.length);
		if(splitLine.length == 1){
			return splitLine[0];
		}
		//System.out.println("Entry 1 : " + splitLine[1] + "||");
		//System.out.println("Entry -1 : " + splitLine[splitLine.length-1] + "||");
		for(int i = 1; i < splitLine.length; i++){
			if(Character.isDigit(splitLine[i].charAt(splitLine[i].length()-1)) == true){
				//System.out.println("Entry: " + splitLine[i] + "||" + "Char: " + splitLine[i].charAt(splitLine[i].length()-1));
				check = true;
				current = Character.getNumericValue(splitLine[i].charAt(splitLine[i].length()-1));
				//System.out.println(current);
				if(current >= highest){
					highest = current;
					index = i;
				}
			}	
		}
		if(check == true){
			splitLine = sound.split(" ", index + 1 );
			//System.out.println("Index: " + index + " Portion: "+ splitLine[splitLine.length-1]);
			return splitLine[splitLine.length-1];
		}
		if( check== false){
			return sound;
		}
		/*
		if(check == false){
			//System.out.println("splitline: " + splitLine.toString());
			System.out.println("splitline split: " + splitLine[index].toString());
			System.out.println("soundgroup: " + splitLine[index]);
			return sound;
		}
		splitLine = sound.split(" ", index);
		//System.out.println("splitline: " + splitLine.toString());
		System.out.println("splitline split: " + splitLine[index].toString());
		//System.out.println("soundgroup: " + splitLine[index]);
		return sound;
		*/
		return sound;
	}


	/**
	 *  Main Method For Your Testing -- Edit all you want.
	 *  
	 *  @param args not used
	 */
	public static void main(String args[]) {
		int location;
		String line, word, sound, soundGroup;
		List lines = readFile("word_to_sound.txt");

		location = 61905;
		line = lines.get(location).toString();
		if (line.equals("ENTHUSIASTICALLY  IH0 N TH UW2 Z IY0 AE1 S T IH0 K L IY0")) {
			System.out.println("Yay1");
		}
		word = extractWordFromLine(line);
		if (word.equals("ENTHUSIASTICALLY")) {
			System.out.println("Yay2");
		}
		sound = extractSoundFromLine(line);
		if (sound.equals("IH0 N TH UW2 Z IY0 AE1 S T IH0 K L IY0")) {
			System.out.println("Yay3");
		}
		soundGroup = extractSoundGroupFromSound(sound);
		if (soundGroup.equals("UW2 Z IY0 AE1 S T IH0 K L IY0")) {
			System.out.println("Yay4");
		}

		location = 63;
		line = lines.get(location).toString();
		if (line.equals("ST_MARTIN  S EY1 N T M AA1 R T IH0 N")) {
			System.out.println("Yay5");
		}
		word = extractWordFromLine(line);
		if (word.equals("ST_MARTIN")) {
			System.out.println("Yay6");
		}
		sound = extractSoundFromLine(line);
		if (sound.equals("S EY1 N T M AA1 R T IH0 N")) {
			System.out.println("Yay7");
		}
		soundGroup = extractSoundGroupFromSound(sound);
		if (soundGroup.equals("AA1 R T IH0 N")) {
			System.out.println("Yay8");
		}
		
		line = "";
		word = extractWordFromLine(line);
		if (word.equals("")) {
			System.out.println("Yay9");
		}
		sound = extractSoundFromLine(line);
		if (sound.equals("")) {
			System.out.println("Yay10");
		}
		soundGroup = extractSoundGroupFromSound(sound);
		if (soundGroup.equals("")) {
			System.out.println("Yay11");
		}
		
		soundGroup = extractSoundGroupFromSound("S EY N T M AA R T IH N");
		if (soundGroup.equals("S EY N T M AA R T IH N")) {
			System.out.println("Yay12");
		}
	}
}
