#include<iostream>
using namespace std;
const int maxn = 1050;
int s[maxn + 1];
int init_set() {   /*数组初始化*/
	for (int i = 1; i <= maxn; i++)
		s[i] = i;
}

int find_set(int x) {
	if(x!=s[x]) s[x]= find_set(s[x]);  
	return s[x];  /*优化是返回朋友的头头的节点，递归返回的均为朋友的头头的值，这样子所有朋友都指向朋友的头头*/
}
void union_set(int x, int y) {
	x = find_set(x);    /*find_set函数返回的是朋友的头头，那么下x和y分别为x的朋友的头头和y朋友的头头*/
	y = find_set(y);
	if (x != y) s[x] = s[y];	/*若x和y的头头不相等，则将s【y】的值给s[x],这样子就把x的串给y了，x和y都为朋友*/
}
int main() {
	int t, n, m, x, y;
	cin >> t;
	while (t--) {
		cin >> n >> m;
		init_set();
		for (int i = 1; i <= m; i++) {
			cin >> x >> y;
			union_set(x, y);
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			if (s[i] == i)
				ans++;
			cout << ans << endl;
		}
	}
	return 0;
}
