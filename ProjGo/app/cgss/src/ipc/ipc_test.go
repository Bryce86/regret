package ipc

import (
	"testing"
)

type EchoServer struct {
}

func (server *EchoServer) Handle(method, params string) *Response {
	return &Response{Code: "200", Body: method + ":" + params}
}

func (server *EchoServer) Name() string {
	return "EchoServer"
}

func TestIpc(t *testing.T) {
	server := NewIpcServer(&EchoServer{})

	client1 := NewIpcClient(server)
	client2 := NewIpcClient(server)

	resp1 := client1.Call("ECHO:", "From Client1")
	resp2 := client2.Call("ECHO:", "From Client2")

	if resp1.Code != "200" || resp2.Code != "200" {
		t.Error("IpcClient.Call failed. resp1:", resp1.Body, "resp2:", resp2.Body)
	}

	client1.Close()
	client2.Close()
}
