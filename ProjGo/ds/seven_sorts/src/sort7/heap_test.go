package sort7

import (
	"fmt"
	"testing"
)

func TestHeapSort(t *testing.T) {
	array := []int{5, 3, 1, 4, 2}

	MaxHeapSort(array)
	if array[0] != 1 || array[1] != 2 || array[2] != 3 || array[3] != 4 || array[4] != 5 {
		t.Error("MaxHeapSort failed. Got", array, "Expected 1 2 3 4 5")
	} else {
		fmt.Println("Finish MaxHeapSort testing", array)
	}

	array1 := []int{5, 3, 1, 4, 2}

	MinHeapSort(array1)
	if array1[0] != 5 || array1[1] != 4 || array1[2] != 3 || array1[3] != 2 || array1[4] != 1 {
		t.Error("MinHeapSort failed. Got", array1, "Expected 5 4 3 2 1")
	} else {
		fmt.Println("Finish MinHeapSort testing", array1)
	}
}
