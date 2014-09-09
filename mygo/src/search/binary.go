package search

func Binary_Search(array []int, ele int) int {

	low := 0
	high := len(array) - 1
	var mid int

	for low <= high {
		mid = (high + low) / 2

		if ele < array[mid] {
			high = mid
		} else if ele > array[mid] {
			low = mid
		} else {
			return mid
		}
	}

	return -1
}

/*
func main() {
	array := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 0}

	fmt.Printf("element %d @ %d in array\n", 6, Binary_Search(array, 6))
}
*/
