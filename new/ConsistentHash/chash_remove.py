#!/usr/bin/env python3

import hashlib
import bisect
from collections import Counter

class ConsistentHash:
    def __init__(self, virtual_nodes=150):
        self.virtual_nodes = virtual_nodes
        self.ring = []
        self.node_map = {}
        self.nodes = set()

    def _hash(self, key):
        return int(hashlib.md5(key.encode()).hexdigest(), 16) % (2**32)

    def add_node(self, node):
        self.nodes.add(node)
        for i in range(self.virtual_nodes):
            h = self._hash(f"{node}#{i}")
            self.ring.append(h)
            self.node_map[h] = node
        self.ring.sort()

    def remove_node(self, node):
        self.nodes.discard(node)
        self.ring = [h for h in self.ring if self.node_map[h] != node]
        # 清理 node_map 中该节点的所有虚拟节点
        to_delete = [h for h, n in self.node_map.items() if n == node]
        for h in to_delete:
            del self.node_map[h]

    def get_node(self, key):
        if not self.ring:
            return None
        key_hash = self._hash(key)
        idx = bisect.bisect_left(self.ring, key_hash)
        if idx >= len(self.ring):
            idx = 0
        return self.node_map[self.ring[idx]]


# ========== 节点宕机 Demo ==========
if __name__ == "__main__":
    ch = ConsistentHash(virtual_nodes=100)

    # 1. 初始 4 个节点
    for node in ["Node-A", "Node-B", "Node-C", "Node-D"]:
        ch.add_node(node)

    # 2. 生成 1000 个 key，记录初始分布
    keys = [f"order:{i}" for i in range(1000)]
    mapping_before = {k: ch.get_node(k) for k in keys}

    print("=== 宕机前（4 节点）===")
    for node, count in Counter(mapping_before.values()).most_common():
        print(f"  {node}: {count} 个 key")

    # 3. 模拟 Node-C 宕机
    ch.remove_node("Node-C")
    mapping_after = {k: ch.get_node(k) for k in keys}

    print("\n=== Node-C 宕机后（3 节点）===")
    for node, count in Counter(mapping_after.values()).most_common():
        print(f"  {node}: {count} 个 key")

    # 4. 详细统计迁移情况
    moved_from_c = 0   # 原本在 C 上，迁移到别处的
    moved_other = 0    # 原本不在 C 上，但也受影响的（理论上应该为 0）
    for k in keys:
        if mapping_before[k] == "Node-C" and mapping_after[k] != "Node-C":
            moved_from_c += 1
        elif mapping_before[k] != "Node-C" and mapping_before[k] != mapping_after[k]:
            moved_other += 1

    print(f"\n--- 迁移详情 ---")
    print(f"  原 Node-C 上的 key 数: {sum(1 for v in mapping_before.values() if v == 'Node-C')}")
    print(f"  其中迁移到其他节点的: {moved_from_c} 个")
    print(f"  其他节点受影响的: {moved_other} 个（应为 0）")
    print(f"\n  总迁移量: {moved_from_c} / 1000（约 {moved_from_c/10}%）")
    print(f"  （传统 hash%N 方案：4→3 节点时，约 250 个 key 全部重映射）")

