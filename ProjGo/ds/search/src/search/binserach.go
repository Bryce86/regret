package search

/*
	this method need array must be sorted.
*/

// time complexity: O(logn)

func BinarySearch(array []int, x int) int {
	i, n := 0, len(array)-1

	for i <= n {
		//mid := (i + n) / 2
		mid := i + (n-i)*(x-array[i])/(array[n]-array[i])
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
