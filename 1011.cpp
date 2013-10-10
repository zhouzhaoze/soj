#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <cmath>

using namespace std;
#define NMAX 2010
#define MMAX 11

long long mem[NMAX][MMAX];

long long dp(int i, int j, int m, int depth) {
	long long ret;
	if (mem[i][j] >= 0)
		ret = mem[i][j];
	else if (i > m) {
		ret = mem[i][j] = 0;
	} else if (j == 1) {
		ret = mem[i][j] = 1;
	}
	else {
		long long s=0;
		for (int ii = 2*i; ii <= m; ++ii) {
			s += dp(ii, j-1, m, depth+1);
		}
		ret = mem[i][j] = s;
	}

	return ret;
}

int main() {
	int t;
	long long s;

	cin >> t;
	int n, m;
	for (int tc = 1; tc <= t; ++tc) {
		cin >> n >> m;
		for (int i = 0; i <= NMAX; ++i) 
			for (int j = 0; j <= MMAX; ++j) 
				mem[i][j] = -1;
		s = 0;
		for (int i = 1; i <= m; ++i) {
			s += dp(i, n, m, 0);
		}
		printf("Case %d: n = %d, m = %d, # lists = %lld\n", tc, n, m, s);
	}
	return 0;
}
/*迭代版本，时间快很多*/
int main2() {
	int t;
	long long s;

	cin >> t;
	int n, m;
	for (int tc = 1; tc <= t; ++tc) {
		cin >> n >> m;
		for (int i = 0; i <= NMAX; ++i) 
			for (int j = 0; j <= MMAX; ++j) 
				mem[i][j] = 0;
		s = 0;
		for (int i = 1; i <= m; ++i) {
			mem[i][1] = 1;
		}
		for (int j = 2; j <= n; j += 1) {
			for (int i = 1; i <= m; i += 1) {
				for (int k = 2*i; k <= m; k+=1) {					
					mem[i][j] += mem[k][j-1];
				}
			}
		}
		for (int i = 1; i <= m; ++i) {
			s += mem[i][n];
		}
		printf("Case %d: n = %d, m = %d, # lists = %lld\n", tc, n, m, s);
	}
	return 0;
}

/*
刚开始RE，因为数组开太大或者数组越界了
然后WA，因为没有用long long类型
*/