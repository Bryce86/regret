package main

import (
	"bytes"
	"fmt"
)

func main() {
	//Compare
	s1, s2 := "hello", "world"
	fmt.Printf("s1 Compare s2 is %d\n", bytes.Compare([]byte(s1), []byte(s2)))

	//Count
	fmt.Printf("%s has %d 'l'\n", s1, bytes.Count([]byte(s1), []byte("l")))

	//Contains
	fmt.Printf("%s contains 'ab' is %v\n", s2, bytes.Contains([]byte(s2), []byte("ab")))

	//Index
	fmt.Printf("ll is %d at Hello\n", bytes.Index([]byte(s1), []byte("ll")))

	//LastIndex
	fmt.Printf("last l is %d at Hello\n", bytes.LastIndex([]byte(s1), []byte("l")))

	//IndexRune
	fmt.Printf("“五” 在 “第二十六招：炮五进四”中第%d个位子\n", bytes.IndexRune([]byte("“第二十六招：炮五进四”"), rune('五')))

	//IndexAny
	fmt.Printf("ae is %d at helloworld\n", bytes.IndexAny([]byte("helloworld"), "ae"))

	//LastIndexAny

	//SplitN
	fmt.Printf("splitN helloworld by o: %s\n", bytes.SplitN([]byte("helloworld"), []byte("o"), -1))

	//SplitAfterN
	fmt.Printf("splitAflterN helloworld by o: %s\n", bytes.SplitAfterN([]byte("helloworld"), []byte("o"), -1))

	//Split
	//SplitAfter

	//Fields
	fmt.Printf("helloworld fields: %s\n", bytes.Fields([]byte("he ll\ro\nwo\tr' 'l\fd")))

	//TBC
}
