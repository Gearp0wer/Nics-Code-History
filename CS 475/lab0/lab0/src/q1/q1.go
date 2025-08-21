Nicholas Locklear (nlocklea)
package q1

import (
	"fmt"
	"io/ioutil"
	"log"
	"regexp"
	"sort"
	"strings"
)

// Find the top K most common words in a text document.
// 	path: location of the document
//	numWords: number of words to return (i.e. k)
//	charThreshold: character threshold for whether a token qualifies as a word,
//		e.g. charThreshold = 5 means "apple" is a word but "pear" is not.
// Matching is case insensitive, e.g. "Orange" and "orange" is considered the same word.
// A word comprises alphanumeric characters only. All punctuation and other characters
// are removed, e.g. "don't" becomes "dont".
// You should use `checkError` to handle potential errors.



func TopWords(path string, numWords int, charThreshold int) []WordCount {
	// TODO: implement me
	// HINT: You may find the `strings.Fields` and `strings.ToLower` functions helpful
	// HINT: To keep only alphanumeric characters, use the regex "[^0-9a-zA-Z]+"
	//2 arrays: one to hold top K words at end, one to hold all words found as we go. 
	//follow path and open file, split words. check if word is appropriate length, if so, tolower and use helper to insert in array
	var counter = 0
	log.Printf("\n%s:%d\n", path, charThreshold)
	content, err := ioutil.ReadFile(path)
	checkError(err)
	text := strings.ToLower(string(content))
	re := regexp.MustCompile(`[^0-9a-zA-Z']`)
	cleanedText := re.ReplaceAllString(text, " ")
	reTrim := regexp.MustCompile(`\b'|'$`)
	cleanedText = reTrim.ReplaceAllString(cleanedText, "")
	words := strings.Fields(cleanedText)
	var listofUnique []WordCount //est slice


	for i := 0; i < len(words); i++ {
		var wordUnit = words[i]
		var catchflag int = 0
		//log.Printf("[WORDUNIT]: %s\n", wordUnit)
		if len(wordUnit)>=charThreshold {
			if counter == 0  {
				listofUnique = append(listofUnique, WordCount{wordUnit, 1})
				catchflag = 1
				counter +=1
				continue
			//log.Printf("[WORDUNIT]: %s\n", wordUnit)
			}
			if counter != 0{
				for j:=0; j<counter; j++{
					if listofUnique[j].Word == wordUnit {
						//log.Printf("[wordunit: j, i]: %s %d____%d\n", wordUnit, j,i)
//log.Printf("[wordunit: %s   count: %d]\n", wordUnit,listofUnique[j].Count)
						listofUnique[j].Count +=1
						catchflag = 1
					
						break
					}
				}
			
				if catchflag != 1{
					listofUnique = append(listofUnique, WordCount{wordUnit, 1})
					counter +=1
				}
			}
		
		}

		
	}
	sortWordCounts(listofUnique)
	if numWords > counter {
		return listofUnique
	}
/*
	log.Printf("-----------------------------------------------------------------\n")
	for j:=0; j<numWords; j++{
		log.Printf("%s, %d  ",listofUnique[j].Word, listofUnique[j].Count )
}
*/
	return listofUnique[:numWords]
}

// A struct that represents how many times a word is observed in a document
type WordCount struct {
	Word  string
	Count int
}

func (wc WordCount) String() string {
	return fmt.Sprintf("%v: %v", wc.Word, wc.Count)
}

// Helper function to sort a list of word counts in place.
// This sorts by the count in decreasing order, breaking ties using the word.
// DO NOT MODIFY THIS FUNCTION!
func sortWordCounts(wordCounts []WordCount) {
	sort.Slice(wordCounts, func(i, j int) bool {
		wc1 := wordCounts[i]
		wc2 := wordCounts[j]
		if wc1.Count == wc2.Count {
			return wc1.Word < wc2.Word
		}
		return wc1.Count > wc2.Count
	})
}
