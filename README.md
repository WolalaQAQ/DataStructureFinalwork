# DataStructureFinalwork
东北大学2023年数据结构课设

## 构建
### 依赖
- CMake >= 3.20
- Ninja
- G++ >= 12.2
- Graphviz

```bash
sudo apt install cmake ninja-build g++-12 graphviz
```
### 编译
```bash
mkdir build && cd build
cmake .. -GNinja
ninja
```

## Problem A
### 校园光纤网络铺设
#### [问题描述]
东北大学铺设校园光纤网络。假设有N个学院和办公楼，只需要铺设N-1条光缆通道。采用最小生成树的算法，给出一个最佳铺设方案。
#### [设计要求]
设计基于最小生成树的校园光缆铺设程序。

（1）采用图结构、并集树等数据结构。

（2）可以随机、文件及人工输入数据。

（3）采用克鲁斯卡尔算法设计最小代价生成树

（4）可以采用堆排序算法选择权值最小的边。

（5）采用并集树完成树边的查询和合并。

（6）其它完善性或扩展性功能。

## Problem B
### 邮局选址问题
#### [问题描述]
n个居民小区规则的坐落在城市中，用x表示东西向，用y表示南北向。如何选择邮局的最佳位置，才能使n个居民小区到邮局的费用为最省。
#### [设计要求]
采用最短路径算法求解。

（1）采用STL数据结构或设计基于STL框架的数据结构。

（2）应用基本运算，设计算法求解。
