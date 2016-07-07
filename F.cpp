#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <vector>

using namespace std;
#define FOR(i, j, k) for(int i=j;i<k;++i)

struct edge
{
    int x;
    int y;
    int z;
};

int father[110];
int ranks[110];

bool myfunc(edge e1, edge e2)
{
    return e1.z < e2.z;
}

int union_find(int x)
{
    if (father[x] == x)
        return x;
    else
        return union_find(father[x]);
}

void make_union(int x, int y)
{
    int rootx = union_find(x);
    int rooty = union_find(y);
    if (ranks[rootx] >= ranks[rooty]) {
        father[rooty] = rootx;
        ranks[rootx]++;
    } else {
        father[rootx] = rooty;
        ranks[rooty]++;
    }
}

vector<edge> edges;

int main()
{
    int n, m;
    cin >> n >> m;
    edge e;
    FOR(i, 0, m) {
        cin >> e.x;
        cin >> e.y;
        cin >> e.z;
        e.x -= 1;
        e.y -= 1;
        edges.push_back(e);
    }

    FOR(i, 0, n+2) {
        father[i] = i;
    }
    sort(edges.begin(), edges.end(), myfunc);
    memset(ranks, 0, sizeof ranks);
    set<int> myset;
    int minpath = 0;
    FOR(i, 0, m) {
        if (union_find(edges[i].x) != union_find(edges[i].y)) {
            make_union(edges[i].x, edges[i].y);
            myset.insert(i);
            minpath += edges[i].z;
        }
    }

    int secondmst = 0xffffff;
    bool possible = false;

    FOR(j, 0, m) {
        if (myset.count(j) == 0)
            continue;

        FOR(i, 0, n+2) {
            father[i] = i;
        }

        memset(ranks, 0, sizeof ranks);

        int path = 0;
        FOR(i, 0, m) {
            if (i == j) {
                continue;
            }

            if (union_find(edges[i].x) != union_find(edges[i].y)) {
                make_union(edges[i].x, edges[i].y);
                path += edges[i].z;
                // printf("fazendo uniao entre %d e %d\n", edges[i].x, edges[i].y);
            }
        }

        bool impossible = false;
        FOR(i, 0, n) {
            FOR(k, i+1, n) {
                if (union_find(father[i]) != union_find(father[k])) {
                    impossible = true;
                    break;
                }
            }
        }
        if (not impossible) {
            if (path > minpath) {
                possible = true;
                secondmst = min(secondmst, path);
            }
        }
    }

    if (possible) {
        printf("%d\n", secondmst);
    } else {
        printf("-1\n");
    }
    return 0;
}
