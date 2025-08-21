package mapreduce

import (
	"encoding/json"
	"os"
)

func doReduce(
	jobName string,       // the name of the whole MapReduce job
	reduceTaskNumber int, // which reduce task this is
	nMap int,             // the number of map tasks that were run ("M" in the paper)
	reduceF func(key string, values []string) string,
) {
	// Map to hold all key/value pairs
	kvMap := make(map[string][]string)
	for m := 0; m < nMap; m++ {
		fileName := reduceName(jobName, m, reduceTaskNumber)
		file, err := os.Open(fileName)
		checkError(err)
		dec := json.NewDecoder(file)
		for {
			var kv KeyValue
			if err := dec.Decode(&kv); err != nil {
				break
			}
			kvMap[kv.Key] = append(kvMap[kv.Key], kv.Value)
		}
		checkError(file.Close())
	}

	outFileName := mergeName(jobName, reduceTaskNumber)
	outFile, err := os.Create(outFileName)
	checkError(err)
	enc := json.NewEncoder(outFile)
	for key, values := range kvMap {
		reduced := reduceF(key, values)
		err := enc.Encode(KeyValue{Key: key, Value: reduced})
		checkError(err)
	}

	checkError(outFile.Close())
}