#include <iostream>

using namespace std;

#define FOR(i,j,k)for(int i=j;i<k;++i)

int dist[310][310];

int main()
{
    int v, e, origin, destination, weight, l, m, f;
    long long int distluana = 0, distmarcos = 0;

    cin >> v >> e;
    cin >> l >> m >> f;
    l -= 1;
    m -= 1;
    f -= 1;

    FOR(i, 0, v+3) {
        FOR(j, 0, v+3) {
            dist[i][j] = 0xffffff;
        }
    }

    FOR(i, 0, e) {
        cin >> origin >> destination >> weight;
        dist[origin-1][destination-1] = weight;
    }

    FOR(k, 0, v) {
        FOR(i, 0, v) {
            FOR(j, 0, v) {
                dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
            }
        }
    }

    distluana = dist[f][l] + dist[l][m] + dist[m][f];
    distmarcos = dist[f][m] + dist[m][l] + dist[l][f];
    if (distluana < 0xffffff || distmarcos < 0xffffff) {
        if (distmarcos < distluana) {
            std::cout << "Marcos " << distmarcos << std::endl;
        } else {
            std::cout << "Luana " << distluana << std::endl;
        }
    } else {
        printf("-1\n");
    }
    return 0;
}
