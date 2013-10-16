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
#include <cstring>

using namespace std;
#include "cstdio"
#include "cstdlib"
#include "string"
#include "vector"
#include "iostream"

#define N 202

short flags[N];
short depths[N];
bool isOutput[N];

inline int is_start_tag(const char *s, int len) {
	int ret = -1;
	
	if (!(s[0] == '<')) 
		return -1;
	if (s[1] == '/')
		return -1;
	
	for (int i = 1; i < len; ++i) {
		if (s[i] == '<')
			return -1;
		if (s[i] == '>')
			return i+1;
	}	

	return -1;
}

inline int is_end_tag(const char *s, int len) {	
	if (!(s[0] == '<')) 
		return -1;
	if (!(s[1] == '/'))
		return -1;	
	for (int i = 2; i < len; ++i) {
		if (s[i] == '<')
			return -1;
		if (s[i] == '>')
			return i+1;
	}	
	return -1;
}
int f(char *s, int beg, int end)
{
	/* code */
	//int n;
	
	int len = strlen(s);

	memset(flags, 0, sizeof(flags));	
	memset(isOutput, 0, sizeof(isOutput));

	int depth = 0;

	for (int i = 0; i < len; ++i) {		
		//cout << i << endl;
		depths[i] = depth;
		int e = is_start_tag(s+i, len-i);
		if (e!=-1) {
			depth += 1;
			for (int j = i; j < i+e; ++j) {
				flags[j] = 1;
				depths[j] = depth;
			}
			i += e-1;
			continue;
		} 
		e = is_end_tag(s+i, len-i);	
		if (e!=-1) {
			for (int j = i; j < i+e; ++j) {
				flags[j] = 2;
				depths[j] = depth;
			}			
			depth -= 1;
			i += e-1;
			continue;
		}			
	}

	for (int  i =beg; i < end; ++i) {
		isOutput[i] = 1;
	}

	depth = depths[beg];
	for (int i = beg-1; i >= 0; --i) {
		if (depths[i] <= depth) {
			depth = depths[i];
			if (flags[i] != 0) {				
				isOutput[i] = 1;
			}
		}
	}
	depth = depths[end-1];
	for (int i = end; i < len; ++i) {
		if (depths[i] <= depth) {
			depth = depths[i];
			if (flags[i] != 0) {				
				isOutput[i] = 1;
			}
		}
	}
	for (int  i =0; i < len; ++i) {
		//cout << isOutput[i];
		if (isOutput[i])
			cout << s[i];
	}
	cout << endl;	
	return 0;
}

int main() {
	char s[500];
	int beg, end;
	while (scanf("%d%d", &beg, &end) && beg != -1 && end != -1) {
		char c=0;
		int i = 0;
		getchar();

		gets(s);
		f(s, beg, end);
	}
	return 0;
}