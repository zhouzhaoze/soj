/*
问题转化为求两个圆的上交点。简单的几何计算问题，但是要耐心将公示转化为代码；不同公式最好推导的时候用全局唯一的变量名，否则容易混淆难以排错。我是用y=kx+b，-b+-sqrt(b^2-4ac)/2a 的表示法则，b容易出错。
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <cmath>

using namespace std;

#define INF 0x00FFFFFF
#define N 1000010
int p[N];

struct point {
	double x;
	double y;
};

double a[11];
point pa[11][11];

void f(point &p1, point &p2, point& r) {
	double k = (p1.x-p2.x)/(p2.y-p1.y);
	double b = 0.5 * ((p1.x + p2.x)*(p2.x-p1.x)/(p2.y-p1.y) + p1.y + p2.y);

	double aa = 1.0 + k * k;
	double bb = 2 * k * b - 2 * p1.x - 2 * p1.y * k;
	double cc = p1.x * p1.x + b * b - 2 * p1.y * b + p1.y * p1.y - 2 * 2;

	double delta_root = sqrt(bb * bb - 4 * aa * cc);
	double x1 = ( -bb + delta_root) / (2*aa);
	double x2 = ( -bb - delta_root) / (2*aa);
	double y1 = k * x1 + b;
	double y2 = k * x2 + b;

	if (x1 >= p1.x && x1 >= p2.x) {
		r.x = x1;
		r.y = y1;
	} else {
		r.x = x2;
		r.y = y2;
	}
}

int main() {
	int n;

	while (cin >> n) {
		if (!n) 
			break;

		for (int i = 0; i < n; ++i) {
			cin >> a[i];
		}
		sort(a, a+n);
		for (int i = 0; i < n; ++i) {
			pa[0][i].y = a[i];
			pa[0][i].x = 1.0;
		}
		for (int i = 0; i <= n-2; ++i) {
			for (int j = 0; j <= n-2; ++j) {
				f(pa[i][j], pa[i][j+1], pa[i+1][j]);
			}
		}
		printf("%.4f %.4f\n", pa[n-1][0].y, pa[n-1][0].x);
	}
}

