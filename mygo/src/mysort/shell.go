package mysort

import (
	"stool"
)

func init() {
	stool.Sfuns.RegisterCall("Shell_sort_1", Shell_sort_1)
	stool.Sfuns.RegisterCall("Shell_sort_2", Shell_sort_2)
	stool.Sfuns.RegisterCall("Shell_sort_3", Shell_sort_3)
}

func Shell_sort_1(array []int) {
	var i, j, gap int
	n := len(array)

	for gap = n / 2; gap > 0; gap /= 2 {
		for i = 0; i < gap; i++ {
			for j = i + gap; j < n; j += gap {
				if array[j] < array[j-gap] {
					temp := array[j]
					k := j - gap
					for k >= 0 && array[k] > temp {
						array[k+gap] = array[k]
						k -= gap
					}
					array[k+gap] = temp
				}
			}
		}
	}
}

func Shell_sort_2(array []int) {
	var j, gap int
	n := len(array)

	for gap = n / 2; gap > 0; gap /= 2 {
		for j = gap; j < n; j++ {
			if array[j] < array[j-gap] {
				temp := array[j]
				k := j - gap

				for k >= 0 && array[k] > temp {
					array[k+gap] = array[k]
					k -= gap
				}
				array[k+gap] = temp
			}
		}
	}
}

func Shell_sort_3(array []int) {
	var i, j, gap int
	n := len(array)

	for gap = n / 2; gap > 0; gap /= 2 {
		for i = gap; i < n; i++ {
			for j = i - gap; j >= 0 && array[j] > array[j+gap]; j -= gap {
				stool.Swap(&array[j], &array[j+gap])
			}
		}
	}
}
