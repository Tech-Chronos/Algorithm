# 🔥 LRU 缓存机制（面试笔记）

---

## 一、LRU 是什么？
LRU（Least Recently Used） = 最近最少使用淘汰策略

👉 核心思想：
- 最近用过 → 保留  
- 很久没用 → 删除  

---

## 二、需要支持的操作
```cpp
get(key)        // O(1)
put(key, value) // O(1)
```

---

## 三、核心数据结构（重点🔥）

👉 **哈希表 + 双向链表**

### 1️⃣ 哈希表（unordered_map）
```cpp
key -> Node*
```
作用：
- O(1) 找到节点

---

### 2️⃣ 双向链表
```text
head <-> ... <-> tail
```

- head：最近使用  
- tail：最久未使用  

👉 必须用双向链表原因：
- O(1) 删除任意节点  
- O(1) 插入  

---

## 四、节点结构

```cpp
struct Node {
    int key, value;
    Node* prev;
    Node* next;
};
```

---

## 五、关键设计（非常重要）

👉 使用虚拟头节点 + 虚拟尾节点

```text
head <-> ... <-> tail
```

优点：
- 避免空指针判断  
- 统一逻辑  

---

## 六、核心操作

---

### ⭐ 1. get(key)

```text
如果 key 不存在 → 返回 -1

如果存在：
    1. 找到节点
    2. 移动到头部
    3. 返回 value
```

---

### ⭐ 2. put(key, value)

---

#### ✅ 情况1：key 已存在

```text
1. 更新 value
2. 移动到头部
```

---

#### ✅ 情况2：key 不存在

```text
1. 创建节点
2. 插入到头部
3. 加入哈希表
```

---

#### ⚠️ 如果容量满了：

```text
1. 删除尾节点
2. 从哈希表删除 key
```

---

## 七、核心函数（建议背🔥）

### 插入头部
```cpp
void addToHead(Node* node);
```

---

### 删除节点
```cpp
void removeNode(Node* node);
```

---

### 移动到头部
```cpp
void moveToHead(Node* node) {
    removeNode(node);
    addToHead(node);
}
```

---

### 删除尾节点
```cpp
Node* removeTail() {
    Node* node = tail->prev;
    removeNode(node);
    return node;
}
```

---

## 八、整体流程总结

👉 LRU = hashmap + 双向链表

- get → 查 + 移到头  
- put → 更新/插入 + 可能删尾  

---

## 九、时间复杂度

| 操作 | 复杂度 |
|------|--------|
| get  | O(1) |
| put  | O(1) |

---

## 十、面试加分点🔥

- 为什么不用数组？  
  → 删除中间元素 O(n)

- 为什么不用单链表？  
  → 无法 O(1) 删除

- 为什么用虚拟头尾？  
  → 简化边界处理

- STL 能用吗？  
  → 可以用 unordered_map  
  → 不建议用 LinkedHashMap（面试可能不允许）

---

## 十一、一句话总结（必背🔥）

```text
LRU = hashmap + double linked list

head = 最近使用
tail = 最久未使用

get → 查 + 移到头
put → 更新/插入 + 可能删尾
```