/*
	practices: io/read write, bufio, flag, os, strings, 7 sort algorithms
*/
package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
	"time"

	"sort7"
)

var infile *string = flag.String("i", "infile", "File contains values for sorting")
var outfile *string = flag.String("o", "outfile", "File store values sorted")
var algorithm *string = flag.String("a", "Bubblesort", "Sort algorithm")

func main() {
	flag.Usage = func() {
		fmt.Println("[Usage]")
		fmt.Printf("\t%s -i infile -o outfile -a algorithm\n", os.Args[0])
		fmt.Println("\talgoritms:\n\t\tbubble\n\t\tquick\n\t\theap\n\t\tshell\n\t\tmerge\n\t\tselect\n\t\tinsert\n")
		fmt.Println()
		return
	}

	flag.Parse()
	if infile == nil {
		fmt.Println("Input file invalid.")
		return
	}

	// read values
	values, err := readValues(*infile)
	if err != nil {
		fmt.Println(err)
		return
	} else {
		t1 := time.Now()

		// call sort
		switch *algorithm {
		case "bubble":
			//sort7.BubbleSort(values)
			//sort7.BubbleSort1(values)
			sort7.BubbleSort2(values)
		case "quick":
			sort7.QuickSort(values)
		case "heap":
			sort7.MaxHeapSort(values) // min -> max
			//sort7.MinHeapSort(values) // reverse sort: max -> min
		case "shell":
			//sort7.ShellSort(values)
			//sort7.ShellSort1(values)
			sort7.ShellSort2(values)
		case "merge":
			sort7.MergeSort(values)
		case "select":
			sort7.SelectSort(values)
		case "insert":
			//sort7.InsertSort(values)
			//sort7.InsertSort1(values)
			sort7.InsertSort2(values)
		default:
			fmt.Println("Sorting algorithm", *algorithm, "is either unknow or unsupported.")
		}

		t2 := time.Now()
		fmt.Println("The sorting process costs", t2.Sub(t1), "to complete.")

		outfileName := strings.Replace(*outfile, "sorted", "sorted_"+*algorithm, -1)

		err := writeValues(values, outfileName)
		if err != nil {
			fmt.Println(err)
			return
		}
	}
}

func readValues(infile string) (values []int, err error) {
	file, err := os.Open(infile)
	if err != nil {
		fmt.Println("Failed to open input file", infile)
		return
	}
	defer file.Close()

	br := bufio.NewReader(file)
	values = make([]int, 0)

	for {
		line, isPrefix, err1 := br.ReadLine()
		if err1 != nil { //EOF
			if err1 != io.EOF {
				err = err1
			}
			break
		}

		if isPrefix {
			fmt.Println("A too long line, seems unexpected.")
			return
		}

		s := string(line)
		value, err1 := strconv.Atoi(s)
		if err1 != nil {
			err = err1
			return
		}

		values = append(values, value)

	}
	return
}

func writeValues(values []int, outfile string) error {
	file, err := os.Create(outfile)
	if err != nil {
		fmt.Println("Failed to open output file", outfile)
		return err
	}
	defer file.Close()

	tail := "\n"
	for n, value := range values {
		str := strconv.Itoa(value)
		if n == len(values)-1 {
			tail = ""
		}

		_, err := file.WriteString(str + tail)
		if err != nil {
			fmt.Println("Failed to write values into", outfile)
			return err
		}
	}

	return nil
}
