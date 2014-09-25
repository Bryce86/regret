package bt

import (
	"fmt"
)

//type ElemType byte
type BiTNode struct {
	data           byte
	lchild, rchild *BiTNode
}

//type BiTree *BiTNode

var usage bool = true

/*
	abd#gj##k###ce#h##fi###

	   a
	 /	\
    b    c
   / #  /  \
  d    e    f
 # \  # \   / #
	g   h  i
   / \ # # # #
  j   k
 # # # #

*/

func CreateTree(T **BiTNode) {
	if usage {
		fmt.Println("input: abc##de#g##f###")
		usage = false
	}

	/*
	   输入要严格按照正确的顺序才能结束.这里要用到二叉树的一个性质,
	   就是说对于有n个节点的二叉树,就有n+1个空域,在这里即为如果你输入了n个元素,
	   那么一定要有n+1个#才会结束迭代过程.
	*/
	var data byte
	fmt.Scanf("%c", &data)

	if data == '#' {
		*T = nil
	} else {
		if *T = new(BiTNode); *T != nil {
			(*T).data = data
			CreateTree(&((*T).lchild))
			CreateTree(&((*T).rchild))
		} else {
			return
		}
	}
}

func PreOrderTraverse(T *BiTNode) {
	if T != nil {
		fmt.Printf("%c", T.data)
		PreOrderTraverse(T.lchild)
		PreOrderTraverse(T.rchild)
	}
}

func InOrderTraverse(T *BiTNode) {
	if T != nil {
		InOrderTraverse(T.lchild)
		fmt.Printf("%c", T.data)
		InOrderTraverse(T.rchild)
	}
}

func PostOrderTraverse(T *BiTNode) {
	if T != nil {
		PostOrderTraverse(T.lchild)
		PostOrderTraverse(T.rchild)
		fmt.Printf("%c", T.data)
	}
}

func LevelOrderTraverse(T *BiTNode) {
	// queue
	const N int = 100
	front, rear := 0, 0
	var SqQueue [N]*BiTNode
	var p *BiTNode

	if T == nil {
		return
	}

	SqQueue[rear] = T
	rear = (rear + 1) % N

	for rear != front {
		p = SqQueue[front]
		front = (front + 1) % N

		fmt.Printf("%c", p.data)

		if p.lchild != nil {
			SqQueue[rear] = p.lchild
			rear = (rear + 1) % N
		}

		if p.rchild != nil {
			SqQueue[rear] = p.rchild
			rear = (rear + 1) % N
		}

	}
}

func PreOrderTraverseUnrec(T *BiTNode) {
	// stack
	const N int = 50
	top := 0
	var stack [N]*BiTNode
	var p *BiTNode

	p = T
	for p != nil || top > 0 {
		for p != nil {
			fmt.Printf("%c", p.data)
			stack[top] = p
			top++
			p = p.lchild
		}

		if top > 0 {
			top--
			p = stack[top]
			p = p.rchild
		}
	}
}

func InOrderTraverseUnrec(T *BiTNode) {
	// stack
	const N int = 50
	top := 0
	var stack [N]*BiTNode
	var p *BiTNode

	p = T
	for p != nil || top > 0 {
		for p != nil {
			stack[top] = p
			top++
			p = p.lchild
		}

		if top > 0 {
			top--
			p = stack[top]
			fmt.Printf("%c", p.data)
			p = p.rchild
		}
	}
}

func PostOrderTraverseUnrec(T *BiTNode) {
	const N int = 50
	top := 0
	var stack [N]*BiTNode
	var p *BiTNode

	p = T
	for p != nil || top > 0 {
		for p != nil {
			stack[top] = p
			top++

			if p.lchild != nil {
				p = p.lchild
			} else {
				p = p.rchild
			}
		}

		if top > 0 {
			top--
			p = stack[top]
			fmt.Printf("%c", p.data)

			if top > 0 && stack[top-1].rchild != p {
				p = stack[top-1].rchild
			} else {
				p = nil
			}
		}
	}
}

func GetBiTreeDepth(T *BiTNode) int {
	if T != nil {
		ldepth := GetBiTreeDepth(T.lchild)
		rdepth := GetBiTreeDepth(T.rchild)

		if ldepth > rdepth {
			return ldepth + 1
		} else {
			return rdepth + 1
		}
	} else {
		return 0
	}
}

func GetBiTreeLeaves(T *BiTNode) int {
	if T == nil {
		return 0
	} else if T.lchild == nil && T.rchild == nil {
		return 1
	} else {
		lLeaf := GetBiTreeLeaves(T.lchild)
		rLeaf := GetBiTreeLeaves(T.rchild)

		return (lLeaf + rLeaf)
	}
}

func GetBiTreeNodes(T *BiTNode) int {
	if T != nil {
		return GetBiTreeNodes(T.lchild) + GetBiTreeNodes(T.rchild) + 1
	} else {
		return 0
	}
}

func GetBiTreeNodesOfLevelK(T *BiTNode, k int) int {
	if T == nil || k < 1 {
		return 0
	} else if k == 1 {
		return 1
	} else {
		l := GetBiTreeNodesOfLevelK(T.lchild, k-1)
		r := GetBiTreeNodesOfLevelK(T.rchild, k-1)

		return l + r
	}
}

func CmpBiTree(T1, T2 *BiTNode) bool {
	if T1 == nil && T2 == nil {
		return true
	} else if T1 == nil || T2 == nil {
		return false
	} else {
		l := CmpBiTree(T1.lchild, T2.lchild)
		r := CmpBiTree(T1.rchild, T2.rchild)

		return l && r
	}
}

func TransformLRChild(T **BiTNode) *BiTNode {
	/* abdfegc */

	if *T != nil {
		l := TransformLRChild(&((*T).lchild))
		r := TransformLRChild(&((*T).rchild))

		(*T).lchild = r
		(*T).rchild = l

		return *T
	} else {
		return nil
	}
}

func BinaryTreeCall() {
	var T *BiTNode
	CreateTree(&T)

	fmt.Print("PreOrderTraverse: ")
	PreOrderTraverse(T)
	fmt.Println()

	fmt.Print("InOrderTraverse: ")
	InOrderTraverse(T)
	fmt.Println()

	fmt.Print("PostOrderTraverse: ")
	PostOrderTraverse(T)
	fmt.Println()

	fmt.Print("LevelOrderTraverse: ")
	LevelOrderTraverse(T)
	fmt.Println()

	fmt.Print("PreOrderTraverseUnrec: ")
	PreOrderTraverseUnrec(T)
	fmt.Println()

	fmt.Print("InOrderTraverseUnrec: ")
	InOrderTraverseUnrec(T)
	fmt.Println()

	fmt.Print("PostOrderTraverseUnrec: ")
	PostOrderTraverseUnrec(T)
	fmt.Println()

	fmt.Print("GetBiTreeDepth: ")
	fmt.Print(GetBiTreeDepth(T))
	fmt.Println()

	fmt.Print("GetBiTreeLeaves: ")
	fmt.Print(GetBiTreeLeaves(T))
	fmt.Println()

	fmt.Print("GetBiTreeNodes: ")
	fmt.Print(GetBiTreeNodes(T))
	fmt.Println()

	fmt.Print("GetBiTreeNodesOfLevelK: ")
	fmt.Print(GetBiTreeNodesOfLevelK(T, 4))
	fmt.Println()

	fmt.Print("CmpBiTree: ")
	fmt.Print(CmpBiTree(T, T))
	fmt.Println()

	fmt.Print("TransformLRChild: ")
	TT := TransformLRChild(&T)
	PreOrderTraverse(TT)
	fmt.Println()
}

func BiTreeCreatedCall() {
	var TPre *BiTNode
	fmt.Println("PreMidCreateTree ---")
	PreMidCreateTree(&TPre, 0, 0, len(mid))

	fmt.Print("PreOrderTraverse: ")
	PreOrderTraverse(TPre)
	fmt.Println()

	fmt.Print("InOrderTraverse: ")
	InOrderTraverse(TPre)
	fmt.Println()

	fmt.Print("PostOrderTraverse: ")
	PostOrderTraverse(TPre)
	fmt.Println()

	/***********************************/

	var TPost *BiTNode
	fmt.Println("PostMidCreateTree ---")
	PostMidCreateTree(&TPost, len(pst)-1, 0, len(mid))

	fmt.Print("PreOrderTraverse: ")
	PreOrderTraverse(TPost)
	fmt.Println()

	fmt.Print("InOrderTraverse: ")
	InOrderTraverse(TPost)
	fmt.Println()

	fmt.Print("PostOrderTraverse: ")
	PostOrderTraverse(TPost)
	fmt.Println()
}
