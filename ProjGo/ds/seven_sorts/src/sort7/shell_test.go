package sort7

import (
	"fmt"
	"testing"
)

func TestShellSort(t *testing.T) {
	array := []int{5, 3, 1, 4, 2}

	ShellSort(array)
	if array[0] != 1 || array[1] != 2 || array[2] != 3 || array[3] != 4 || array[4] != 5 {
		t.Error("ShellSort failed. Got", array, "Expected 1 2 3 4 5")
	} else {
		fmt.Println("Finish ShellSort testing", array)
	}
}

func TestShellSort1(t *testing.T) {
	array := []int{5, 3, 1, 4, 2}

	ShellSort1(array)
	if array[0] != 1 || array[1] != 2 || array[2] != 3 || array[3] != 4 || array[4] != 5 {
		t.Error("ShellSort1 failed. Got", array, "Expected 1 2 3 4 5")
	} else {
		fmt.Println("Finish ShellSort1 testing", array)
	}
}

func TestShellSort2(t *testing.T) {
	array := []int{5, 3, 1, 4, 2}

	ShellSort2(array)
	if array[0] != 1 || array[1] != 2 || array[2] != 3 || array[3] != 4 || array[4] != 5 {
		t.Error("ShellSort2 failed. Got", array, "Expected 1 2 3 4 5")
	} else {
		fmt.Println("Finish ShellSort2 testing", array)
	}
}
