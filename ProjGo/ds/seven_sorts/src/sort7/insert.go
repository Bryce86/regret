package sort7

func InsertSort(array []int) {
	var i, j int

	for i = 1; i < len(array); i++ {
		for j = i - 1; j >= 0; j-- {
			if array[j] < array[i] {
				break
			}
		}

		if j != i-1 {
			temp, k := array[i], 0

			for k = i - 1; k > j; k-- {
				array[k+1] = array[k]
			}
			array[k+1] = temp
		}
	}
}

func InsertSort1(array []int) {
	var i, j int

	for i = 1; i < len(array); i++ {
		if array[i] < array[i-1] {
			temp := array[i]

			for j = i - 1; j >= 0 && array[j] > temp; j-- {
				array[j+1] = array[j]
			}
			array[j+1] = temp
		}
	}
}

func InsertSort2(array []int) {
	var i, j int

	for i = 1; i < len(array); i++ {
		for j = i - 1; j >= 0 && array[j] > array[j+1]; j-- {
			array[j+1], array[j] = array[j], array[j+1]
		}
	}
}
