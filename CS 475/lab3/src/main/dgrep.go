// +build dgrep
package main

import (
	"os"
	"fmt"
	"lab3/mapreduce"
	"regexp"
	"strings"
)
func mapF(filename string, pattern string, contents string) (res []mapreduce.KeyValue) {
    re, err := regexp.Compile(pattern)
    if err != nil {
        panic(err)
    }
    
    lines := strings.Split(contents, "\n")
    for i, line := range lines {
        if re.MatchString(line) {
            // Value is only the line number and text.
            value := fmt.Sprintf("%d:%s", i+1, line)
            res = append(res, mapreduce.KeyValue{Key: filename, Value: value})
        }
    }
    return res
}

func reduceF(key string, values []string) string {
    // Build a new slice of results:
    // - For the first line, do not prepend the key since the framework will print it.
    // - For subsequent lines, prepend the key.
    if len(values) == 0 {
        return ""
    }

    results := make([]string, len(values))
    results[0] = values[0] // first value remains as is
    for i := 1; i < len(values); i++ {
        results[i] = fmt.Sprintf("%s:%s", key, values[i])
    }
    return strings.Join(results, "\n")
}








// Can be run in 3 ways:
// 1) Sequential (e.g., go run dgrep.go master sequential pattern x1.txt .. xN.txt)
// 2) Master (e.g., go run dgrep.go master localhost:7777 pattern x1.txt .. xN.txt)
// 3) Worker (e.g., go run dgrep.go worker localhost:7777 localhost:7778 &)

func main() {
	if len(os.Args) < 4 {
		fmt.Printf("%s: see usage comments in file\n", os.Args[0])
	} else if len(os.Args) > 5 {
		if os.Args[1] == "master" {
			var mr *mapreduce.Master
			if os.Args[2] == "sequential" {
				mr = mapreduce.Sequential("dgrep", os.Args[3], os.Args[4:], 2, mapF, reduceF)
			} else {
				mr = mapreduce.Distributed("dgrep", os.Args[3], os.Args[4:], 2, os.Args[2])
			}
			mr.Wait()
		}
	} else if len(os.Args) == 4 && os.Args[1] == "worker" {
		mapreduce.RunWorker(os.Args[2], os.Args[3], mapF, reduceF, 100)
	} else {
		fmt.Printf("%s: see usage comments in file\n", os.Args[0])
	}
}
