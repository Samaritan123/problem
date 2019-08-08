#include <cstdio>
#include <iostream>
#include <vector>
#include <ctime>
#define N 110000
using namespace std;

int n, k, p, ans, deep[N], v[N], f[N][20];
vector<int> g[N];


void dfs(int x, int d, int fa) {
  deep[x] = d;
  f[x][0] = fa;
  for (int i = 1; f[x][i - 1]; i ++) f[x][i] = f[f[x][i - 1]][i - 1];
	for(auto t: g[x]) dfs(t, d + 1, x);
}

int lca(int x, int y) {
  if (deep[x] < deep[y]) swap(x, y);
  int k = deep[x] - deep[y];
  for (int i = 0; i < 20; i ++) {
    if ((1 << i) & k) x = f[x][i];
  }
  if (x == y) return x;
  for (int i = 19; i >= 0; i --) {
    if (f[x][i] == f[y][i]) continue;
    x = f[x][i]; 
    y = f[y][i];
  }
  return f[x][0];
}


int main() {
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i ++) scanf("%d", &v[i]);
  for (int i = 2; i <= n; i ++) {
  	scanf("%d", &p);
  	g[p].push_back(i);
  }
  dfs(1, 0, 0);
  for (int i = 1; i < n; i ++)
  	for (int j = i + 1; j <= n; j ++) {
  		int t = lca(i, j);
  		if (t != i && t != j && deep[i] + deep[j] -  2 * deep[t] <= k)
  			if (2 * v[t] == v[i] + v[j]) ans ++;
  	}
  printf("%d\n", ans);
  return 0;
}

