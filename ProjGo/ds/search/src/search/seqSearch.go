/*
	Sequence Search
*/

package search

/* unsorted search */
// time complexity: O(n)

func SeqSearch(array []int, x int) int {
	n := len(array)

	for i := 0; i < n; i++ {
		if array[i] == x {
			return i
		}
	}

	return -1
}
