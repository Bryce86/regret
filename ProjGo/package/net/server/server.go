package main

import (
	"flag"
	"fmt"
	"io"
	"net"
	"os"
)

func Server(ip, port string) {
	fmt.Printf("Welcome to meeting room: %s, %s\n\n", ip, port)

	lst, err := net.Listen("tcp", ":7788")
	if err != nil {
		fmt.Println("Listen failed: ", err)
		return
	}

	for {
		conn, err := lst.Accept()
		if err != nil {
			fmt.Println("Accept fail: ", err)
			return
		} else {
			fmt.Printf("\n~ Welcome %s\n\n", conn.RemoteAddr())

		}
		defer conn.Close()

		//goroutine
		go processMsg(conn)
	}
}

func processMsg(conn net.Conn) {
	buff := make([]byte, 1024)
	defer fmt.Printf("\n~ %v leave room.\n\n", conn.RemoteAddr())

	for {
		n, err := conn.Read(buff)
		if err != nil {
			if err == io.EOF {
				break
			} else {
				fmt.Printf("conn Read failed(%d): %v\n", n, err)
				return
			}
		}

		slice := buff[:n]
		fmt.Printf("[%s]: %v\n", conn.RemoteAddr(), string(slice))
	}
}

func main() {
	flag.Usage = func() {
		fmt.Printf("[Usage]\n\t\t%s ip port\n", os.Args[0])
	}
	flag.Parse()

	if flag.NArg() == 2 {
		Server(os.Args[1], os.Args[2])
	} else {
		flag.Usage()
	}
}
