package mysort

import (
	"stool"
)

func init() {
	stool.Sfuns.RegisterCall("Bubble_sort_1", Bubble_sort_1)
	stool.Sfuns.RegisterCall("Bubble_sort_2", Bubble_sort_2)
	stool.Sfuns.RegisterCall("Bubble_sort_3", Bubble_sort_3)
}

func Bubble_sort_1(array []int) {

	l := len(array)

	for i := 0; i < l; i++ {
		for j := 1; j < l-i; j++ {
			if array[j-1] > array[j] {
				stool.Swap(&array[j-1], &array[j])
			}
		}
	}
}

func Bubble_sort_2(array []int) {
	k := len(array)
	flag := true

	for flag {
		flag = false

		for j := 1; j < k; j++ {
			if array[j-1] > array[j] {
				stool.Swap(&array[j-1], &array[j])
			}
			flag = true
		}
		k--
	}
}

func Bubble_sort_3(array []int) {
	k, n := 0, len(array)
	flag := n

	for flag > 0 {
		k = flag
		flag = 0

		for j := 1; j < k; j++ {
			if array[j-1] > array[j] {
				stool.Swap(&array[j-1], &array[j])
				flag = j
			}
		}
	}
}
