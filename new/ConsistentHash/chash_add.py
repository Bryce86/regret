#!/usr/bin/env python3

import hashlib
import bisect

class ConsistentHash:
    def __init__(self, virtual_nodes=150):
        self.virtual_nodes = virtual_nodes
        self.ring = []          # 有序列表，存虚拟节点的哈希值
        self.node_map = {}      # 哈希值 → 物理节点名
        self.nodes = set()      # 当前所有物理节点

    def _hash(self, key):
        """用 md5 生成 32 位无符号整数哈希"""
        return int(hashlib.md5(key.encode()).hexdigest(), 16) % (2**32)

    def add_node(self, node):
        """添加物理节点，同时创建虚拟节点"""
        self.nodes.add(node)
        for i in range(self.virtual_nodes):
            vnode_key = f"{node}#{i}"
            h = self._hash(vnode_key)
            self.ring.append(h)
            self.node_map[h] = node
        self.ring.sort()  # 保持有序，方便二分查找

    def remove_node(self, node):
        """删除物理节点及其所有虚拟节点"""
        self.nodes.discard(node)
        new_ring = []
        for h in self.ring:
            if self.node_map[h] != node:
                new_ring.append(h)
            else:
                del self.node_map[h]
        self.ring = new_ring

    def get_node(self, key):
        """查找 key 归属的节点：顺时针找第一个 >= key_hash 的虚拟节点"""
        if not self.ring:
            return None
        key_hash = self._hash(key)
        # 二分查找第一个 >= key_hash 的位置
        idx = bisect.bisect_left(self.ring, key_hash)
        # 如果没找到（key_hash 比所有节点都大），绕回到环开头
        if idx >= len(self.ring):
            idx = 0
        return self.node_map[self.ring[idx]]


# ========== Demo ==========
if __name__ == "__main__":
    ch = ConsistentHash(virtual_nodes=50)

    # 1. 初始 3 个节点
    ch.add_node("Node-A")
    ch.add_node("Node-B")
    ch.add_node("Node-C")

    # 2. 生成 1000 个测试 key，记录每个 key 归属哪个节点
    keys = [f"user:{i}" for i in range(1000)]
    mapping_before = {k: ch.get_node(k) for k in keys}

    # 统计各节点负载
    from collections import Counter
    print("=== 扩容前（3 节点）===")
    for node, count in Counter(mapping_before.values()).most_common():
        print(f"  {node}: {count} 个 key")

    # 3. 新增一个节点
    ch.add_node("Node-D")
    mapping_after = {k: ch.get_node(k) for k in keys}

    print("\n=== 扩容后（4 节点）===")
    for node, count in Counter(mapping_after.values()).most_common():
        print(f"  {node}: {count} 个 key")

    # 4. 统计迁移量
    moved = sum(1 for k in keys if mapping_before[k] != mapping_after[k])
    print(f"\n总共 1000 个 key，扩容后迁移了 {moved} 个（{moved/10}%）")
    print("（传统 hash%N 方案会迁移约 750 个）")
