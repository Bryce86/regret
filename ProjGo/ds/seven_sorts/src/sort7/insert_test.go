package sort7

import (
	"fmt"
	"testing"
)

func TestInsertSort(t *testing.T) {
	array := []int{5, 3, 1, 4, 2}

	InsertSort(array)
	if array[0] != 1 || array[1] != 2 || array[2] != 3 || array[3] != 4 || array[4] != 5 {
		t.Error("InsertSort failed. Got", array, "Expected 1 2 3 4 5")
	} else {
		fmt.Println("Finish InsertSort testing", array)
	}
}

func TestInsertSort1(t *testing.T) {
	array := []int{5, 3, 1, 4, 2}

	InsertSort1(array)
	if array[0] != 1 || array[1] != 2 || array[2] != 3 || array[3] != 4 || array[4] != 5 {
		t.Error("InsertSort1 failed. Got", array, "Expected 1 2 3 4 5")
	} else {
		fmt.Println("Finish InsertSort1 testing", array)
	}
}

func TestInsertSort2(t *testing.T) {
	array := []int{5, 3, 1, 4, 2}

	InsertSort2(array)
	if array[0] != 1 || array[1] != 2 || array[2] != 3 || array[3] != 4 || array[4] != 5 {
		t.Error("InsertSort2 failed. Got", array, "Expected 1 2 3 4 5")
	} else {
		fmt.Println("Finish InsertSort2 testing", array)
	}
}
