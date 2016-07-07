#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

vector<int> graph[550];
bool visited[550];
#define FOR(i, j, k)for(int i=j;i<k;++i)

int bfs(int idx)
{
    visited[idx] = true;
    queue<int > myq;
    myq.push(idx);
    int total = 1;
    while (not myq.empty()) {
        int idx = myq.front();
        myq.pop();
        for (auto it : graph[idx]) {
            if (visited[it] == false) {
                visited[it] = true;
                myq.push(it);
                total += 1;
            }
        }
    }
    return total;
}

int main()
{
    int n, m, t, k, origin, destination, z;
    cin >> t;
    FOR(z, 0, t) {
        cin >> n >> m;

        FOR(i, 0, n+5) {
            graph[i].clear();
        }

        FOR(i, 0, m) {
            cin >> origin >> destination;
            graph[origin-1].push_back(destination-1);
            graph[destination-1].push_back(origin-1);
        }

        cin >> k;
        vector<int> results;

        memset(visited, 0, sizeof visited);
        FOR(i, 0, n) {
            if (visited[i] == false) {
                int val = bfs(i);
                results.push_back(val);
            }
        }

        sort(results.begin(), results.end(), greater<int>());
        FOR(i, 0, k) {
            printf("%d\n", results[i]);
        }
    }

    return 0;
}
