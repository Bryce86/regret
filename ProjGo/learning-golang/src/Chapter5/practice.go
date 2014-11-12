package Chapter5

import (
	"fmt"
)

// Q23. interface and compile

type I struct {
	i int
}

func (i *I) put(x int) {
	i.i = x
}

func (i I) get() int {
	return i.i
}

func g(any interface{}) int {
	if t, ok := any.(I); ok {
		return t.get()
	}
	return -1
}

func Q23() {
	var i I
	i.put(101)
	fmt.Println(g(i))
}

// Q24. the question refer to 'Call-by-value' and 'Call-by-reference'

// Q25. interface{} and max

func Less(a, b interface{}) bool {
	switch a.(type) {
	case int:
		if _, ok := b.(int); ok {
			return b.(int) < b.(int)
		}
	case float32:
		if _, ok := b.(float32); ok {
			return a.(float32) < b.(float32)
		}
	default:
		return false
	}
}

func Q25() {
	var a, b, c int = 1, 2, 0
	if c = a; Less(a, b) {
		c = b
	}

	var x, y, z float32 = 2.0, 1.0, 0.0
	if z = x; Less(x, y) {
		z = y
	}

	fmt.Printf("c=%v, z=%f\n", c, z)
}
