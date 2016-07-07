#include <iostream>
#include <stack>
#include <vector>
#include <cstring>

using namespace std;

#define FOR(i, j, k)for(int i=j;i<k;++i)

stack<int> mys;
bool visited[1010];
vector<int> graph[1010];

int dfs(int idx)
{
    visited[idx] = true;
    for (auto it : graph[idx]) {
        if (visited[it] == false)
            dfs(it);
    }
    mys.push(idx);
}

void kojajaru(int idx)
{
    visited[idx] = true;
    for (auto it : graph[idx]) {
        if (visited[it] == false)
            kojajaru(it);
    }
}

int main()
{
    int t, n, m, origin, destination;
    cin >> t;
    FOR(z, 0, t) {
        cin >> n >> m;
        FOR(i, 0, n+3) {
            graph[i].clear();
        }

        FOR(i, 0, m) {
            cin >> origin >> destination;
            graph[origin-1].push_back(destination-1);
        }

        memset(visited, false, sizeof visited);
        FOR(i, 0, n) {
            if (visited[i] == false)
                dfs(i);
        }

        int scc = 0;
        memset(visited, false, sizeof visited);
        while (not mys.empty()) {
            int idx = mys.top();
            if (visited[idx] == false) {
                kojajaru(idx);
                scc++;
            }
            mys.pop();
        }
        printf("%d\n", n-scc);
    }
    return 0;
}
