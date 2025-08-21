import java.util.ArrayList;
import java.util.List;
import java.util.Map;


/**
 * Add your description here.
 */
class SimilarSounds
{
	// ******DO NO CHANGE********//
		
	/**
	 * wordToSound maps each word to its corresponding sound.
     */
	static Map<String, String> wordToSound;
	
	/**
	 * soundGroupToSimilarWords maps each sound-group to a BST containing all the words that share that sound-group.
     */
	static Map<String, BST<String>> soundGroupToSimilarWords;

	/**
	 * Do not change.
	 * @param words one or more words passed on the command line.
     */		
	public static void processWords(String words[]) {
			
		ArrayList<String> lines = (ArrayList<String>)Extractor.readFile("word_to_sound.txt");
		populateWordToSoundMap(lines);
		populateSoundGroupToSimilarWordsMap(lines);
		
		if (words.length >= 2) {
			// check which of the words in the list have matching sounds 
			findSimilarWordsInList(words); 
		} else if (words.length == 1) {
			// get the list of words with matching sounds as this word
			findSimilarWordsTo(words[0]);
		} 
	}
	
	/**
	 *  Main Method.
	 *  
	 *  @param args args
	 */
	public static void main(String args[]) {
		if (args.length == 0) {
			System.out.println("Wrong number of arguments, expecting:");
			System.out.println("java SimilarSounds word1 word2 word3...");
			System.out.println("java SimilarSounds word");
			System.exit(-1);
		} 
		
		wordToSound = new java.util.HashMap<>(); // maps <word, sound>
        soundGroupToSimilarWords = new java.util.HashMap<>(); // maps <sound-group, sorted list of words with similar sounds>
		
		processWords(args);	
	}
	// ******DO NO CHANGE********//
	
	/**
	 * Given a list of all entries in the database, this method populates the wordToSound map
	 * as follows: the key is the word, and the value is the sound (i.e., the sequence of unisounds)
	 * For example, if the line entry is "moderated M AA1 D ER0 EY2 T IH0 D", the key would be "moderated"
	 * and the value would be "M AA1 D ER0 EY2 T IH0 D"
	 * To achieve this, you need to use the methods in the Extractor class 
	 * @param lines lines
	 */
	public static void populateWordToSoundMap(List<String> lines) {	
		//check to make sure its taking ALL values in the line
		String wordLine;
		for(int i = 0; i < lines.size(); i++){
			wordLine = lines.get(i);
			wordToSound.put(Extractor.extractWordFromLine(wordLine), Extractor.extractSoundFromLine(wordLine));
		}
		//System.out.println(wordToSound);
	}
	
	/**
	 * Given a list of all entries in the database, this method populates the 
	 * soundGroupToSimilarWords map as follows: the key is the sound-group, 
	 * and the value is a BST containing all the words that share that sound-group. 
	 * For example, if the line entry is "moderated M AA1 D ER0 EY2 T IH0 D", the key would 
	 * be "EY2 T IH0 D" and the value would be a BST containing "moderated" and all other
	 * words in the database that share the sound-group "EY2 T IH0 D"
	 * To achieve this, you need to use the methods in the Extractor class
	 * @param lines content of the database
	 */
	public static void populateSoundGroupToSimilarWordsMap(List<String> lines) {
		String wordLine, word, sound, soundGroup;
		wordLine = lines.get(0);
		BST<String> root = new BST<>();
		for(int i = 0; i < lines.size() ; i++){ //lines.size()
			wordLine = lines.get(i);
			word = Extractor.extractWordFromLine(wordLine);
			sound = Extractor.extractSoundFromLine(wordLine);
			soundGroup = Extractor.extractSoundGroupFromSound(sound);
			if(soundGroupToSimilarWords.get(soundGroup) == null){
				root = new BST<>();
				root.insert(word);
				//System.out.println("Soundgroup: " + soundGroup + " " + root.toString());
				soundGroupToSimilarWords.put(soundGroup, root);
			}
			else{
				BST<String> newroot = soundGroupToSimilarWords.get(soundGroup);
				newroot.insert(word);
				//System.out.println("Soundgroup: " + soundGroup + " " + newroot.toString());
			}
		}
		//all words are being put into 1 bst
		//System.out.println("Key = " + soundGroupToSimilarWords.get(Extractor.extractSoundGroupFromSound(Extractor.extractSoundFromLine(wordLine))));
	}
	
	/**
	 * Given a list of words, e.g., [word1, word2, word3, word4], this method checks whether 
	 * word1 is similar to word2, word3, and word4. Then checks whether word2 is similar 
	 * to word3 and word4, and finally whether word3 is similar to word4.
	 *
	 * <p>For example if the list contains: [calculated legislated hello world miscalleneous 
	 * miscalculated encapsulated LIBERATED Sophisticated perculated hello], 
	 * the output should exactly be as follows:
	 *
	 * <p>"calculated" sounds similar to: "legislated"
	 *	"hello" sounds similar to: none
	 *	"world" sounds similar to: none
	 *	"miscalculated" sounds similar to: "encapsulated" "LIBERATED" "Sophisticated"
	 *	Unrecognized words: "miscalleneous" "perculated"
     *
     * 	<p>Note however that: 
	 * a) if a word was already found similar, then it will be ignored hereafter
	 * b) the behavior is case insensitive
	 * c) the subsequent occurrence of a given word is ignored 
	 * d) words that couldn’t be found in the database are deemed unrecognizable 
	 * e) words are displayed within quotes
	 * @param words list of words to examine
	 */
	public static void findSimilarWordsInList(String words[]) {
		ArrayList<String> unrecognized =  new ArrayList<String>();
		Map<String,ArrayList<String>> wordList = new java.util.HashMap<>();
		ArrayList<String> usedWords = new ArrayList<String>();
		for(int i = 0; i < words.length; i++){
			//System.out.println(" | " + words[i]);
			//recognized = new BST<>();
			if(wordToSound.get(words[i].toUpperCase()) == null){
				unrecognized.add(words[i]);
				usedWords.add(words[i].toUpperCase());
				continue;
			}
			if(usedWords.contains(words[i].toUpperCase()) == false){
				wordList.put(words[i], new ArrayList<String>());
				usedWords.add(words[i].toUpperCase());
				String soundGroup = Extractor.extractSoundGroupFromSound((wordToSound.get(words[i].toUpperCase())));
				//System.out.print("\"" + words[i] + "\"" + " sounds similar to:");
				for(int j = i ; j < words.length -1; j ++){
					if(usedWords.contains(words[j].toUpperCase()) || wordToSound.get(words[j].toUpperCase()) == null){
						continue;
					}
					else{
						//System.out.println(Soundgroup + " comparing to: " + Extractor.extractSoundGroupFromSound((wordToSound.get(words[j].toUpperCase()))));
						if(soundGroup.compareTo(Extractor.extractSoundGroupFromSound((wordToSound.get(words[j].toUpperCase())))) == 0){
							wordList.get(words[i]).add(words[j]);
							//System.out.print(" \"" + words[j] + "\"");
							usedWords.add(words[j].toUpperCase());
						}
					}
				}
			}
			else{
				continue;
			}
		}
		//After this is a lot of output handling
		usedWords.clear();
		for(int i = 0; i < words.length; i ++){
			if(wordList.get(words[i]) != null && usedWords.contains(words[i]) == false){
				usedWords.add(words[i]);
				if(wordList.get(words[i]).size() == 0){
					System.out.println("\"" + words[i] + "\"" + " sounds similar to: " + "none");
				}
				else{
					System.out.print("\"" + words[i] + "\"" + " sounds similar to:");
					for(String word : wordList.get(words[i])){
						System.out.print(" \"" + word + "\"");
					}
					System.out.println();
				}
			}
		}
		System.out.print("Unrecognized words:");
		if(unrecognized.size() == 0){
			System.out.println(" none");
		}
		else{
			for(String word : unrecognized){
				System.out.print(" \"" + word + "\"");
			}
		}
	}

	/**
	 *Given a passed word this method prints all similarly sounding words in ascending order (including the passed word)
	 * For example:	java SimilarSounds dimension
	 * Words similar to "dimension": "ASCENSION" "ATTENTION" "CONTENTION" "CONVENTION" "DECLENSION"
	 * "DETENTION" "DIMENSION" "DISSENSION" "EXTENSION" "GENTIAN" "HENSCHEN" "LAURENTIAN"
	 * "MENTION" "PENSION" "PRETENSION" "PREVENTION" "RETENTION" "SUSPENSION" "TENSION"
     *
	 * <p>Note how the word passed as an argument must still appear in the output. 
	 * However, if it cannot be found in the database an appropriate error message should be displayed
	 * @param theWord word to process
	 */
	public static void findSimilarWordsTo(String theWord) {
		// go over the map, 
		//check the key, 
		//grab the sound group, 
		//compare to the input string
		//find match
		//output bst.tostring
		//System.out.println(theWord);
		String sound, soundGroup;
		sound = wordToSound.get(theWord.toUpperCase());
		if(sound == null){
			System.out.println("Unrecognized word: \"" + theWord + "\"");
		}
		else{
			soundGroup = Extractor.extractSoundGroupFromSound(sound);
			BST<String> newroot = soundGroupToSimilarWords.get(soundGroup);
			System.out.println("Words similar to \"" + theWord + "\": " + newroot.toString());
		}
	}
}
