#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 10;
const int sig = 26;

struct node {
	int nxt[sig];
	int fail;
	int cnt;
	int occ;
	node(); 
};
node trie[maxn]; 
node::node() {
	memset(nxt, -1, sizeof(nxt));
	fail = 0;
	cnt = 0;
	occ = 0;
}

int ccnt = 1;
int ans = 0;
vector<int> g[maxn];

void insert(const string &s) {
	int p = 0;
	for (int i = 0; i < s.size(); i++) {
		int idx = s[i] - 'a';
		if (trie[p].nxt[idx] == -1) {
			trie[p].nxt[idx] = ccnt++;
		}
		p = trie[p].nxt[idx];
	}
	trie[p].cnt++;
}

void build() {
	queue<int>q;
	for (int i = 0; i < sig; i++) {
		int v = trie[0].nxt[i];
		if (v != -1) {
			trie[v].fail = 0;
			q.push(v);
		} else {
			trie[0].nxt[i] = 0;
		}
	}
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = 0; i < sig; i++) {
			int v = trie[u].nxt[i];
			if (v != -1) {
				trie[v].fail = trie[trie[u].fail].nxt[i];
				q.push(v);
			} else {
				trie[u].nxt[i] = trie[trie[u].fail].nxt[i];
			}
		}
	}
}

//int query(const string &tx) {
//	int p = 0;
//	int res = 0;
//	for (int i = 0; i < tx.size(); i++) {
//		char c = tx[i];
//		int idx = c - 'a';
//		p = trie[p].nxt[idx];
//		int tmp = p;
//		while (tmp) {
//			res += trie[tmp].cnt;
//			trie[tmp].cnt = 0;
//			tmp = trie[tmp].fail;
//		}
//	}
//	return res;
//}

void query(const string &tx) {
	int p = 0;
	for (int i = 0; i < tx.size(); i++) {
		int idx = tx[i] - 'a';
		p = trie[p].nxt[idx];
		trie[p].occ++;
	}
} 

void dfs(int u) {
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		dfs(v);
		trie[u].occ += trie[v].occ;
	}
	if (trie[u].cnt > 0) {
		if (trie[u].occ > 0)  
			ans += trie[u].cnt;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		insert(s);
	}
	build();
	for (int i = 1; i < ccnt; i++) {
		g[trie[i].fail].push_back(i);
	}
	string txt;
	cin >> txt;
	query(txt);
	dfs(0);
	cout << ans << endl;
	return 0;
}
