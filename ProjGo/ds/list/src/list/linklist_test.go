package list

import (
	"fmt"
	"testing"
)

func TestBuildLinkList(t *testing.T) {
	L := BuildLinkList(10)
	if L == nil || GetListNodes(L) != 10 {
		t.Error("Test BuildLinkList failed.")
	} else {
		fmt.Print("Test BuildLinkList success. ")
		TraverseLinkList(L)
	}
}

func TestBuildSortedLinkList(t *testing.T) {
	L := BuildSortedLinkList(10)
	if L == nil || GetListNodes(L) != 10 {
		t.Error("Test BuildSortedLinkList failed.")
	} else {
		fmt.Print("Test BuildSortedLinkList success. ")
		TraverseLinkList(L)
	}
}

func TestBuildhasCircleList(t *testing.T) {
	L := BuildhasCircleList(10)
	if L == nil {
		t.Error("Test BuildhasCircleList failed.")
	} else {
		fmt.Println("Test BuildhasCircleList success.")
	}
}

func TestBuildTwoIntersectList(t *testing.T) {
	L1, L2 := BuildTwoIntersectList(10)
	if L1 == nil || L2 == nil || GetListNodes(L1) != 10 || GetListNodes(L2) != 10 {
		t.Error("Test BuildTwoIntersectList failed.")
	} else {
		fmt.Print("Test BuildTwoIntersectList success.\n")
		fmt.Print("L1: ")
		TraverseLinkList(L1)
		fmt.Print("L2: ")
		TraverseLinkList(L2)
	}
}

func TestGetOneNodefromList(t *testing.T) {
	L := BuildSortedLinkList(10)
	L1 := GetOneNodefromList(L, 5)
	if L == nil || L1 == nil {
		t.Error("Test GetOneNodefromList failed.")
	} else {
		fmt.Printf("Test GetOneNodefromList success. value: %d\n", L1.data)
	}
}

func TestGetListNodes(t *testing.T) {
	var n int
	L := BuildSortedLinkList(10)
	n = GetListNodes(L)
	if n != 10 {
		t.Error("Test GetListNodes failed. %d nodes", n)
	} else {
		fmt.Printf("Test GetListNodes success. %d nodes\n", n)
	}
}

func TestReverseList(t *testing.T) {
	L := BuildLinkList(10)

	var tempArray [10]int
	pNode := L.next
	for i := 0; i < 10; i++ {
		tempArray[i] = pNode.data
		pNode = pNode.next
	}

	ReverseList(&L)
	pNode = L.next
	for i := 9; i >= 0; i-- {
		if tempArray[i] != pNode.data {
			t.Error("Test ReverseList failed.\n")
			goto err
		}
		pNode = pNode.next
	}
	fmt.Println("Test ReverseList success.")
err:
	fmt.Print("Origin:  ")
	for i := 0; i < len(tempArray); i++ {
		fmt.Print(tempArray[i], " ")
	}
	fmt.Println()
	fmt.Print("Reverse: ")
	TraverseLinkList(L)
}

func TestGetReverseKthNode(t *testing.T) {
	L := BuildSortedLinkList(10)
	L1 := GetReverseKthNode(L, 3)

	if L1 != nil || L1.data == 7 {
		fmt.Println("Test GetReverseKthNode success.")
	} else {
		t.Error("Test GetReverseKthNode failed.")
	}
	fmt.Print("The List is : ")
	L = L.next
	for L != nil {
		fmt.Print(L.data, " ")
		L = L.next
	}
	fmt.Printf("\nThe reverse 3 value is %d\n", L1.data)
}

func TestGetMiddleNode(t *testing.T) {
	L := BuildSortedLinkList(10)
	L1 := GetMiddleNode(L)
	if L1.data == 5 {
		fmt.Println("Test GetMiddleNode success. mid val is ", L1.data)
	} else {
		t.Error("Test GetMiddleNode failed. mid val is ", L1.data)
	}
}

func TestReversetPrintListRec(t *testing.T) {
	L := BuildSortedLinkList(10)
	fmt.Println("Test ReversePrintListRec: ")
	ReversetPrintListRec(L.next) // remove head node
}

func TestReversetPrintListUnrec(t *testing.T) {
	L := BuildSortedLinkList(10)
	fmt.Print("Test ReversePrintListUnrec: ")
	ReversetPrintListUnrec(L) // remove head node
}

func TestListHasCircle(t *testing.T) {
	L := BuildhasCircleList(10)
	flag := ListHasCircle(L)
	if flag {
		fmt.Println("Test ListHasCircle success. ", flag)
	} else {
		t.Error("Test ListHasCircle failed. ", flag)
	}
}

func TestListIsIntersection(t *testing.T) {
	L1, L2 := BuildTwoIntersectList(10)
	flag := ListIsIntersection(L1, L2)

	if flag {
		fmt.Println("Test ListIsIntersection success. ", flag)
	} else {
		t.Error("Test ListIsIntersection failed. ", flag)
	}
}

func TestGetFirstNodeOfTwoIntersectionLists(t *testing.T) {
	L1, L2 := BuildTwoIntersectList(10)
	L3 := GetFirstNodeOfTwoIntersectionLists(L1, L2)

	fmt.Print("List 1: ")
	pNode1 := L1.next
	for pNode1 != nil {
		fmt.Print(pNode1.data, " ")
		pNode1 = pNode1.next
	}
	fmt.Println()

	fmt.Print("List 2: ")
	pNode2 := L2.next
	for pNode2 != nil {
		fmt.Print(pNode2.data, " ")
		pNode2 = pNode2.next
	}
	fmt.Println()

	fmt.Printf("The first intersect node : %d\n", L3.data)
}

func TestGetFirstNodeOfCircleList(t *testing.T) {
	L := BuildhasCircleList(10)
	L1 := GetFirstNodeOfCircleList(L)
	if L1 == nil {
		t.Error("Test GetFirstNodeOfCircleList failed.")
	} else {
		fmt.Printf("Test GetFirstNodeOfCircleList success. 1st node : %d\n", L1.data)
	}
}

func TestDeleteOneNode(t *testing.T) {
	L := BuildSortedLinkList(10)
	DeleteNode := GetOneNodefromList(L, 5)
	DeleteOneNode(L, DeleteNode)

	L = L.next
	for L != nil {
		fmt.Print(L.data, " ")
		L = L.next
	}
	fmt.Println()
}
