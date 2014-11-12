package Chapter6

import (
	"fmt"
)

// Q26. Channel
// rewrite Q1.

const (
	showNum = 10
)

func shower(c chan int, quit chan bool) {
	for {
		select {
		case i := <-c:
			fmt.Print(i, " ")
		case <-quit:
			break
		}
	}
}

func Q26() {
	c := make(chan int)
	q := make(chan bool)

	go shower(c, q)
	for i := 0; i < showNum; i++ {
		c <- i
	}

	q <- false
	fmt.Println()
}

// Q27. fibonacci using channel

var c chan int

const (
	num = 20
)

func fib(i int) int {

	if i == 0 || i == 1 {
		return i
	} else {
		// i >= 2
		return fib(i-1) + fib(i-2)
	}
}

func fibonacci(n int) <-chan int { // only read channel, only write like chan<- int
	out := make(chan int, num)

	go func(m int, o chan int) {
		for i := 1; i <= m; i++ {
			o <- fib(i)
		}
	}(n, out) // they are parameters.

	return out
}

func Q27() {
	c := fibonacci(num)

	for i := 1; i <= num; i++ {
		fmt.Print(<-c, " ")
	}
	fmt.Println()
}
