package main

import (
	"fmt"
	"log"
	"net/rpc"
	"os"
)

type Args struct {
	A int
	B int
}

type Quotient struct {
	Quo int
	Rem int
}

func main() {
	if len(os.Args) != 2 {
		fmt.Println("Usage: ", os.Args[0], " server")
		os.Exit(1)
	}

	// string
	serverAddr := os.Args[1]

	//client, err := rpc.DialHTTP("tcp", serverAddr+":1234")
	client, err := rpc.Dial("tcp", serverAddr+":1234")
	if err != nil {
		log.Fatal("dailing: ", err)
	}

	args := Args{17, 8}
	var reply int
	err = client.Call("Arith.Multiply", args, &reply)
	if err != nil {
		log.Fatal("arith error:", err)
	}
	fmt.Printf("Arith: %d*%d=%d\n", args.A, args.B, reply)

	var quo Quotient
	err = client.Call("Arith.Divide", args, &quo)
	if err != nil {
		log.Fatal("arith error:", err)
	}

	fmt.Printf("Arith: %d/%d=%d remainder %d\n", args.A, args.B, quo.Quo, quo.Rem)
}
