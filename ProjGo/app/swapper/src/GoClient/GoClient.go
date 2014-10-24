package main

import (
	"flag"
	"fmt"
	"net"
	"os"
	//"time"
	"io"
)

func Client(ip, port, cmd string) {
	conn, err := net.Dial("tcp", ip+":"+port)
	if err != nil {
		fmt.Println("Dial failed: ", err)
		return
	} else {
		fmt.Printf("connect %s\n\n", ip+":"+port)
	}
	defer conn.Close()

	conn.Write([]byte(cmd))

	switch cmd {
	case "go":
		var reply [256]byte
		n, err1 := conn.Read(reply[:])
		if err1 != nil {
			fmt.Println("read failed, ", err1)
			return
		}
		fmt.Println(string(reply[:n]))

	case "cp":

		var data [2048]byte
		// read log dir
		n, err0 := conn.Read(data[:])
		if err0 != nil {
			fmt.Println("read logDir failed.")
			return
		}

		// mkdir logDir
		err0 = os.Mkdir(string(data[:n]), os.ModePerm)
		if err0 != nil {
			fmt.Println("mkdir logDir failed. ", err0)
			return
		}

		// create log file
		swLog, err := os.OpenFile(string(data[:n])+"\\"+"swUpgrade.log", os.O_CREATE|os.O_RDWR|os.O_TRUNC, 0777)
		if err != nil {
			fmt.Println("Client: Open swUpgrade.log failed.")
			return
		}
		defer swLog.Close()

		// write log info
		for {
			n, err1 := conn.Read(data[:])
			if err1 != nil {
				if err1 == io.EOF {
					break
				}

				fmt.Println("read failed, ", err1)
				return
			}
			//fmt.Println(string(data[:n]))
			m, err2 := swLog.Write(data[:n])
			if err2 != nil || m != n {
				fmt.Println("write failed, ", err2)
				return
			}
		}

	default:
		fmt.Println("Client: Invalid cmd")
	}

	return
}

func main() {
	flag.Usage = func() {
		fmt.Printf("[Usage] %s ip port cmd\n", os.Args[0])
	}
	flag.Parse()

	if flag.NArg() == 3 {
		Client(os.Args[1], os.Args[2], os.Args[3])
	} else {
		flag.Usage()
	}
}
