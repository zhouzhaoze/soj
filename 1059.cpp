#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <cmath>

using namespace std;

struct point {
	double x;
	double y;
};

point operator + (point a, point b) {
	point r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	return r;
}

point operator - (point a, point b) {
	point r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	return r;
}

point middle(point a, point b) {
	point r;
	r.x = (a.x + b.x) / 2.0;
	r.y = (a.y + b.y) / 2.0;
	return r;
}

const double eps = 1e-6;
double fix(double x) {
	if (fabs(x - 0.0) < eps) {
		return 0;
	}
	return x;
}

point withoutslope(double x, point p1, point p2) {
	point o;
	double k = (p1.y-p2.y)/(p1.x-p2.x);
	double b = p1.y - p1.x * k;
	o.x = x;
	o.y = k*x+b;
	return o;
}

point withslope(point p1, point p2, point p3, point p4) {
	point o;double k1=(p1.y-p2.y)/(p1.x-p2.x);
	double b1=p1.y-p1.x*k1;
	double k2=(p3.y-p4.y)/(p3.x-p4.x);
	double b2=p3.y-p3.x*k2;
	o.x=(b1-b2)/(k2-k1);
	o.y=k1*o.x+b1;
	return o;


}
point intersection_point(point a, point b, point a2, point b2) {

	point r;
	if (fabs(a.x - b.x) < eps) {
		r = withoutslope(a.x, a2, b2);
	} else if(fabs(a2.x-b2.x) < eps) {
		r = withoutslope(a2.x, a, b);
	} else {
		r = withslope(a, b, a2, b2);
	}
	return r;
}


struct line {
	double k;
	double b;
};

double sinv(point from, point to) {
	return (from.x * to.y - from.y * to.x) / 
		(from.x * from.x + from.y * from.y);
}

point rotate(point &from, double angle) {
	point to;
	to.x = from.x * cos(angle) - from.y * sin(angle);
	to.y = from.x * sin(angle) + from.y * cos(angle);
	return to;
}

double const PI = acos(double(-1));

int main() {
	int n;
	while (cin >> n) {
		if (!n) 
			break;
		point points[3];

		for (int i = 0; i < n; ++i) {
			for (int j=0; j < 3; ++j) 				
				cin >> points[j].x >> points[j].y;
			
			point AB = points[1] - points[0];
			point AC = points[2] - points[0];

		//	cout << sinv(AB, AC) << endl;
			if (sinv(AB, AC) > 0) {
				point tmp = points[1];
				points[1] = points[2];
				points[2] = tmp;
			} 

			point A = points[0];
			point B = points[1];
			point C = points[2];

			point AD, DE, D, E;
			DE = AB;	
			AD = rotate(AB, PI/2);
			D = A + AD;
			E = D + DE;
			
			point BJ, JH, J, H;
			JH = C-B;
			BJ = rotate(JH, PI/2);
			J = B+BJ;
			H = J + JH;

			point CF, FG, F, G;
			FG = A - C;
			CF = rotate(FG, PI/2);
			F = C + CF;
			G = F + FG;

			point L, M, N;
			L = middle(G, D);
			M = middle(E, J);
			N = middle(H, F);

			point r = intersection_point(L, A, M, B);

			printf("%.4f %.4f\n", fix(r.x), fix(r.y));
			
		//	cout << "a(" << A.x << "," << A.y << ")" << endl;
		//	cout << "b(" << B.x << "," << B.y << ")" << endl;
		//	cout << "c(" << C.x << "," << C.y << ")" << endl;
		//	cout << "d(" << D.x << "," << D.y << ")" << endl;
		//	cout << "e(" << E.x << "," << E.y << ")" << endl;
		//	cout << "f(" << F.x << "," << F.y << ")" << endl;
		//	cout << "g(" << G.x << "," << G.y << ")" << endl;
		//	cout << "h(" << H.x << "," << H.y << ")" << endl;
		//////	cout << "(" << i.x << "," << i.y << ")" << endl;
		////	cout << "j(" << j.x << "," << j.y << ")" << endl;
		//////	cout << "(" << k.x << "," << k.y << ")" << endl;
		//	cout << "l(" << L.x << "," << L.y << ")" << endl;
		//	cout << "m(" << M.x << "," << M.y << ")" << endl;
		//	cout << "n(" << N.x << "," << N.y << ")" << endl;
		}		
	}
}

/*
样例能通过，但是还是WA
*/