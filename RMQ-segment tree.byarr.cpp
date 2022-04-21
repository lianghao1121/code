#include<iostream>
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
void updataTree(int arr[], int tree[], int node, int start, int end, int idx, int val) {  /*updatatree的具体实现*/
	if (start==end){
		arr[idx] = val;   /*updatatree的形参所传输的idx是根据原序列数组所想改变的位置来确立的，所以如果要更改原序列数组里面的
值，则直接arr[idx]=val即可*/
		tree[node] = val; /*若想在线段树的数组表示来修改某个值，需要去确定其元素的位置，依靠不断地去改变node来搜索正确的值
因为每次判断为否的时候，会带入left，right的坐标，形式上来更换抽象的线段树的左右孩子*/
	}
	else {
		int mid = (start + end) / 2;
		int left_node = node * 2 + 1;
		int right_node = node * 2 + 2;
		if (idx >= start && idx <= mid) {
			updataTree(arr, tree, node, start, mid, idx, val);
		}
		else {
			updataTree(arr, tree, node, mid + 1, end, idx, val);
		}
		tree[node] = tree[left_node] + tree[right_node];
	}
}
int query_tree(int arr[], int tree[], int& node, int start, int end, int& L, int& R) {
			/*此树需要求需求范围的的序列元素的和，sum，和其他的一样，需要原始序列的数组，以及以数组储存的线段二叉树，和其他的函数
类似，但是不同的是此函数需要所求序列的区间，也就L和R*/
	if (R<start || L>end) return 0;
	if (start == end) {
		return arr[node];
	}
	else if (L <= start && end >= R) {
		return tree[node];
	}else {
		int mid = (start + end) / 2;
		int left_node = 2 * node + 1;
		int right_node = 2 * node + 2;
		int sum_left = query_tree(arr, tree, left_node, start, mid, L, R);
		int sum_right = query_tree(arr, tree, right_node, mid + 1, end, L, R);
		return sum_left + sum_right;
	}
}
int main() {
	int arr[] = {1,3,5,7,9,11};
	auto size =6;
	int idx = 4;
	int val = 6; /*将arr数组下表为4位置的7改为6，即为更新此序列的排序*/
	int tree[MAX_LEN] = { 0 };
	buildtree(arr,tree, 0, 0, size - 1);  /*第一个‘0’代表着线段树的根，因为此树是用数组表示的，所以他的根节点就储存在第一个
位置，start代表arr的下标，因为开始也是0，所以就是0，end即为6-1=5*/

	updataTree(arr, tree, 0, 0, size - 1, idx, val); /*updatatree的所需形参和buildtree的形参类似，都需要原所需序列，用
数组来容纳哦，还需要一个数组表示的线段树的容器，以及抽象线段树的根，也就是容器数组的第一个位置0，接下来就需要start和end，也就是所
给序列的数组的开始下表和最后一个元素的下表，最后的idx是index的缩写，也就是说是user所需要改所给序列的位置，val则为需改修改原序列的值
*/
	query_tree(arr, tree, 0, 0, size - 1, L, R);


}
/*以上的left，right，node，start，end均为arr的下标*/
