package mysort

import (
	"stool"
)

func init() {
	stool.Sfuns.RegisterCall("MaxHeap_sort", MaxHeap_sort)
	stool.Sfuns.RegisterCall("MinHeap_sort", MinHeap_sort)
}

func MinHeapFixup(array []int, i int) {
	j, temp := (i-1)/2, array[i]

	for j >= 0 && i != 0 {
		if array[j] <= temp {
			break
		}

		array[i] = array[j]
		i = j
		j = (i - 1) / 2
	}
	array[i] = temp
}

/* 优化 */
func MinHeapFixup_1(array []int, i int) {
	j := 0
	for j = (i - 1) / 2; (j >= 0 && i != 0) && array[i] < array[j]; i, j = j, (i-1)/2 {
		stool.Swap(&array[i], &array[j])
	}
}

func MinHeapFixdown(array []int, i, n int) {
	j, temp := 2*i+1, array[i]

	for j < n {
		if j+1 < n && array[j+1] < array[j] { // 在左右孩子中找最小
			j++
		}

		if array[j] >= temp {
			break
		}

		array[i] = array[j]
		i = j
		j = 2*i + 1
	}
	array[i] = temp
}

/* 在最小堆中删除数 */
func MinHeapDeleteNumber(array []int, n int) {
	stool.Swap(&array[0], &array[n])
	MinHeapFixdown(array, 0, n-1)
}

func MakeMinHeap(array []int, n int) {
	for i := n/2 - 1; i >= 0; i-- {
		MinHeapFixdown(array, i, n)
	}
}

/* 最小堆排序 */
func MinHeap_sort(array []int) {
	n := len(array)
	MakeMinHeap(array, n)

	for i := n - 1; i >= 1; i-- {
		stool.Swap(&array[i], &array[0])
		MinHeapFixdown(array, 0, i)
	}
}

func MaxHeapFixdown(array []int, i, n int) {
	j, temp := i*2+1, array[i]

	for j < n {
		if j+1 < n && array[j] < array[j+1] {
			j++
		}

		if array[j] <= temp {
			break
		}

		array[i] = array[j]
		i = j
		j = i*2 + 1
	}
	array[i] = temp
}

func MakeMaxHeap(array []int, n int) {
	for i := n/2 - 1; i >= 0; i-- {
		MaxHeapFixdown(array, i, n)
	}
}

/* 最大堆排序 */
func MaxHeap_sort(array []int) {
	n := len(array)
	MakeMaxHeap(array, n)

	for i := n - 1; i >= 1; i-- { // array[0 ... n-1]
		stool.Swap(&array[i], &array[0])
		MaxHeapFixdown(array, 0, i)
	}
}
