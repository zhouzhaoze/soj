#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>

using namespace std;

#define INF 0x00FFFFFF
#define N 1000010
int p[N];


inline int find(int x)
{
    if(x!=p[x])
    {
        p[x]=find(p[x]);//zhe li yao shi num[x]
    }
    return p[x];
}

int main() {
    int n;
    int j;
    int i;
    int ito, jto;
    while(cin >> n) {
        for (i = 1; i <= n; ++i) {
            p[i] = i;
        }
        int ans = n;
        for (i = 1; i <= n; ++i) {
            cin >> j;
            ito = find(i);
            jto = find(j);
            if (ito != jto) {
                p[ito] = jto;
                ans -= 1;
            }
        }
    //    set<int> s;
    //    for (int i = 1; i <= n; ++i) {
    //        s.insert(p[i]);
    //    }
    //    cout << s.size() << endl;
        cout << ans << endl;
    //  break;
    }
}            

/*
这里不知道为什么用set来对连通子图进行计数就不行
*/