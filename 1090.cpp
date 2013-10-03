#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <cmath>

using namespace std;

int a[500][500];
//short w[500*249/2];

struct edge {
	int u;
	int v;
	int w;
} edges[500*500/2];

int cmp(edge a, edge b) {
	return a.w < b.w;
}

int p[501];

int find(int x) { 
	return p[x] == x ? x: p[x]= find(p[x]); 
}

int main() {
	int t;
//	cin >> t;
	scanf("%d", &t);
	while(t--) {
		int n;
		scanf("%d", &n);
		//vector<edge> ve;
		//vector<int> vr;
		int ans = 0;
		for (int i = 0; i < n; ++i) 
			p[i] = i;

		for (int i = 0; i < n; ++i) 
			for(int j = 0; j < n; ++j) {
				scanf("%d", &a[i][j]);
			}

		int m = 0;

		for (int u = 0; u < n; ++u) 
			for (int v = u + 1; v < n; ++v) {
				int w = a[u][v];
				edges[m].u = u;
				edges[m].v = v;
				edges[m].w = w;
				m++;
			}
		sort(edges, edges+m, cmp);
		int mavW = -1;
		for (int i = 0; i < m; ++i) {
			int uto = find(edges[i].u);
			int vto = find(edges[i].v);
			if (uto != vto) { 
				p[vto] = uto; 
				mavW = max(mavW, edges[i].w);
			}
		}	
		printf("%d\n", mavW);
		//cout << mavW << endl;
	}
}

/*
POJ 2485 Accepted but SOJ presentation error

*/