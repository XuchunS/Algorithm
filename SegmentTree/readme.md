## 线段树
线段树可以在logN的时间复杂度内实现单点修改、区间修改、区间查询（区间求和，求区间最大值，求区间最小值）等操作。
### 关键操作
1. pushup
2. pushdown 懒标记， 启发于 线段树的 查询过程
            即若当前点所代表的区间完全包含于 要修改的区间内，（tr[u].l >= l && tr[u].r <= r) 则将该区间
            更新后，就不再往下更新。

### 关键函数
- build 构建线段树
- modify 
  - 修改单点 -> pushup
  - 区间修改 -> pushdown