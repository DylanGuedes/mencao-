#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#define FOR(i, j, k)for(int i=j;i<k;++i)

using namespace std;

bool visited[10020];
bool mendigo[10020];
vector<int> graph[10020];
int dist[10020];

int bfs(int origin)
{
    visited[origin] = 1;
    if (mendigo[origin])
        return 0;
    queue<pair<int, int> > myq;
    myq.push(make_pair(0, origin));

    while (not myq.empty()) {
        int idx = myq.front().second;
        int val = myq.front().first;
        visited[idx] = true;
        myq.pop();
        if (mendigo[idx]) {
            return val;
        }

        for (auto it : graph[idx]) {
            if (visited[it] == false) {
                myq.push(make_pair(val+1, it));
                visited[it] = true;
            }
        }
    }
    return 0xffffff;
}

int main()
{
    int b, r, h, place, origin, destination;
    cin >> b >> r >> h;

    memset(mendigo, false, sizeof mendigo);

    FOR(i, 0, h) {
        scanf("%d", &place);
        mendigo[place-1] = true;
    }

    FOR(i, 0, r) {
        scanf("%d", &origin);
        scanf("%d", &destination);
        graph[origin-1].push_back(destination-1);
        graph[destination-1].push_back(origin-1);
    }

    memset(dist, -1, sizeof dist);
    int p;
    scanf("%d", &p);
    FOR(i, 0, p) {
        scanf("%d", &place);
        memset(visited, false, sizeof visited);
        if (dist[place-1] != -1) {
            if (dist[place-1] == 0xffffff)
                printf("-1\n");
            else
                printf("%d\n", dist[place-1]);
        } else {
            long long int mydist = bfs(place-1);
            dist[place-1] = mydist;
            if (mydist == 0xffffff) {
                printf("-1\n");
            } else {
                printf("%d\n", mydist);
            }
        }
    }
    return 0;
}
