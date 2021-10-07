// 最长上升子序列 O(nlogn)解法
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
int arr[N];

int n;
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
        
        len = max(len, r + 1);
        arr[r + 1] = num;
    }
    
    cout << len << endl;
    
    return 0;
}