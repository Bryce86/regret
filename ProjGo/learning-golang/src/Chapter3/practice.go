package Chapter3

import (
	"fmt"
)

// Q15. make a package for stack

// define a stack of 'byte' used for Q16
const (
	MAX_STACK_SIZE = 20
)

type stack struct {
	v   [MAX_STACK_SIZE]byte
	top int
}

func (s *stack) init() {
	s.top = -1
}

func (s *stack) push(c byte) {
	if s.top >= MAX_STACK_SIZE {
		fmt.Println("out of range.")
		return
	}

	s.top++
	s.v[s.top] = c
}

func (s *stack) pop() byte {
	if s.top < 0 {
		fmt.Println("stack empty.")
		return '#'
	}

	e := s.v[s.top]
	s.top--
	return e
}

func reverseTraverse(s *stack) {
	if s.top < 0 {
		return
	}
	e := s.v[s.top]
	s.top--

	reverseTraverse(s)
	fmt.Printf("%c", e)
}

// Log on/off
var flag bool = false

func logEx(flag bool, format string, args ...interface{}) {
	if flag {
		fmt.Printf(format, args)
	}
}

// s1 used to store operator
var s1 stack

// s2 used to store expression
var s2 stack

func RPExpression(ex []byte) {
	if len(ex) == 0 {
		return
	}

	s1.init()
	s2.init()

	for _, v := range ex {
		switch {
		case v >= '0' && v <= '9':
			logEx(flag, "s2 push %c\n", v)
			s2.push(v)

			if s1.top != -1 {
				e := s1.pop()
				logEx(flag, "s1 pop %c\n", e)
				if e != '(' && e != ')' {
					s2.push(e)
				}
			} else {
				logEx(flag, "s1 no element.")
			}
		case v == '(':
			fallthrough
		case v == ')':
			fallthrough
		case v == '+':
			fallthrough
		case v == '-':
			fallthrough
		case v == '*':
			fallthrough
		case v == '/':
			logEx(flag, "s1 push %c\n", v)
			s1.push(v)
		default:
			logEx(flag, "skipping.")
		}
	}
	// get remain operator from s1
	for s1.top != -1 {
		e := s1.pop()
		logEx(flag, "s1 pop %c\n", e)
		if e != '(' && e != ')' {
			s2.push(e)
		}
	}

	reverseTraverse(&s2)
	fmt.Println()
}

// Q16. Reverse Polish notation, calculator.
// only using for digit.
func Q16() {

	// example: (a+b)*c-(a+b)/d
	// RP: ab+c*ab+d/-

	var str string = "(1+2)*3-(1+2)/4" // 12+3*12+4/-
	RPExpression([]byte(str))

	var str1 string = "((1-2)+3)*5/6-(2+4)" // 12-3+5*6/24+-
	RPExpression([]byte(str1))
}
