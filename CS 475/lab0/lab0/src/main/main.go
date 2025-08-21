package main

import (
    "fmt"
    "lab0/q1"
)



func main() {

 var count []q1.WordCount
 count = q1.TopWords("../q1/declaration_of_independence.txt",5,6);

 for  i,_ := range count {
   fmt.Println(count[i])
  }

}
