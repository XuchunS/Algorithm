// 最长上升子序列 O(nlogn)解法

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
int arr[N];

int n;

// 计算覆盖整个序列至少需要多少个上升子序列
void compute_how_many() {
    int cnt = 0;
    int q[10000];
    for (int i = 0; i < n; ++ i) {
        int k = 0;
        while (k < cnt && q[k] < arr[i]) k ++; // 从前往后找，第一个找到的一定是最接近 当前值的
        if (k == cnt) q[cnt ++] = arr[i];
        else q[k] = arr[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n; 
    int len = 0;
    for (int i = 0; i < n; ++ i) {
        int num; cin >> num;
        int l = 0, r = len;
        while (l < r) {
            int mid = l + (r - l + 1) / 2;
            if (arr[mid] < num) l = mid;
            else r = mid - 1;
        }
        // 不同长度的上升序列 其最大值 是单调递增的
        len = max(len, r + 1);  
        arr[r + 1] = num;
    }
    
    cout << len << endl;
    
    return 0;
}