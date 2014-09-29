package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"net"
	"os"
)

func Client(ip, port string) {
	conn, err := net.Dial("tcp", ip+":"+port)
	if err != nil {
		fmt.Println("Dial failed: ", err)
		return
	} else {
		fmt.Printf("~ Enter room %s.\n\n", ip+":"+port)
	}
	defer conn.Close()

	rb := bufio.NewReader(os.Stdin)

	for {
		buff, isPrefix, err := rb.ReadLine()
		if err != nil {
			fmt.Println("...................")
			if err == io.EOF {
				break
			}

			fmt.Println("ReadString failed, ", err)
			return
		}

		if isPrefix {
			fmt.Println("error, too long text was over limited.")
			return
		}

		n, err := conn.Write(buff)
		if err != nil {
			fmt.Printf("conn Write failed(%d): %v\n", n, err)
			return
		}

		switch string(buff) {
		case "88", "bye", "quit", "exit", "byebye", "拜拜", "goodbye":
			fmt.Println("\n~ Quit meeting room.")
			return
		}
	}
}

func main() {
	flag.Usage = func() {
		fmt.Printf("[Usage] %s ip port\n", os.Args[0])
	}
	flag.Parse()

	if flag.NArg() == 2 {
		Client(os.Args[1], os.Args[2])
	} else {
		flag.Usage()
	}
}
