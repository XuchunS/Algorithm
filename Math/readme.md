## 数学相关

### 分解质因数
```c++
for (int i = 2; i * i <= num; ++i) {
    if (num % i == 0) {
        int s = 0;
        while (num % i == 0) {
            num /= i;
            s ++;
        }
        cout << i << " " << s << endl;
    }
}
if (num > 1) cout << num << " " << "1" << endl;
```

### 线性筛质数
```c++
// 线性时间筛出小于 n 的所有质数
void get_primes(int n)
{
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}
```

### 计算几何
#### 1. 基础
1. 叉积 A(x1, y1), B(x2, y2);
- 几何：表示由A 和 B构成的三角形面积的两倍
- 值： x1*y2 - x2*y1

```c++
double cross(Point a, Point b)
{
    return a.x * b.y - b.x * a.y;
}
```

2. 向量(x, y)顺时针旋转角度 a
(x, y) 乘矩阵 [cos(a), -sin(a); sin(a), cos(a)]

3. 直线表示
- 点向式， 过点P0: P0 + tV(V 是方向向量)

4. 求两直线的交点
直线 P + tV 和 Q + tW
```c++
Point get_line_intersection(Point P, Vector v, Point Q, Vector w) {
    Vector u = P - Q;
    double t = cross(w, u) / cross(v, w);
    return P + tv;
}
```

5. 点到直线的距离

6. 点到线段的距离

7. 点在直线上的投影

8. 点是否在线段上

9. 判断两线段是否相交

#### 2. 多边形
1. 三角形
- 面积
  - 海伦公式
    p = (a + b + c) / 2; S = sqrt(p * (p-a) * (p-b) * (p-c));

2. 求任意多边形的面积
可以取第一个点，把凸多边形分成 n - 2个三角形
```c++
double polygon_area(Point p[], int n) {
    double s = 0;
    for (int i = 1; i < n - 1; ++i) {
        s += cross(p[i] - p[0], p[i + 1] - p[i]);
    }
    return s / 2;
}
```
- 皮克定理
若多边形的顶点都是整点，则S = a + b / 2 - 1;
a 是内部的整点个数，b是边上的整点个数

3. 判断点是否在多边形内（任意多边形）
- 转角法
  - 如果在多边形内，该点和多边形每个点构成的向量，其转过的角度为360.
  - 如果在多边形外，该点转过的角度为0.

- 射线法
以该点做一条随机射线（不要平行）
  - 若点在多边形内部，则穿过边奇数次
  - 若点在多边形外部，则穿过边偶数次


#### 3. 凸包求解
Andrew算法求凸包
- 将所有点排序，横坐标相同，再比较纵坐标


### 博弈论
1. 公平组合游戏ICG
- 条件：
  - 两名玩家交替行动
  - 游戏的任意时刻，可以执行的合法行动与轮到哪位玩家无关

- 先手必胜状态：可以找到一个必败状态
- 先手必败状态：走不到任何一个必败状态

2. NIM游戏
n堆石头，两名玩家，每次都必须从一堆石头中拿若干（不能不拿），谁最后拿完谁赢。
- a1,a2, a3, a4,....an
- 若 a1 ^ a2 ^ a3 ^ ... ^ an = 0, 则先手必败
- 若不等于0， 则先手必胜
（深入思考一下，异或和这东西就是每一位都成对）

3. SG函数
- Mex函数： 设S表示一个非负整数集合，Mex(s)为求出不属于S的最小非负整数
- SG函数

4. 对于当前状态，枚举每种可能的下一步，若有一种情况返回必胜，则当前状态必胜