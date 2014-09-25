package sort7

import (
	"fmt"
	"testing"
)

func TestQuickSort(t *testing.T) {
	array := []int{5, 3, 1, 4, 2}

	QuickSort(array)
	if array[0] != 1 || array[1] != 2 || array[2] != 3 || array[3] != 4 || array[4] != 5 {
		t.Error("QuickSort failed. Got", array, "Expected 1 2 3 4 5")
	} else {
		fmt.Println("Finish QuickSort testing", array)
	}
}
