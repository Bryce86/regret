package sort7

func QuickSort(array []int) {
	quicksort(array, 0, len(array)-1)
}

func quicksort(array []int, l, r int) {
	if l < r {
		i, j, temp := l, r, array[l]

		for i < j {
			for i < j && array[j] > temp {
				j--
			}

			if i < j {
				array[i] = array[j]
				i++
			}

			for i < j && array[i] <= temp {
				i++
			}

			if i < j {
				array[j] = array[i]
				j--
			}
		}
		array[i] = temp

		quicksort(array, l, i-1)
		quicksort(array, i+1, r)
	}
}
