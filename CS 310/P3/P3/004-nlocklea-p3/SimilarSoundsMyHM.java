// *********************//
// DO NO CHANGE THIS FILE
// *********************//

/**
 * Do not change.
 */
class SimilarSoundsMyHM extends SimilarSounds
{	
	/**
	 * Do not change.
	 * @param args arguments to process
	 */
	public static void main(String args[]) {
		
		if (args.length == 0) {
			System.out.println("Wrong number of arguments, expecting:");
			System.out.println("java SimilarSoundsMyHM word1 word2 word3...");
			System.out.println("java SimilarSoundsMyHM word");
			System.exit(-1);
		} 
		
		wordToSound = new LinearProbingMap<>(400000); // maps <word, sound>
        soundGroupToSimilarWords = new LinearProbingMap<>(400000); // maps <sound-group, sorted list of words with similar sounds>

		processWords(args);
	}

}

