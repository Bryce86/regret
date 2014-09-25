package bt

import (
	"fmt"
	"testing"
)

const midLen = 10

var preMidArray [midLen]byte
var preMidIdx int = 0
var pstMidArray [midLen]byte
var pstMidIdx int = 0

func PreOrderTraversePMCB(T *BiTNode) {
	if T != nil {
		preMidArray[preMidIdx] = T.data
		preMidIdx++
		PreOrderTraversePMCB(T.lchild)
		PreOrderTraversePMCB(T.rchild)
	}
}

func PstOrderTraversePMCB(T *BiTNode) {
	if T != nil {
		PstOrderTraversePMCB(T.lchild)
		PstOrderTraversePMCB(T.rchild)
		pstMidArray[pstMidIdx] = T.data
		pstMidIdx++
	}
}

func TestPreMCreateBT(t *testing.T) {
	var T *BiTNode

	PreMidCreateTree(&T, 0, 0, len(mid))
	PreOrderTraversePMCB(T)

	s := string(preMidArray[:])
	if s != pre {
		t.Error("TestPreMCreateBT failed. preorder travers: ", s)
	} else {
		fmt.Println("TestPreMCreateBT finished.")
	}
}

func TestPstMCreateBT(t *testing.T) {
	var T *BiTNode

	PostMidCreateTree(&T, len(pst)-1, 0, len(mid))
	PstOrderTraversePMCB(T)

	s := string(pstMidArray[:])
	if s != pst {
		t.Error("TestPstMCreateBT failed. pstorder travers: ", s)
	} else {
		fmt.Println("TestPstMCreateBT finished.")
	}
}
