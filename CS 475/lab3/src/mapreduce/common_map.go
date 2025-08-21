package mapreduce

import (
	"hash/fnv"
        "encoding/json"
        "os"
)

func doMap(
	jobName string,
	mapTaskNumber int,
	input_argument string,
	inFile string,
	nReduce int,
	mapF func(file string, arg string, contents string) []KeyValue,
) {
	contentBytes, err := os.ReadFile(inFile)
	checkError(err)
	contents := string(contentBytes)
	kvs := mapF(inFile, input_argument, contents)
	tempData := make([][]KeyValue, nReduce)
	for _, kv := range kvs {
		r := int(ihash(kv.Key)) % nReduce
		tempData[r] = append(tempData[r], kv)
	}

	// Write each reduce task's data to its own intermediate file
	for r := 0; r < nReduce; r++ {
		fileName := reduceName(jobName, mapTaskNumber, r)
		file, err := os.Create(fileName)
		checkError(err)
		enc := json.NewEncoder(file)
		for _, kv := range tempData[r] {
			err := enc.Encode(&kv)
			checkError(err)
		}
		err = file.Close()
		checkError(err)
	}
}

func ihash(s string) uint32 {
	h := fnv.New32a()
	h.Write([]byte(s))
	return h.Sum32()
}
