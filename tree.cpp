#include <cstdio>
#include <iostream>
#include <vector>
#include <ctime>
#define N 110000
using namespace std;

int n, x, y;
vector<int> g[N];

struct treap {

	struct node {
		node* left,right;
		int value, fix, size;
		node() {}
		node(int _value) {
			value = _value
			fix = rand();
			size = 1;
		}
	};

	node* root;

	void left_rotate(node *a) {
		node *b = a -> right;
		a -> right = b -> left;
		update(a);
		b -> left = a;
		update(b);
		a = b;
	}

	void right_rotate(node *a) {
		node *b = a -> left; 
		a -> left = b -> right;
		update(a);
		b -> right = a;
		update(b);
		a = b;
	}

	void update(node *p) {
		p -> size = p -> left -> size + p -> right -> size + 1;
	}

	int find(node *p, int k) {
		if (!p) return 0;
		if (p -> value <= k) {
			return p -> left -> size + 1 + find(p -> right, k);
		} else {
			return find(p -> right, k);
		}
	}

	void insert(node *&p, int value) {
		if (!p) {
			p = new node(value);    
		} else if (value <= p -> value) {
			insert(p -> left, value);
			if (p -> left -> fix < p -> fix) {
				right_rotate(p);
			} 
		} else {
			insert(p -> right, value);
			if (p -> right -> fix < p -> fix) {
				left_rotate(p);
			}
		}
		update(p);
	}

	void erase(node *&p, int value) {
	  if (p -> value == value) {
	  	if (!p -> right && !p -> left) {
	  		node *t = p;
	  		if (!p -> right) {
	  			p = p -> left;
	  		} else {
	  			p = p -> right;
	  		}
	  		delete t;
	  	} else {
	  		if (p -> left -> fix < p -> right -> fix) {
	  			right_rotate(p);
	  			erase(p -> right, value);
	  		} else {
	  		  left_rotate(p);
	  		  erase(p -> left, value);
	  		}
	  	}
	  } else if (value < p -> value) {
	    erase(p -> left, value);
	  } else {
	    erase(p -> right, value);
	  }
	  update(p);
	}

}T[N];

void dfs(int x, int d) {
	size[x] = 1;
	deep[x] = d;
	for(auto t: g[x]) {             
		dfs(t, d + 1);
		size[x] += size[t];
		if (size[t] > size[son[x]]) son[x] = t;
	}
}

void add(int x)
{
	T[v[x]].insert(T[v[x]].root, deep[x]);
	for(auto t: g[x]) add(t);
}

void clear(int x)
{
	T[v[x]].erase(T[v[x]].root, deep[x]);
	for(auto t: g[x]) clear(t);
}


int calc(int x, int w)
{
	int h = 2 * v[w] - v[x];
	if (h >= 0) {
	  ans += T[h].find(T[h].root, k + 2 * deep[w] - deep[x]);
	}
	for(auto t: g[x]) calc(t, w);
}


void dsu(int x, int keep) {
	for(int t: g[x]) {
		if (t == son[x]) continue;  
		dsu(t, 0);
	}
	if (son[x]) dsu(son[x], 1);
	for(int t: g[x]) {
		if (t == son[x]) continue;
    calc(t, x);
    add(t);
  }
  if (!keep) { 
  	clear(x);
  } else {
  	T[v[x]].insert(T[v[x]].root, deep[x]);
  }
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
  dfs(1, 0);
  dsu(1, 1);
  return 0;
}

