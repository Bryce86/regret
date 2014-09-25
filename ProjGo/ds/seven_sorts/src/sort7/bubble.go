/*
	Bubble sort
*/

package sort7

func BubbleSort(array []int) {
	for i := 0; i < len(array); i++ {
		for j := 1; j < len(array)-i; j++ {
			if array[j] < array[j-1] {
				array[j], array[j-1] = array[j-1], array[j]
			}
		}
	}
}

func BubbleSort1(array []int) {
	var flag bool = true
	var n int = len(array)

	for flag {
		flag = false
		for j := 1; j < n; j++ {
			if array[j] < array[j-1] {
				array[j], array[j-1] = array[j-1], array[j]
				flag = true
			}
		}
		n--
	}
}

func BubbleSort2(array []int) {
	var flag int = len(array)
	var k int

	for flag > 0 {
		k = flag
		flag = 0
		for j := 1; j < k; j++ {
			if array[j] < array[j-1] {
				array[j], array[j-1] = array[j-1], array[j]
				flag = j
			}
		}
	}
}
