package sort7

import (
	"fmt"
	"testing"
)

func TestBubbleSort(t *testing.T) {
	array := []int{5, 4, 1, 3, 2}

	BubbleSort(array)
	if array[0] != 1 || array[1] != 2 || array[2] != 3 || array[3] != 4 || array[4] != 5 {
		t.Error("BubbleSort failed. Got", array, "Expected 1 2 3 4 5")
	} else {
		fmt.Println("Finish BubbleSort testing", array)
	}
}

func TestBubbleSort1(t *testing.T) {
	array := []int{5, 4, 1, 3, 2}

	BubbleSort1(array)
	if array[0] != 1 || array[1] != 2 || array[2] != 3 || array[3] != 4 || array[4] != 5 {
		t.Error("BubbleSort1 failed. Got", array, "Expected 1 2 3 4 5")
	} else {
		fmt.Println("Finish BubbleSort1 testing", array)
	}
}

func TestBubbleSort2(t *testing.T) {
	array := []int{5, 4, 1, 3, 2}

	BubbleSort2(array)
	if array[0] != 1 || array[1] != 2 || array[2] != 3 || array[3] != 4 || array[4] != 5 {
		t.Error("BubbleSort2 failed. Got", array, "Expected 1 2 3 4 5")
	} else {
		fmt.Println("Finish BubbleSort2 testing", array)
	}
}
