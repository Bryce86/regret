package stool

import (
	"fmt"
	"math/rand"
)

type funcSort func([]int)
type SFunctions map[string]funcSort

var Sfuns SFunctions
var FuncNames []string
var idx int

func init() {
	Sfuns = make(SFunctions)
	FuncNames = make([]string, 100)
}

func (s SFunctions) RegisterCall(name string, fun funcSort) {
	s[name] = fun

	FuncNames[idx] = name
	idx++
}

func Swap(a, b *int) {
	temp := *a
	*a = *b
	*b = temp
}

func Swap1(a, b *int) {
	if *a != *b {
		*a ^= *b
		*b ^= *a
		*a ^= *b
	}
}

func SevenSortAlgorithms() {
	for _, name := range FuncNames {
		for s, fun := range Sfuns {

			var array []int

			if s == name {
				if true {
					array = []int{-2, 1000, 52, -88, 10, 421, 161, 161, 53, 0}

				} else {
					array = make([]int, 10)
					for i := 0; i < len(array); i++ {
						array[i] = rand.Int() % 100
					}
				}

				fun(array)
				fmt.Printf("%-16s: %d\n", s, array)
			}
		}
	}
}
