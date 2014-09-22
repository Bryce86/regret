package qsort

import (
	"testing"
)

func TestQuicksort1(t *testing.T) {
	values := []int{5, 4, 2, 3, 1}
	Quicksort(values)

	if values[0] != 1 || values[1] != 2 || values[2] != 3 || values[3] != 4 || values[4] != 5 {
		t.Error("Quicksort() failed. Got", values, "Expected 1 2 3 4 5")
	}
}
