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

struct segment {
	point p1;
	point p2;
	double k;
	double b;
	int isKExist;
} segs[10000];

const double eps = 1e-8;

int equals(double a, double b) {
	return fabs(a - b) < eps;
}

int cmp(segment a, segment b) {
	if (a.isKExist && b.isKExist) {
		if (!equals(a.k, b.k) ){
			return a.k < b.k;
		} else {
			if (!equals(a.b, b.b)) {
				return a.b < b.b;
			} else {
				if (!equals(a.p1.x, b.p1.x)) {
					return a.p1.x < b.p1.x;
				} else if(!equals(a.p2.x,  b.p2.x)) {
					return a.p2.x < b.p1.x;
				} else {
					return 0;
				}
			}
		}
	} else if (a.isKExist || b.isKExist) {
		return a.isKExist > b.isKExist;
	} else {
		if (!equals(a.p1.x, b.p1.x)) {
			return a.p1.x < b.p1.x;
		} else if (!equals(a.p1.y, b.p1.y)) {
			return a.p1.y < b.p1.y;
		}
		else if (!equals(a.p2.y, b.p2.y)) {
			return a.p2.y < b.p2.y;
		} else {
			return 0;
		}
	//	return 0;
	}
}

int counter(segment *start, segment *end) {
	int ret = end-start;
	segment *cur = start;
	int isKExist = start->isKExist;

	if (isKExist) {
		double l = cur->p1.x;
		double r = cur->p2.x;
		while (cur+1 != end) {
			cur += 1;
			//cout <<"DEBUG"<< r << ":"<<cur->p1.x << endl;
			if (cur->p1.x <= r) {
				ret--;
				r = max(r, cur->p2.x);				
			}		
		}
	}
	else {
		double l = cur->p1.y;
		double r = cur->p2.y;
		while (cur+1 != end) {
			cur += 1;
			if (cur->p1.y <= r) {
				ret--;
				r = max(r, cur->p2.y);				
			}			
		}
	}
	return ret;
}

void getKB(point p1, point p2, double &k, double &b) {
	k = (p2.y-p1.y)/(p2.x-p1.x);
	b = p2.y - k * p2.x;
}


int main() {
	int n;
	while(cin >> n) {
		if (!n) 
			break;

		for (int i = 0; i < n; ++i) {
			cin >> segs[i].p1.x >> segs[i].p1.y;
			cin >> segs[i].p2.x >> segs[i].p2.y;

			if (segs[i].p1.x > segs[i].p2.x) {
				double tmp = segs[i].p1.x;
				segs[i].p1.x = segs[i].p2.x;
				segs[i].p2.x = tmp;
				tmp = segs[i].p1.y;
				segs[i].p1.y = segs[i].p2.y;
				segs[i].p2.y = tmp;
			}

			double k, b;

			if (!equals(segs[i].p1.x, segs[i].p2.x)) {
				getKB(segs[i].p1, segs[i].p2, k, b);
				segs[i].k = k;
				segs[i].b = b;
				segs[i].isKExist = 1;
			} else {
				segs[i].isKExist = 0;
			}
		}

		sort(segs, segs+n, cmp);

		//for (int i =0; i < n; ++i) {
		//	cout << "("<<segs[i].k << ","<< segs[i].b <<")"<< endl;
		//}
		//cout << endl;
		int s, t;

		vector<int> v;
		for (int i = 0; i < n-1; ++i) {
			if (segs[i].isKExist && !segs[i+1].isKExist) {
				v.push_back(i);
			//	cout << "#1" << endl;
			} else if(!segs[i].isKExist && !segs[i+1].isKExist) {
				if (!equals(segs[i].p1.x, segs[i+1].p1.x)) {
					v.push_back(i);
				//	cout << "#2" << endl;
				}
			}
			else {
				if (!(equals(segs[i].k, segs[i+1].k) && equals(segs[i].b, segs[i+1].b))) {
					v.push_back(i);
				//cout << "#3" << endl;
				}
			}
		}
		int c = 0;
		v.push_back(n-1);
	/*	cout << v.size() << endl;
		for (int i = 0; i < v.size(); ++i) {
			cout << v[i] << "->";
		}*/
		//cout << endl;
		s = 0;
			for (int i = 0;  i < v.size(); ++i) {	
			//	cout << "<" << s << "," << v[i] + 1 << ">" << endl;
				int tmp =  counter(segs+s, segs+v[i]+1);
				//cout << "<" << s << "," << v[i] + 1 << ">" << tmp << endl;
				c+= tmp;
				s = v[i]+1;
			}
		cout << c << endl;	
		//cout << endl;
	}
}