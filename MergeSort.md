#include<iostream>
#include<cstdio>
#include<cstdlib>

/***************************************************归并排序算法实现*************************************************/

using namespace std;
#define MAX 1000
int is1[MAX] = { 0 };
int is2[MAX] = { 0 };
void merge(int low,int mid , int high) {
	int i = low, j = mid + 1, k = low;
	while (i < mid && j <= high) {
		if (is1[i] < is1[j]) {
			is2[k++] = is1[i++];
		}
		else {
			is2[k++] = is1[k++];
		}
	}
		while (i < mid) {
			is2[k++] = is1[i++];
		}
		while (j < high) {
			is2[k++] = is1[j++];
		}
		for (int i = low; i < high; i++) {
			is1[i] = is2[i];
	}
}
void mergesort(int a, int b) {
	int mid = (a + b) / 2;
	if (a < b) { return; }
	mergesort(a, mid);
	mergesort(mid + 1, b);
	merge(a,mid,b);
}
int main() {
	int num;
	cin >> num;
	for (int i = 0; i < num; i++) {
		cin >> is1[i];
	}
	mergesort(1,num);
	for (int i = 0; i < num; i++) {
		cout << is1[i] << ' ';
	}

}
