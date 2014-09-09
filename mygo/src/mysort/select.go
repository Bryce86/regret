package mysort

import (
	"stool"
)

func init() {
	stool.Sfuns.RegisterCall("Select_sort", Select_sort)
}

func Select_sort(array []int) {
	var i, j, nMinIndex int
	n := len(array)

	for i = 0; i < n; i++ {
		nMinIndex = i
		for j = i + 1; j < n; j++ {
			if array[j] < array[nMinIndex] {
				nMinIndex = j
			}
		}

		stool.Swap1(&array[i], &array[nMinIndex])
	}
}
