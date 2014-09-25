package sort7

func MergeSort(array []int) {
	var n int = len(array)

	tempArray := make([]int, n)
	mergesort(array, 0, n-1, tempArray)
}

func mergearray(array []int, fst, mid, lst int, tempArray []int) {
	var i, m int = fst, mid
	var j, n int = mid + 1, lst
	var k int = 0

	for i <= m && j <= n {
		if array[i] < array[j] {
			tempArray[k] = array[i]
			k++
			i++
		} else {
			tempArray[k] = array[j]
			k++
			j++
		}
	}

	for i <= m {
		tempArray[k] = array[i]
		k++
		i++
	}

	for j <= n {
		tempArray[k] = array[j]
		k++
		j++
	}

	for i = 0; i < k; i++ {
		array[i+fst] = tempArray[i]
	}
}

func mergesort(array []int, fst, lst int, tempArray []int) {
	if fst < lst {
		mid := (fst + lst) / 2
		mergesort(array, 0, mid, tempArray)
		mergesort(array, mid+1, lst, tempArray)
		mergearray(array, fst, mid, lst, tempArray)
	}
}
