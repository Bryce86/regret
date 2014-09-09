package mysort

import (
	"stool"
)

func init() {
	stool.Sfuns.RegisterCall("Merge_sort", Merge_sort)
}

func Merge_sort(array []int) {
	pTempArray := make([]int, len(array))
	if pTempArray == nil {
		return
	}

	mergesort(array, 0, len(array)-1, pTempArray)
}

func mergesort(array []int, first, last int, temp []int) {
	if first < last {
		mid := (first + last) / 2

		mergesort(array, first, mid, temp)
		mergesort(array, mid+1, last, temp)
		mergearray(array, first, mid, last, temp)
	}
}

func mergearray(array []int, first, mid, last int, temp []int) {
	i, j, m, n := first, mid+1, mid, last
	k := 0

	for i <= m && j <= n {
		if array[i] < array[j] {
			temp[k] = array[i]
			k++
			i++
		} else {
			temp[k] = array[j]
			k++
			j++
		}
	}

	for i <= m {
		temp[k] = array[i]
		k++
		i++
	}

	for j <= n {
		temp[k] = array[j]
		k++
		j++
	}

	for i = 0; i < k; i++ {
		array[first+i] = temp[i]
	}
}
