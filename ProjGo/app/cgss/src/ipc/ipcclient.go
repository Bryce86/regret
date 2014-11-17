package ipc

import (
	"encoding/json"
)

type IpcClient struct {
	conn chan string
}

func NewIpcClient(server *IpcServer) *IpcClient {
	c := server.Connect()
	return &IpcClient{c}
}

func (client *IpcClient) Call(method, params string) (*Response, error) {
	req := &Request{method, params}

	b, err := json.Marshal(req)
	if err != nil {
		return nil, err
	}

	client.conn <- string(b)
	str := <-client.conn

	var resp Response
	err = json.Unmarshal([]byte(str), &resp)

	return &resp, nil
}

func (client *IpcClient) Close() {
	client.conn <- "CLOSE"
}
