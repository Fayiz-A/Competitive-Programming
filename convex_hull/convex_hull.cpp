#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Route {
    public:
    int u, v;
    ll len;
    int wear;
    int currentWear;

    Route(int v1, int v2, ll l, int w, int cw):u(v1), v(v2), len(l), wear(w), currentWear(cw) {}
};

const ll MAX = __LONG_LONG_MAX__;

const int N = 2001;
const int ROADS_C = 10001;
ll dist[N][N];
ll wearArr[N][N];
vector<Route> routesArr[ROADS_C];
bool visited[N];

class RouteComp {
    public:
    bool operator()(Route r1, Route r2) {
        return (r1.len > r2.len);
    }
};

int djiktras(int start, int end, int wear) {
    int time = 0;
    // Route roadStart = routesArr[start];
    // Route roadEnd = routesArr[end];

    dist[start][start] = 0;
    priority_queue<Route, vector<Route>, RouteComp> q;
    q.push(Route(start, start, 0, 0, wear));

    while(!q.empty()) {
        Route top = q.top();
        q.pop();

        if(top.len == MAX) {
            //ran out of all routes
            time = -1;
            break;
        }

        if(top.v == end) {
            dist[start][end] = top.len;
            time = dist[start][end];
            break;
        }

        if(visited[top.v]) {
            if(top.currentWear > wearArr[start][top.v]) {
                //do nothing
            } else {
                continue;
            }
        }

        if(top.len<dist[start][top.v] && (top.currentWear> 0)) {
            dist[start][top.v] = top.len;
            wearArr[start][top.v] = top.currentWear;
        }

        visited[top.v] = true;

        for(Route child:routesArr[top.v]) {
            int newWear = top.currentWear-child.wear;//ll
            ll newLen = top.len+child.len;//ll
            if(newWear <= 0) {
                newLen = MAX;
            }
            // if(top.currentWear == -1) {
            //     newWear = wear;
            //     //first
            // }
            Route newRoad = Route(child.u, child.v, newLen, child.wear, newWear);
            q.push(newRoad);
        }
    }

    return time;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    fill(visited, visited+N, false);

    for (int i = 0; i < N; i++) {
        fill(dist[i], dist[i]+N, MAX);
        fill(wearArr[i], wearArr[i]+N, MAX);
    }
    
    int hull_len; 
    int islands; 
    int routes;

    cin >> hull_len >> islands >> routes;

    for (int i = 1; i <= routes; i++) {
        int v1, v2, l, w;
        cin >> v1 >> v2 >> l >> w;
        Route route1 = Route(v1, v2, l, w, hull_len);
        Route route2 = Route(v2, v1, l, w, hull_len);
        routesArr[v1].push_back(route1);
        routesArr[v2].push_back(route2);
    }

    int start, end;
    cin >> start >> end;
    int time = djiktras(start, end, hull_len);
    
    cout << time;

    return 0;
}