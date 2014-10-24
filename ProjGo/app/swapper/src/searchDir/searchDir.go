package main

import (
	"fmt"
	"io/ioutil"
	"sort"
	"strconv"
	"strings"
	"time"
)

func main() {
	// get dir infos
	fi, err := ioutil.ReadDir("D:\\Workspace\\regret\\ProjGo\\ds\\list\\src")
	if err != nil {
		fmt.Println("read failed.")
		return
	}

	// get time
	t := strconv.Itoa(int(time.Now().Month())) + strconv.Itoa(time.Now().Day()) +
		strconv.Itoa(time.Now().Year()) + "_"
	//fmt.Println(t)

	//
	LogDirs := make(map[string]string)
	for i := 0; i < len(fi); i++ {
		if fi[i].IsDir() {
			if strings.Contains(fi[i].Name(), t) {
				key := strings.Index(fi[i].Name(), "_")
				LogDirs[fi[i].Name()[key+1:]] = fi[i].Name()
			}
		}
	}
	//fmt.Println(LogDirs)

	var keys []string
	for k := range LogDirs {
		keys = append(keys, k)
	}
	//fmt.Println(keys)
	sort.Strings(keys)

	fmt.Println(keys[len(keys)-1])
	fmt.Println(LogDirs[keys[len(keys)-1]])
}
