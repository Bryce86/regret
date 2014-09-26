package search

import (
	"fmt"
	"testing"
)

func TestBinarySeach(t *testing.T) {
	array := []int{1, 3, 5, 7, 8, 10, 12}

	r := BinarySearch(array, 10)
	if r != 5 {
		t.Error("TestBinarySearch() failed. Got", r, ", expected 5")
	} else {
		fmt.Printf("Finish TestBinarySearch testing, Got %d.\n", r)
	}
}
