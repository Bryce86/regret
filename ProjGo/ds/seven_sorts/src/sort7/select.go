package sort7

func SelectSort(array []int) {
	var nMinIdx int

	for i := 0; i < len(array); i++ {
		nMinIdx = i
		for j := i + 1; j < len(array); j++ {
			if array[j] < array[nMinIdx] {
				nMinIdx = j
			}
		}

		array[i], array[nMinIdx] = array[nMinIdx], array[i]
	}
}
