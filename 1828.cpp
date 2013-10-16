// Problem#: 1828
// Submission#: 2279374
// The source code is licensed under Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
// URI: http://creativecommons.org/licenses/by-nc-sa/3.0/
// All Copyright reserved by Informatic Lab of Sun Yat-sen University
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
#define For(i, n) for (int i=0; i < n; ++i)
#define N 510
#define M 510
int s1[N];
int s2[M];
int mem[N][M];
int dist[N][M];

int dis(int i, int j) {
    return abs(s1[i]-s2[j]);
}

int dp(int i, int j, int depth) {   
    if (mem[i][j] != -1) 
        return mem[i][j];

    int &ret = mem[i][j];

    if (i == j) {
        if (i == 0) 
            ret = dis(0, 0);
        else
            ret = dis(i, i) + dp(i-1, i-1, depth+1);
    } else {
        ret = min(dis(i, j) + dp(i-1, j-1, depth+1), dp(i, j-1, depth+1) );
    }   
    return ret;
}

int main() {
    int t, n, m;
    //int i, j;
    cin >> t;
    while(t--) {                
        cin >> n >> m;
        memset(mem, -1, sizeof(mem));
        for (int i = 0; i < n; ++i) 
            cin >> s1[i];
        for (int i = 0; i < m; ++i) 
            cin >> s2[i];
        sort(s1, s1+n);
        sort(s2, s2+m);
        cout << dp(n-1, m-1, 0) << endl;
    }
}                                 