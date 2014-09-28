package search

import (
	"fmt"
	"testing"
)

func TestSeqSearch(t *testing.T) {
	array := []int{1, 3, 5, 7, 8, 10, 12}
	r := SeqSearch(array, 10)
	if r != 5 {
		t.Error("TestSeqSearch() failed. Got", r, ", expected 5")
	} else {
		fmt.Printf("Finish TestSeqSearch testing, Got %d.\n", r)
	}
}
