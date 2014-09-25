package sort7

/* Max Heap Sort */
func MaxHeapSort(array []int) {
	var n int = len(array)
	MakeMaxHeap(array)

	for i := n - 1; i >= 1; i-- {
		array[0], array[i] = array[i], array[0]
		MaxHeapFixdown(array, 0, i)
	}

}

func MakeMaxHeap(array []int) {
	var n int = len(array)

	for i := n/2 - 1; i >= 0; i-- {
		MaxHeapFixdown(array, i, n)
	}
}

func MaxHeapFixdown(array []int, i, n int) {
	j, temp := 2*i+1, array[i]

	for j < n {
		if j+1 < n && array[j] < array[j+1] {
			j++
		}

		if array[j] <= temp {
			break
		}

		array[i] = array[j]
		i = j
		j = 2*i + 1
	}
	array[i] = temp
}

/* *********************************************** */

/* Min Heap Sort */
func MinHeapSort(array []int) {
	var n int = len(array)
	MakeMinHeap(array)

	for i := n - 1; i >= 1; i-- {
		array[0], array[i] = array[i], array[0]
		MinHeapFixdown(array, 0, i)
	}
}

func MakeMinHeap(array []int) {
	var n int = len(array)

	for i := n/2 - 1; i >= 0; i-- {
		MinHeapFixdown(array, i, n)
	}
}

func MinHeapFixdown(array []int, i, n int) {
	var j, temp int = 2*i + 1, array[i]

	for j < n {
		for j+1 < n && array[j+1] < array[j] {
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

// for add element
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

// optimize
func MinHeapFixup_1(array []int, i int) {
	j := 0
	for j = (i - 1) / 2; (j >= 0 && i != 0) && array[i] < array[j]; i, j = j, (i-1)/2 {
		array[i], array[j] = array[j], array[i]
	}
}

func MinHeapDeleteNumber(array []int, n int) {
	array[0], array[n] = array[n], array[0]
	MinHeapFixdown(array, 0, n-1)
}
