#include<bits/stdc++.h>
using namespace std;

class Road {
    public:
    int u, v, dist, cost;

    Road(int r1, int r2, int length, int price) {
        u = r1;
        v = r2;
        dist=length;
        cost=price;
    }
};

const int N = 10000;
const int MAX = INT_MAX;

vector<Road> roads[N];
const int VEC = 1000;
int dist[VEC][VEC];
int visited[VEC];

struct PQComparator {
    bool operator()(Road a,Road b) {
        return (a.dist > b.dist);
    }
};

void djiktras(int start) {
    priority_queue<Road, vector<Road>, PQComparator> q;

    Road startRoad = Road(start, start, 0, 0);
    q.push(startRoad);
    dist[startRoad.u][startRoad.v] = 0;

    while(!q.empty()) {
        Road top = q.top();
        q.pop();

        if(visited[top.v]) {
            continue;
        }

        visited[top.v] = true;
   
        int leastDist = min(dist[startRoad.u][top.v], top.dist);
        dist[startRoad.u][top.v] = leastDist;
        // for(int i=0; i<4; i++) {
        //     for(int j=0; j<4; j++) {
        //         cout << dist[i][j] << " ";
        //     }
        //     cout << endl;
        // }

        for(Road child:roads[top.v]) {
            q.push(Road(child.u, child.v, dist[startRoad.u][top.v]+child.dist, child.cost));
        }
    }
}

int main() {

#ifndef ONLINE_JUDGE:
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    for(int i=0; i<VEC; i++) {
        fill(dist[i], (dist[i]+VEC), MAX);
    }

    int n, e;
    cin>>n>>e;

    for(int i=0; i<e; i++) {
        int u,v,d,c;
        cin >> u >> v >> d;
        c=0;

        roads[u-1].push_back(Road(u-1,v-1,d,c));
        roads[v-1].push_back(Road(u-1,v-1,d,c));
    }

    djiktras(0);
    
    for(int i=0;i<n; i++) {
        if(dist[0][i] == MAX) {
            cout << -1 << endl;
        } else {
            cout << dist[0][i] << endl;
        }
    }

    return 0;
}