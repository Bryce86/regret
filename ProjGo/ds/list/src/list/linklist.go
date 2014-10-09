package list

import (
	"fmt"
	"math/rand"
	"time"
)

type LNode struct {
	data int
	next *LNode
}

func BuildLinkList(num int) *LNode {
	rand.Seed(time.Now().Unix())

	head := new(LNode)
	head.data = -1
	head.next = nil

	temp := head

	for i := 0; i < num; i++ {
		temp.next = new(LNode)
		temp = temp.next
		temp.data = rand.Intn(100)
		temp.next = nil
	}
	return head
}

func BuildSortedLinkList(num int) *LNode {
	head := new(LNode)
	head.data = -1
	head.next = nil

	temp := head

	for i := 0; i < num; i++ {
		temp.next = new(LNode)
		temp = temp.next
		temp.data = i
		temp.next = nil
	}
	return head
}

func BuildhasCircleList(num int) *LNode {
	rand.Seed(time.Now().Unix())

	head := new(LNode)
	head.data = -1
	head.next = nil

	temp := head
	intersect := new(LNode)

	for i := 0; i < num; i++ {
		temp.next = new(LNode)
		temp = temp.next
		temp.data = rand.Intn(100)
		temp.next = nil

		if i == num/2 {
			intersect = temp
		}
	}
	temp.next = intersect

	return head
}

func TraverseLinkList(l *LNode) {
	p := l.next

	for p != nil {
		fmt.Print(p.data, " ")
		p = p.next
	}
	fmt.Println()
}

func BuildTwoIntersectList(num int) (*LNode, *LNode) {
	rand.Seed(time.Now().Unix())
	head1 := new(LNode)
	head2 := new(LNode)
	head1.data = -1
	head2.data = -1

	temp1 := head1
	temp2 := head2
	intersect := new(LNode)

	for i := 0; i < num; i++ {
		temp1.next = new(LNode)
		temp1 = temp1.next
		temp1.data = rand.Intn(100)
		temp1.next = nil

		if i == num/2 {
			intersect = temp1
		}
	}

	for j := 0; j < num/2; j++ { // notice, only half nodes
		temp2.next = new(LNode)
		temp2 = temp2.next
		temp2.data = rand.Intn(100)
		temp2.next = nil
	}
	temp2.next = intersect

	return head1, head2
}

func GetOneNodefromList(L *LNode, value int) *LNode {
	if L == nil {
		return nil
	}

	pNode := L.next

	for pNode != nil {
		if pNode.data == value {
			return pNode
		}
		pNode = pNode.next
	}

	return nil
}

func GetListNodes(L *LNode) int {
	if L == nil || L.next == nil {
		return 0
	}

	count := 0
	pNode := L.next

	for pNode != nil {
		count++
		pNode = pNode.next
	}

	return count
}

func ReverseList(L **LNode) {
	if L == nil {
		return
	}

	if (*L) == nil {
		return
	}

	head := *L
	pNode := head.next
	var curr, temp *LNode = nil, nil

	for pNode != nil {
		curr = pNode
		pNode = pNode.next
		curr.next = temp
		temp = curr
	}
	head.next = temp
}

func GetReverseKthNode(L *LNode, k int) *LNode {
	if L == nil || k == 0 {
		return nil
	}

	curr1, curr2 := L.next, L.next

	for k > 1 && curr1 != nil {
		curr1 = curr1.next
		k--
	}

	if k > 1 || curr1 == nil {
		return nil
	}

	for curr1.next != nil {
		curr1 = curr1.next
		curr2 = curr2.next
	}

	return curr2
}

func GetMiddleNode(L *LNode) *LNode {
	if L == nil || L.next == nil {
		return nil
	}

	fast := L.next
	slow := L.next

	for fast != nil && fast.next != nil {
		fast = fast.next
		slow = slow.next
		if fast.next != nil {
			fast = fast.next
		}
	}
	return slow
}

func ReversetPrintListRec(L *LNode) {
	if L == nil {
		return
	}

	ReversetPrintListRec(L.next)
	fmt.Println(L.data)
}

func ReversetPrintListUnrec(L *LNode) {
	var stack [50]*LNode
	var top int
	L = L.next

	for L != nil {
		stack[top] = L
		top++
		L = L.next
	}

	for top > 0 {
		top--
		fmt.Print(stack[top].data, " ")
	}
	fmt.Println()
}

func ListHasCircle(L *LNode) bool {
	if L == nil {
		return false
	}

	fast := L.next
	slow := L.next

	for fast != nil && fast.next != nil {
		fast = fast.next.next
		slow = slow.next

		if fast == slow {
			return true
		}
	}

	return false
}

func ListIsIntersection(L1, L2 *LNode) bool {
	if L1 == nil || L2 == nil {
		return false
	}

	curr1 := L1.next
	curr2 := L2.next

	for curr1.next != nil {
		curr1 = curr1.next
	}

	for curr2.next != nil {
		curr2 = curr2.next
	}

	return curr1 == curr2
}

func GetFirstNodeOfTwoIntersectionLists(L1, L2 *LNode) *LNode {
	if L1 == nil || L2 == nil {
		return nil
	}

	var len1, len2 int = 1, 1
	curr1, curr2 := L1.next, L2.next

	for curr1.next != nil {
		len1++
		curr1 = curr1.next
	}

	for curr2.next != nil {
		len2++
		curr2 = curr2.next
	}

	if curr1 != curr2 {
		return nil
	}

	pNode1 := L1.next
	pNode2 := L2.next

	if len1 > len2 {
		k := len1 - len2
		for k > 0 {
			pNode1 = pNode1.next
			k--
		}
	} else {
		k := len2 - len1
		for k > 0 {
			pNode2 = pNode2.next
			k--
		}
	}

	for pNode1 != pNode2 {
		pNode1 = pNode1.next
		pNode2 = pNode2.next
	}

	return pNode1
}

func GetFirstNodeOfCircleList(L *LNode) *LNode {
	if L == nil {
		return nil
	}

	fast, slow := L.next, L.next
	for fast != nil && fast.next != nil {
		fast = fast.next.next
		slow = slow.next
		if fast == slow {
			break
		}
	}

	if fast == nil || fast.next == nil {
		return nil
	}

	pTail := slow
	pNode1 := L.next
	pNode2 := pTail.next

	var len1, len2 int = 1, 1

	for pNode1 != pTail {
		pNode1 = pNode1.next
		len1++
	}

	for pNode2 != pTail {
		pNode2 = pNode2.next
		len2++
	}

	pNode1 = L.next
	pNode2 = pTail.next

	if len1 > len2 {
		k := len1 - len2
		for k > 0 {
			pNode1 = pNode1.next
			k--
		}
	} else {
		k := len2 - len1
		for k > 0 {
			pNode2 = pNode2.next
			k--
		}
	}

	for pNode1 != pNode2 {
		pNode1 = pNode1.next
		pNode2 = pNode2.next
	}

	return pNode1
}

func DeleteOneNode(L, pToBeDeleted *LNode) {
	if L == nil || pToBeDeleted == nil {
		return
	}

	if pToBeDeleted.next != nil {
		pToBeDeleted.data = pToBeDeleted.next.data
		pToBeDeleted.next = pToBeDeleted.next.next
	} else { // be the last one
		if pToBeDeleted == L.next {
			L.next = nil
		} else {
			pNode := L.next
			for pNode.next != pToBeDeleted {
				pNode = pNode.next
			}
			pNode.next = nil
		}
	}
}
