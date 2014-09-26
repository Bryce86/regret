package search

func BinarySearch(array []int, x int) int {
	i, n := 0, len(array)

	for i <= n {
		mid := (i + n) / 2
		if array[mid] == x {
			return mid
		} else if array[mid] < x {
			i = mid + 1
		} else if array[mid] > x {
			n = mid - 1
		}
	}

	return -1
}
