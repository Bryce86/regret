package DS

import (
	"strings"
)

var pre string = "ABDHLEKCFG"
var mid string = "HLDBEKAFCG"
var pst string = "LHDKEBFGCA"

/* 确定c在中序序列mid中的下标,假设树的各个节点的值各不相同 */
func Position(s string, c byte) int {
	return strings.IndexByte(s, c)
}

/*  利用前序中序序列创建树
*        i: 子树的前序序列字符串的首字符在pre[]中的下标
*        j: 子树的中序序列字符串的首字符在mid[]中的下标
*      len: 子树的字符串序列的长度
 */
func PreMidCreateTree(T **BiTNode, i, j, length int) {
	if length <= 0 {
		*T = nil
		return
	}

	*T = new(BiTNode)
	(*T).data = pre[i]

	m := Position(mid, pre[i])
	PreMidCreateTree(&((*T).lchild), i+1, j, m-j)                    //m-j为左子树字符串长度
	PreMidCreateTree(&((*T).rchild), i+(m-j)+1, m+1, length-(m-j)-1) //len-1-(m-j)为右子树字符串长度
}

/*  利用后序中序序列创建树
*        i: 子树的后序序列字符串的尾字符在post[]中的下标
*        j: 子树的中序序列字符串的首字符在mid[]中的下标
*      len: 子树的字符串序列的长度
 */

func PostMidCreateTree(T **BiTNode, i, j, length int) {
	if length <= 0 {
		*T = nil
		return
	}

	*T = new(BiTNode)
	(*T).data = pst[i]

	m := Position(mid, pst[i])
	PostMidCreateTree(&((*T).lchild), i-1-(length-1-(m-j)), j, m-j) //注意参数:m-j左子树的长度,len-1-(m-j)右子树的长度
	PostMidCreateTree(&((*T).rchild), i-1, m+1, length-1-(m-j))
}
