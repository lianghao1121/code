# #include<iostream>
#include<cstdio>
using namespace std;
#define MAX_LEN 1000
void buildtree(int arr[], int tree[], int node, int start, int end) {
	if (start == end) {
		tree[node] = arr[start];  /*到达叶子,则将arr中的元素放入tree的位置中，全程均为数组表达*/
	}
	else {
		int left_node = 2 * node + 1;
		int right_node = 2 * node + 2;
		int mid = (start + end) / 2;
		buildtree(arr, tree, left_node, start, mid);
		buildtree(arr, tree, right_node, mid + 1, end);
		tree[node] = tree[left_node] + tree[right_node];
	}
}
int main() {
	int arr[] = {1,2,5,7,9,11};
	auto size =6;
	int tree[MAX_LEN] = { 0 };
	buildtree(arr, tree, 0, 0, size - 1);  /*第一个‘0’代表着线段树的根，因为此树是用数组表示的，所以他的根节点就储存在第一个
位置，start代表arr的下标，因为开始也是0，所以就是0，end即为6-1=5*/

}
/*以上的left，right，node，start，end均为arr的下标*/
