package Chapter2

import (
	"errors"
	"fmt"
	"strconv"
)

// Q5. -> Q4

// Q6. (0) sort int
func Q6() {
	funs := func(a, b int) {
		a, b = b, a
		fmt.Println(a, " ", b)
	}

	var a, b int = 1, 2
	fmt.Println(a, " ", b)
	funs(a, b)
}

// Q7. (1) area
// i's area is only in for-loop.

// Q8. stack

const (
	MAX_SIZE = 10
)

type Stack struct {
	v   [MAX_SIZE]int
	top int
}

func (s *Stack) Push(e int) {
	if s.top >= MAX_SIZE {
		fmt.Println("out of range.")
		return
	}

	if s.top == -1 {
		s.top = 0
	}

	s.v[s.top] = e
	s.top++
}

func (s *Stack) Pop() (int, error) {
	if s.top < 0 {
		return -1, errors.New("empty stack.")
	}

	s.top--
	return s.v[s.top], nil
}

func (s Stack) String() string {
	if s.top < 0 {
		return ""
	}

	var str string
	for i := 0; i < s.top; i++ {
		str = str + "[" +
			strconv.Itoa(i) + ":" + strconv.Itoa(s.v[i]) + "]"
	}
	return str
}

func Q8() {
	var s Stack
	s.Push(1)
	s.Push(2)
	s.Push(3)
	s.Push(4)
	fmt.Printf("My stack %v\n", s)
	s.Pop()
	s.Pop()
	fmt.Printf("My stack %v\n", s)
}

// Q9. (1) mutilple args
func Q9() {
	fun := func(args ...int) {
		for _, v := range args {
			fmt.Println(v)
		}
	}

	fun(1, 2, 3, 4, 5)
}

// Q10. (1) fibonacci
func fibonacci(i int) int {
	if i == 0 {
		return 0
	}

	if i == 1 || i == 2 {
		return 1
	}

	return fibonacci(i-1) + fibonacci(i-2)
}

func Q10() {
	fmt.Print("fibonacci in 20: ")

	for i := 1; i <= 20; i++ {
		fmt.Print(fibonacci(i), " ")
	}
	fmt.Println()
}

// Q11. (1) map
func Map(f func(interface{}), arr []byte) {
	for _, v := range arr {
		f(v)
	}
	fmt.Println()
}

func Q11() {
	f := func(i interface{}) {
		fmt.Printf("%c", i)
	}

	ch := "abcdefg"
	Map(f, []byte(ch))
}

// Q12. (0) Max & Mix
func Q12() {
	max := func(arr []int) int {
		max_value := arr[0]
		for _, v := range arr {
			if max_value < v {
				max_value = v
			}
		}

		return max_value
	}

	arr := []int{1, 3, 7, 5, 4}
	fmt.Println("max:", max(arr[:]))

	mix := func(arr []int) int {
		mix_value := arr[0]
		for _, v := range arr {
			if mix_value > v {
				mix_value = v
			}
		}

		return mix_value
	}

	fmt.Println("mix:", mix(arr[:]))
}

// Q13. (1) Bubble Sort
func Q13() {
	bubblesort := func(arr []int) {
		n := len(arr)

		for i := 0; i < n; i++ {
			for j := 1; j < n-i; j++ {
				if arr[j] < arr[j-1] {
					arr[j], arr[j-1] = arr[j-1], arr[j]
				}
			}
		}
	}

	arr := []int{3, 2, 1, 5, 6, 0, 9}
	fmt.Println("origin:", arr)

	bubblesort(arr[:])
	fmt.Println("sorted:", arr)
}

// Q14. return function
func plusX(x int) func(i int) int {
	return func(i int) int {
		return i + x
	}
}

func Q14() {
	f := plusX(10)
	fmt.Println("plusX 5:", f(5))
}
