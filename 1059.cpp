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

struct line {
	double k;
	double b;
};

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

double sinv(point from, point to) {
	return (from.x * to.y - from.y * to.x) / 
		(from.x * from.x + from.y * from.y);
}

void rotate(point &from, double angle, point &to) {
	to.x = from.x * cos(angle) - from.y * sin(angle);
	to.y = from.x * sin(angle) + from.y * cos(angle);
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
			
			point AB;
			AB.x = points[1].x-points[0].x;
			AB.y = points[1].y-points[0].y;
			point AC;
			AC.x = points[2].x-points[0].x;
			AC.y = points[2].y-points[0].y;

		//	cout << sinv(AB, AC) << endl;
			if (sinv(AB, AC) > 0) {
				point tmp = points[1];
				points[1] = points[2];
				points[2] = tmp;
			} 
			/*for (int i = 0; i < 3; ++i) {
				cout << points[i].x << ";" << points[i].y << endl;
			}*/
			point A = points[0];
			point B = points[1];
			point C = points[2];
			point AD, DE, D, E;
			DE = AB;	
			rotate(DE, PI/2, AD);
			//D = A + AD;
			D.x = A.x + AD.x;
			D.y = A.y + AD.y;
			E.x = D.x + DE.x;
			E.y = D.y + DE.y;
			
			point BJ, JH, J, H;
			JH.x = points[2].x - points[1].x;
			JH.y = points[2].y - points[1].y;
			rotate(JH, PI/2, BJ);
			J.x = B.x + BJ.x;
			J.y = B.y + BJ.y;
			H.x = J.x + JH.x;
			H.y = J.y + JH.y;

			point CF, FG, F, G;
			FG.x = points[0].x - points[2].x;
			FG.y = points[0].y - points[2].y;
			rotate(FG, PI/2, CF);
			F.x = C.x + CF.x;
			F.y = C.y + CF.y;
			G.x = F.x + FG.x;
			G.y = F.y + FG.y;

			point L, M, N;
			L.x = (G.x + D.x)/2.0;
			L.y = (G.y + D.y)/2.0;
			M.x = (E.x + J.x)/2.0;
			M.y = (E.y + J.y)/2.0;
			N.x = (H.x + F.x)/2.0;
			N.y = (H.y + F.y)/2.0;

			line LA, NC, MB;
			int flag[3] = {0,0,0};
			if (A.x - L.x == 0) 
				flag[1] = 1;
			LA.k = (A.y - L.y) / (A.x - L.x);
			LA.b = (A.x * L.y - L.x * A.y )/(A.x - L.x);
			
			if (C.x - N.x == 0) 
				flag[0] = 1;
			NC.k = (C.y - N.y) / (C.x - N.x);
			NC.b = (C.x * N.y - N.x * C.y)/(C.x - N.x);
			
			if (B.x - M.x == 0) 
				flag[2] = 1;
			MB.k = (B.y - M.y) / (B.x - M.x);
			MB.b = (B.x * M.y - M.x * B.y)/(B.x - M.x);

			point r;

		/*	cout << LA.k << "->" << LA.b << endl;
			cout << NC.k << "->" << NC.b << endl;
			cout << MB.k << "->" << MB.b << endl;
*/
			if (flag[2]) {
				r.x = -(LA.b-NC.b)/(LA.k-NC.k);
				r.y = LA.k * r.x + LA.b; 
			//	cout << "@" << endl;
			} else if (flag[1]) {
				r.x = -(NC.b-MB.b)/(NC.k-MB.k);
				r.y = NC.k * r.x + NC.b; 
			//	cout << "！" << endl;
			} else {
				r.x = -(LA.b-MB.b)/(LA.k-MB.k);
				r.y = LA.k * r.x + LA.b; 
			//	cout << "）" << endl;
			}

		//	cout << r.x << "," << r.y << endl;
			printf("%.4f %.4f\n", r.x, r.y);
			//r.y = NC.k * r.x + NC.b;
			//cout << r.x << "," << r.y << endl;
			
		//	cout << "a(" << A.x << "," << A.y << ")" << endl;
		//	cout << "b(" << B.x << "," << B.y << ")" << endl;
		//	cout << "c(" << C.x << "," << C.y << ")" << endl;
		////	cout << "d(" << d.x << "," << d.y << ")" << endl;
		////	cout << "e(" << e.x << "," << e.y << ")" << endl;
		////	cout << "f(" << f.x << "," << f.y << ")" << endl;
		////	cout << "g(" << g.x << "," << g.y << ")" << endl;
		////	cout << "h(" << h.x << "," << h.y << ")" << endl;
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