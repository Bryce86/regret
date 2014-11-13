package Chapter7

import (
	"fmt"
	"os/exec"
	"sort"
	"strconv"
	"strings"
	"unicode/utf8"
)

// Q28. process
// this process is only used on windows os.
func process() {
	cmd := exec.Command("ps", "-W")
	r, err1 := cmd.Output()
	if err1 != nil {
		fmt.Println(err1)
		return
	}

	// notice: pkg strings 's functions: Split and Fields
	// map type: key is int, and value is []int
	child := make(map[int][]int)

	for i, buf := range strings.Split(string(r), "\n") {
		if i == 0 { // remove topic
			continue
		}
		if len(buf) == 0 { // remove the last space line
			continue
		}
		if buf[0] == 'I' { // remove a special process
			continue
		}

		fields := strings.Fields(buf)
		fpp, _ := strconv.Atoi(fields[1]) // ppid
		fp, _ := strconv.Atoi(fields[0])  // pid
		child[fpp] = append(child[fpp], fp)
	}

	// sort map's key
	schild := make([]int, len(child))
	count := 0
	for k, _ := range child {
		schild[count] = k
		count++
	}
	sort.Ints(schild)

	for _, ppid := range schild {
		fmt.Printf("Pid %d has %d ", ppid, len(child[ppid]))
		if len(child[ppid]) == 1 {
			fmt.Printf("child: %v\n", child[ppid])
		} else {
			fmt.Printf("children: %v\n", child[ppid])
		}
	}
}

func Q28() {
	process()
}

// Q29. words and letters counter

// -w words 10
// -c bytes, chars 51
// -l lines
func wc(opt string, w string) int {
	switch opt {
	case "-l":
		return len(strings.Split(w, "\n"))
	case "-w":
		words := 0
		for _, buf := range strings.Split(w, "\n") {
			words += len(strings.Fields(buf))
		}
		return words
	case "-c":
		return utf8.RuneCount([]byte(w))
	}

	return 0
}

func Q29() {
	var w string = `hi John,
This is a process
using to implement 'wc'.`

	fmt.Printf("-w: %d\n", wc("-w", w))
	fmt.Printf("-c: %d\n", wc("-c", w))
	fmt.Printf("-l: %d\n", wc("-l", w))
}

// Q30. uniq

func uniq(b []byte) {
repeat:
	for i, v := range b {
		for j := 0; j < i; j++ {
			if b[j] == v {
				continue repeat
			}
		}
		fmt.Printf("%c ", v)
	}
	fmt.Println()
}

func Q30() {
	b := []byte{'a', 'b', 'a', 'b', 'g', 'c', 'd', 'e', 'f', 'g'}
	uniq(b)
}

// Q31. Quine: print self
// I don't konw what's the mean.
func quine() {
	fmt.Printf("%s%c%s%c\n", q, 0x60, q, 0x60)
}

var q = ` // Q31. Quine: print self
func quine() {
	fmt.Printf("%s%c%s%c\n", q, 0x60, q, 0x60)
}
var q = `

func Q31() {
	quine()
}

// Q32. Echo Service
// A server and a client.
// Detail see my other project (https://github.com/Bryce86/regret.git
// regret/ProjGo/package/net)

// Q33. Math Game
// ToDO: It's hard.

// Q34. Finger Daemon
// I think it's a service, receiving command from client and execute it.
// Skipped.
