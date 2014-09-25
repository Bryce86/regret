package sort7

func ShellSort(array []int) {
	var i, j, gap int
	var n int = len(array)

	for gap = n / 2; gap > 0; gap /= 2 {
		for i = 0; i < gap; i++ {
			for j = i + gap; j < n; j += gap {
				if array[j] < array[j-gap] {
					temp, k := array[j], j-gap

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

func ShellSort1(array []int) {
	var j, gap int
	var n int = len(array)

	for gap = n / 2; gap > 0; gap /= 2 {
		for j = gap; j < n; j++ {
			if array[j] < array[j-gap] {
				temp, k := array[j], j-gap

				for k >= 0 && array[k] > temp {
					array[k+gap] = array[k]
					k -= gap
				}
				array[k+gap] = temp
			}
		}
	}
}

func ShellSort2(array []int) {
	var i, j, gap int
	var n int = len(array)

	for gap = n / 2; gap > 0; gap /= 2 {
		for i = gap; i < n; i++ {
			for j = i - gap; j >= 0 && array[j] > array[j+gap]; j -= gap {
				array[j], array[j+gap] = array[j+gap], array[j]
			}
		}
	}
}
