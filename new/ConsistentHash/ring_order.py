#!/usr/bin/env python3

import hashlib
import bisect

class ConsistentHash:
    def __init__(self, virtual_nodes=150):
        self.virtual_nodes = virtual_nodes
        self.ring = []
        self.node_map = {}

    def _hash(self, key):
        return int(hashlib.md5(key.encode()).hexdigest(), 16) % (2**32)

    def add_node(self, node):
        for i in range(self.virtual_nodes):
            h = self._hash(f"{node}#{i}")
            self.ring.append(h)
            self.node_map[h] = node
        self.ring.sort()

    def get_ring_order(self):
        """返回环上所有虚拟节点的排列顺序"""
        return [f"{self.node_map[h]}(位置{h})" for h in self.ring]


# ========== 验证脚本 ==========
if __name__ == "__main__":
    # 方案一：按 A → B → C 的顺序加入
    ch1 = ConsistentHash(virtual_nodes=5)  # 为了演示清晰，每个节点只生成5个虚拟节点
    ch1.add_node("A")
    ch1.add_node("B")
    ch1.add_node("C")

    # 方案二：按 C → A → B 的顺序加入（完全打乱）
    ch2 = ConsistentHash(virtual_nodes=5)
    ch2.add_node("C")
    ch2.add_node("A")
    ch2.add_node("B")

    # 获取两种方案的环上排列
    order1 = ch1.get_ring_order()
    order2 = ch2.get_ring_order()

    print("=== 方案一：按 A → B → C 顺序加入 ===")
    for i, item in enumerate(order1):
        print(f"  位置 {i+1}: {item}")

    print("\n=== 方案二：按 C → A → B 顺序加入 ===")
    for i, item in enumerate(order2):
        print(f"  位置 {i+1}: {item}")

    # 对比结果
    print("\n=== 结论 ===")
    if order1 == order2:
        print("✅ 两种顺序的环上排列完全一致！")
        print("   说明：加入顺序不影响最终排列，只由哈希函数决定。")
    else:
        print("❌ 两种顺序的环上排列不同。")
        print("   （这种情况通常是因为哈希函数中包含了顺序相关的变量）")

