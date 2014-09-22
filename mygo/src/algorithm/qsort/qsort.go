package qsort

func quicksort(values []int, l, r int) {
	if l < r {
		temp := values[l]
		i, j := l, r

		for i < j {
			for i < j && values[j] > temp {
				j--
			}

			if i < j {
				values[i] = values[j]
				i++
			}

			for i < j && values[i] <= temp {
				i++
			}

			if i < j {
				values[j] = values[i]
				j--
			}
		}
		values[i] = temp

		quicksort(values, l, i-1)
		quicksort(values, i+1, r)
	}
}

func Quicksort(values []int) {
	quicksort(values, 0, len(values)-1)
}
