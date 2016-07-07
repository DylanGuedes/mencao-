#include <iostream>
#include <vector>
#include <cstring>

#define FOR(i, j,k)for(int i=j;i<k;++i)

using namespace std;

vector<int> graph[60];
int color[60];
bool visited[60];
int pos[60][60];

bool is_friend_of(int idx, int idx2)
{
    for (auto it : graph[idx]) {
        if (it == idx2)
            return true;
    }
    return false;
}

int main()
{
    int n, m, g, origin, destination;
    while (cin >> n >> m >> g) {
        FOR(i, 0, 2*n+2) {
            graph[i].clear();
            color[i] = 0;
        }
        FOR(i, 0, g) {
            color[i] = 1;
        }
        FOR(i, g, 2*n) {
            color[i] = 2;
        }

        FOR(i, 0, n) {
            FOR(j, 0, n) {
                cin >> pos[i][j];
                pos[i][j] -= 1;
            }
        }

        FOR(i, 0, m) {
            cin >> origin >> destination;
            graph[origin-1].push_back(destination-1);
            graph[destination-1].push_back(origin-1);
        }

        bool impossible = false;
        FOR(i, 0, n) {
            FOR(j, 0, n) {
                if (impossible)
                    break;
                vector<pair<int, int> > myv {make_pair(i+1, j), make_pair(i-1, j), make_pair(i, j+1), make_pair(i, j-1)};
                for (auto it : myv) {
                    if (it.first < 0 || it.second < 0 || it.first >= n || it.second >= n)
                        continue;
                    if (color[pos[i][j]] == color[ pos[it.first][it.second] ]) {
                        // printf("pos[%d][%d] = %d, pos[%d][%d] = %d\n", i, j, pos[i][j], it.second, it.first, pos[it.second][it.first]);
                        impossible = true;
                        break;
                    }
                    if (is_friend_of(pos[i][j], pos[it.first][it.second])) {
                        impossible = true;
                        break;
                    }
                }
            }
        }

        if (impossible)
            printf("NAO\n");
        else
            printf("SIM\n");
    }
    return 0;
}
