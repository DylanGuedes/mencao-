#include <iostream>
#include <vector>
#include <cstring>
#include <set>

using namespace std;

vector<int> graph[1010];
bool visited[1010];
int lowtime[1010];
int times[1010];
int father[1010];
set<int> scc;

#define FOR(i, j, k) for(int i=j;i<k;++i)

void tarjan(int idx, int val)
{
    lowtime[idx] = val;
    times[idx] = val;
    visited[idx] = true;
    int children = 0;

    for (auto it : graph[idx]) {
        if (father[idx] == it)
            continue;
        if (visited[it] == false) {
            children++;
            father[it] = idx;
            tarjan(it, val+1);
            lowtime[idx] = min(lowtime[idx], lowtime[it]);
            if (lowtime[it] >= times[idx] && father[idx] != idx) {
                scc.insert(idx);
            }
            if (father[idx] == idx && children > 1) {
                scc.insert(idx);
            }
        } else {
            lowtime[idx] = min(lowtime[idx], times[it]);
        }
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
            graph[destination-1].push_back(origin-1);
        }

        scc.clear();
        FOR(i, 0, n+4) {
            father[i] = i;
        }
        scc.clear();
        memset(visited, 0, sizeof visited);
        FOR(i, 0, n) {
            if (visited[i] == false)
                tarjan(i, 0);
        }
        printf("%d\n", n - scc.size());
    }

    return 0;
}
