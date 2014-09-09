package mysort

import (
	"stool"
)

func init() {
	stool.Sfuns.RegisterCall("Quick_sort", Quick_sort)
}

func Quick_sort_in(array []int, l, r int) {
	if l < r {

		//Swap(&array[l], &array[(l+r)/2]) //如果以中间值作为基准数，
		//与第一位交换即可
		i, j := l, r
		x := array[i]

		for i < j && array[j] >= x {
			j--
		}

		if i < j {
			array[i] = array[j]
			i++
		}

		for i < j && array[i] < x {
			i++
		}

		if i < j {
			array[j] = array[i]
			j--
		}
		array[i] = x // i == j

		Quick_sort_in(array, 0, i-1)
		Quick_sort_in(array, i+1, r)
	}
}

func Quick_sort(array []int) {
	Quick_sort_in(array, 0, len(array)-1)
}
