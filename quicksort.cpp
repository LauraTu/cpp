#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int> &nums, int low, int high) {
	int pivot = nums[high];
	int s = low;
	int e = high;
	while (s < e) {
		while (nums[s] < pivot)
			s ++;
		while (nums[e] > pivot)
			e --;
		if (s == e) return s;
		if (nums[s] == nums[e])
			e --;
		else swap(nums[s],nums[e]);
	}
	return s;
}

void quicksort(vector<int> &nums, int low, int high) {
	if (low >= high) return;
	int p = partition(nums, low, high);
	quicksort(nums, low, p-1);
	quicksort(nums, p+1, high);
}

int main() {
	vector<int> v = {4,3,0,2,3,5,1,3};
	// int n3 = partition(v,0,v.size()-1);
	quicksort(v,0,v.size()-1);
	for(auto x:v)
		cout << x << " ";
	cout << endl;
	// cout << n3 << endl;
	return 0;
}