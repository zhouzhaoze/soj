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
#define N 1010
double mem[N][N];
int a[N];
int n;

struct point {
	double x;
	double y;
} points[N];

double dist(int i, int j) {
	double dx = (points[i].x - points[j].x);
	double dy = (points[i].y - points[j].y);
	return sqrt(dx * dx + dy * dy);
}

double dp(int i, int j) {
	if (mem[i][j] != -1) return mem[i][j];
	double &ret = mem[i][j];

	if (i == n-1 || j == n-1) // 这里判断终点的时候错了
		return ret = dist(i, j);
	else {
		int next = max(i, j) + 1;
		ret = min( dist(i, next) + dp(next, j), dist(j, next) + dp(i, next) );
	}	
	return ret;
}

int main() {
	int counter = 0;
	while(cin >> n && n != 0) {				
		for (int i = 0; i < n; ++i) 
			for (int j = 0; j < n; ++j) 
				mem[i][j] = -1;
		for (int i = 0; i < n; ++i) 
			cin >> points[i].x >> points[i].y;

		printf("%.2f\n", dist(0, 1) + dp(0, 1));
	}
}