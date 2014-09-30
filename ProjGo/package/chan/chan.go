package main

import (
	"fmt"
	"runtime"
	"sync"
	"time"
)

var x int

func process(c chan int, mutex *sync.Mutex) {
	mutex.Lock()
	defer mutex.Unlock()
	c <- x
	x++
	runtime.Gosched()
}

func main() {
	//runtime.NumCPU()
	runtime.GOMAXPROCS(4)
	mutex := &sync.Mutex{}
	c := make(chan int)

	for i := 0; i < 8; i++ {
		go process(c, mutex)
	}

	for {
		select {
		case x := <-c:
			fmt.Println(x)
		case <-time.After(time.Second * 1):
			fmt.Println("timeout")
			return
		}
	}
}
