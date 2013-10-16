#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int mem[1001][1001];
int a[1001];
int n;

int dp(int i, int j) {
	if (mem[i][j] != -1) return mem[i][j];
	int &ret = mem[i][j];
    ret = i+1 == j? abs(a[i]-a[j]):
		max(
			(a[i]-max(a[i+1], a[j])) + (a[i+1] >= a[j]? dp(i+2,j):dp(i+1,j-1)), 
			(a[j]-max(a[j-1], a[i])) + (a[i] >= a[j-1]? dp(i+1,j-1):dp(i,j-2)) 
			);
	return ret;
}

int main() {
	int counter = 0;
	while(cin >> n && n != 0) {				
		for (int i = 0; i < n; ++i) 
			for (int j = 0; j < n; ++j) 
				mem[i][j] = -1;
		for (int i = 0 ; i < n; ++i) 
			cin >> a[i];

		printf("In game %d, the greedy strategy might lose by as many as %d points.\n", ++counter, dp(0, n-1));
	}
}