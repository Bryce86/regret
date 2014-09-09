package mysort

import (
	"stool"
)

func init() {
	stool.Sfuns.RegisterCall("Insertion_sort_1", Insertion_sort_1)
	stool.Sfuns.RegisterCall("Insertion_sort_2", Insertion_sort_2)
	stool.Sfuns.RegisterCall("Insertion_sort_3", Insertion_sort_3)
}

func Insertion_sort_1(array []int) {
	n := len(array)

	i, j, k := 0, 0, 0

	for i = 1; i < n; i++ {
		for j = i - 1; j >= 0; j-- {
			if array[j] < array[i] {
				break
			}
		}

		if j != i-1 {
			temp := array[i]

			for k = i - 1; k > j; k-- {
				array[k+1] = array[k]
			}
			array[k+1] = temp
		}
	}
}

func Insertion_sort_2(array []int) {
	j := 0

	for i := 1; i < len(array); i++ {
		if array[i] < array[i-1] {
			temp := array[i]

			for j = i - 1; j >= 0 && array[j] > temp; j-- {
				array[j+1] = array[j]
			}
			array[j+1] = temp
		}
	}
}

func Insertion_sort_3(array []int) {
	j := 0

	for i := 1; i < len(array); i++ {
		for j = i - 1; j >= 0 && array[j] > array[j+1]; j-- {
			stool.Swap(&array[j], &array[j+1])
		}
	}
}
