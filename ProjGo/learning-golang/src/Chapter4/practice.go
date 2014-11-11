package Chapter4

import (
	"bufio"
	"container/list"
	"fmt"
	"io"
	"os"
	"strconv"
)

// Q17. pointer
// answer: integer, byte

// Q18. map using interface
func callback_func(x interface{}) {
	fmt.Print(x, " ")
}

func myMap(f func(x interface{}), arr []interface{}) {
	for _, v := range arr {
		f(v)
	}
	fmt.Println()
}

func Q18() {
	arr := []string{"hello", "the", "world"}

	args := make([]interface{}, len(arr))
	for i, _ := range arr {
		args[i] = arr[i]
	}

	myMap(callback_func, args)
}

// Q19. pointer

// Q120. double link

// Container/list
func ContainerDlink() {
	fmt.Println("Container list: ")

	l := list.New()
	l.PushBack(1)
	l.PushBack(2)
	l.PushBack(4)

	for e := l.Front(); e != nil; e = e.Next() {
		fmt.Print(e.Value, " ")
	}
	fmt.Println()
}

// my dblink
type DBLink struct {
	data  interface{}
	prev  *DBLink
	next  *DBLink
	front *DBLink
	back  *DBLink
}

func New() *DBLink {
	dbl := new(DBLink)
	return dbl
}

func (dbl *DBLink) Init() {
	dbl.data = int(-1)
	dbl.next = nil
	dbl.prev = nil
	dbl.front = nil
	dbl.back = nil
}

func (dbl *DBLink) PushBack(e interface{}) {
	if dbl.back == nil {
		dbl.back = dbl
	}

	tmp := new(DBLink)
	tmp.data = e
	tmp.next = nil
	tmp.prev = dbl.back
	dbl.back.next = tmp

	dbl.back = tmp

	if dbl.front == nil {
		dbl.front = tmp
	}
}

func (dbl *DBLink) Front() *DBLink {
	return dbl.front
}

func (dbl *DBLink) Back() *DBLink {
	return dbl.back
}

func (dbl *DBLink) Next() *DBLink {
	return dbl.next
}

func (dbl *DBLink) Value() interface{} {
	return dbl.data
}

func MyDLink() {
	fmt.Println("My link: ")

	l := New()
	l.Init()
	l.PushBack(1)
	l.PushBack(2)
	l.PushBack(4)
	//fmt.Println(l.Back().Value())

	for e := l.Front(); e != nil; e = e.Next() {
		fmt.Print(e.Value(), " ")
	}
	fmt.Println()
}

func Q20() {
	ContainerDlink()
	MyDLink()
}

// Q21. Cat

// because this .go file not main exec, so use file path argment
// replace os.args
func cat(opt string, f string) {
	fd, err := os.Open(f)
	if err != nil {
		fmt.Printf("open file %s failed. %v\n", f, err)
		return
	}
	defer fd.Close()

	bf := bufio.NewReader(fd)
	var line int = 1

	for {
		buff, err1 := bf.ReadString('\n')
		if err1 != nil {
			if err1 == io.EOF {
				// because the last line no '\n', maybe not be printed
				fmt.Println(buff)
				break
			}

			fmt.Println("bufio readstring failed. ", err1)
			return
		}

		var output string
		switch opt {
		case "-n":
			output = strconv.Itoa(line) + " " + buff
			line++
		default:
			output = buff
		}
		fmt.Print(output)
	}
}

func Q21() {
	cat("-n", "practice_test.go")
}
