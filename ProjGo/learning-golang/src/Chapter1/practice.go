package Chapter1

import (
	"fmt"
	"unicode/utf8"
)

// Q1. (0) For-loop
func Q1() {
	// 1
	for i := 1; i <= 10; i++ {
		fmt.Print(i, " ")
	}
	fmt.Println()

	// 2
	var i int = 1

loop:
	if i <= 10 {
		fmt.Print(i, " ")
		i++
		goto loop
	}
	fmt.Println()

	// 3
	array := [...]int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	for _, i := range array {
		fmt.Print(i, " ")
	}
	fmt.Println()
}

// Q2. (0)FizzBuzz
func Q2() {
	for i := 1; i <= 100; i++ {
		if i%3 == 0 {
			if i%5 == 0 {
				fmt.Print("FizzBuzz", " ")
			} else {
				fmt.Print("Fizz", " ")
			}
		} else if i%5 == 0 {
			fmt.Print("Buzz", " ")
		} else {
			fmt.Print(i, " ")
		}
	}
}

// Q3. (1) string
func Q3() {
	// 1
	str := "A"
	for i := 1; i <= 10; i++ {
		fmt.Printf("%s\n", str)
		str = str + "A"
	}

	// 2
	var s string = "asSASA ddd dsjkdsjs dk"
	fmt.Println(len(s), " ", utf8.RuneCount([]byte(s)))

	// 3
	//s3 := strings.Replace(s, s[4:7], "abc", 3)
	s3 := []byte(s)
	copy(s3[4:4+3], []byte("abc"))
	fmt.Println(string(s3))

	// 4
	var s4 string = "foobar"
	reverse := func(s string) string {
		array := []byte(s)
		for i, j := 0, len(array)-1; i < j; i, j = i+1, j-1 {
			array[i], array[j] = array[j], array[i]
		}
		return string(array)
	}

	s5 := reverse(s4)
	fmt.Println(s5)
}

// Q4. (1) average
func Q4() {
	array := [...]float64{1.1, 2.2, 3.3, 4.4, 5.5}

	average := func(a []float64) float64 {
		if len(a) == 0 {
			return 0
		}

		sum := 0.0
		for _, v := range a {
			sum += v
		}

		return (sum / float64(len(a)))
	}

	ave := average(array[:])
	fmt.Printf("%v\n", ave)
}
