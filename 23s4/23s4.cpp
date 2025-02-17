// #include<bits/stdc++.h>
// using namespace std;

// typedef long long ll;

// class Road {
//     public:
//         int cost;
//         int len;
//         int u;
//         int v;
//         int index;
//         bool removed;
    
//     Road(int v1, int v2, int l, int c, int i):u(v1), v(v2), len(l), cost(c), index(i), removed(false) {}

//     Road():u(-1), v(-1), len(-1), cost(-1), index(-1), removed(false) {}
// };

// const int N = 2001;
// long long MAX = __LONG_LONG_MAX__;
// vector<Road> roadsVec;
// vector<Road> roadsArr[N];
// vector<Road> roadsVec2;

// ll dist[N][N];
// ll dist2[N][N];

// void djiktras(int src) {
//     queue<Road> q;
//     dist[src][src] = 0;

//     Road srcRoad = Road(src, src, 0, 0, 0);
//     q.push(srcRoad);

//     while(!q.empty()) {
//         Road top = q.front();
//         q.pop();

//         for(Road child:roadsArr[top.v]) {
//             ll newLen = dist[src][top.v]+child.len;
//             if(newLen < dist[src][child.v]) {
//                 dist[src][child.v]=newLen;
//                 q.push(child);
//             }
//         }
//     }
// }

// void djiktras2(int src, int ignore) {
//     queue<Road> q;
//     dist2[src][src] = 0;

//     Road srcRoad = Road(src, src, 0, 0, 0);
//     q.push(srcRoad);

//     while(!q.empty()) {
//         Road top = q.front();
//         q.pop();

//         for(Road child:roadsArr[top.v]) {
//             if(roadsVec[child.index-1].removed || child.index==ignore) {
//                 continue;
//             }

//             ll newLen = dist2[src][top.v]+child.len;
//             if(newLen < dist2[src][child.v]) {
//                 dist2[src][child.v]=newLen;
//                 q.push(child);
//             }
//         }
//     }
// }

// bool roadsComp(Road a, Road b) {
//     return (a.cost > b.cost);
// }

// ll cost = 0;

// int main() {
//     #ifndef ONLINE_JUDGE:
//         freopen("input.txt", "r", stdin);
//         freopen("output.txt", "w", stdout);
//     #endif

//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     for (int i = 0; i < N; i++) {
//         fill(dist[i], dist[i]+N, MAX);
//         fill(dist2[i], dist2[i]+N, MAX);
//     }
    
//     int intrs, roads;
//     cin >> intrs >> roads;

//     for (int i = 1; i <= roads; i++) {
//         int v1, v2, l, c;
//         cin >> v1 >> v2 >> l >> c;
//         Road road1 = Road(v1, v2, l, c, i);
//         Road road2 = Road(v2, v1, l, c, i);
//         Road roadEdge = Road(v1, v2, l, c, i);

//         roadsArr[v1].push_back(road1);
//         roadsArr[v2].push_back(road2);
//         roadsVec.push_back(roadEdge);
//         roadsVec2.push_back(roadEdge);
//         cost = cost+c;
//     }

//     for (int i = 1; i <= intrs; i++) {
//         djiktras(i);    
//     }

//     sort(roadsVec2.begin(), roadsVec2.end(), roadsComp);
//     for (int i = 0; i < roadsVec2.size(); i++) {
//         djiktras2(roadsVec2[i].u, roadsVec2[i].index);

//         bool shouldRemove = true;

//         for (int j = 1; j <= intrs; j++) {
//             if(dist[roadsVec2[i].u][j] < dist2[roadsVec2[i].u][j]) {
//                 shouldRemove=false;
//                 break;
//             }
//         }

//         if(shouldRemove) {
//             roadsVec2[i].removed=true;
//             roadsVec[roadsVec2[i].index-1].removed=true;
//             cost = cost-roadsVec2[i].cost;
//         }
        

//         for (int k = 0; k < N; k++) {
//             dist2[roadsVec2[i].u][k] = MAX;
//         }
//     }

//     cout << cost;
    
    
//     return 0;
// }

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

class Road {
    public:
        int cost;
        ll len;
        int u;
        int v;
        int index;
        bool removed;
    
    Road(int v1, int v2, ll l, int c, int i):u(v1), v(v2), len(l), cost(c), index(i), removed(false) {}

    Road():u(-1), v(-1), len(-1), cost(-1), index(-1), removed(false) {}
};

const int N = 2001;
long long MAX = __LONG_LONG_MAX__;
vector<Road> roadsVec;
vector<Road> roadsArr[N];
vector<Road> roadsVec2;

ll dist[N][N];
ll dist2[N][N];
bool visited[N];

class Comp {
    public:
    bool operator()(Road a, Road b) {
        return (a.len > b.len);
    }
};

void djiktras(int src) {
    priority_queue<Road, vector<Road>, Comp> q;
    dist[src][src] = 0;

    Road srcRoad = Road(src, src, 0, 0, 0);
    q.push(srcRoad);

    while(!q.empty()) {
        Road top = q.top();
        q.pop();

        if(visited[top.v]) {
            continue;
        }

        ll newLen = top.len;
        if(newLen < dist[src][top.v]) {
            dist[src][top.v]=newLen;
        }

        visited[top.v] = true;

        for(Road child:roadsArr[top.v]) {
            Road newRoad = Road(top.v, child.v, (top.len+child.len), child.cost, child.index);
            q.push(newRoad);
        }
    }
}

bool djiktras2(int src, int ignore) {
    bool shouldRemove=true;
    priority_queue<Road, vector<Road>, Comp> q;
    dist2[src][src] = 0;

    Road srcRoad = Road(src, src, 0, 0, 0);
    q.push(srcRoad);

    while(!q.empty()) {
        Road top = q.top();
        q.pop();

        if(visited[top.v]) {
            continue;
        }

        ll newLen = top.len;
        if(newLen < dist2[src][top.v]) {
            dist2[src][top.v]=newLen;
        }

        if(dist2[src][top.v] > dist[src][top.v]) {
            shouldRemove = false;
            break;
        }
        
        visited[top.v] = true;

        for(Road child:roadsArr[top.v]) {

            if(roadsVec[child.index-1].removed || child.index==ignore) {
                continue;
            }

            Road newRoad = Road(top.v, child.v, (top.len+child.len), child.cost, child.index);
            q.push(newRoad);
        }
    }

    return shouldRemove;
}

bool roadsComp(Road a, Road b) {
    return (a.cost > b.cost);
}

ll cost = 0;

int main() {
    fill(visited, visited+N, false);

    #ifndef ONLINE_JUDGE:
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i < N; i++) {
        fill(dist[i], dist[i]+N, MAX);
        fill(dist2[i], dist2[i]+N, MAX);
    }
    
    int intrs, roads;
    cin >> intrs >> roads;

    for (int i = 1; i <= roads; i++) {
        int v1, v2, l, c;
        cin >> v1 >> v2 >> l >> c;
        Road road1 = Road(v1, v2, l, c, i);
        Road road2 = Road(v2, v1, l, c, i);
        Road roadEdge = Road(v1, v2, l, c, i);

        roadsArr[v1].push_back(road1);
        roadsArr[v2].push_back(road2);
        roadsVec.push_back(roadEdge);
        roadsVec2.push_back(roadEdge);
        cost = cost+c;
    }

    for (int i = 1; i <= intrs; i++) {
        djiktras(i);
        fill(visited, visited+N, false);
    }

    sort(roadsVec2.begin(), roadsVec2.end(), roadsComp);
    for (int i = 0; i < roadsVec2.size(); i++) {
        djiktras2(roadsVec2[i].u, roadsVec2[i].index);
        // if() {
        //     // cost = cost-roadsVec2[i].cost;
        //     // roadsVec2[i].removed = true;
        //     // roadsVec[roadsVec2[i].index-1].removed = true;
        // }

        bool shouldRemove = true;

        for (int k = 1; k < N; k++) {
            if(dist2[roadsVec2[i].u][k] > dist[roadsVec2[i].u][k]) {
                shouldRemove = false;
                break;
            }
        }

        if(shouldRemove) {
            cost = cost-roadsVec2[i].cost;
            roadsVec2[i].removed = true;
            roadsVec[roadsVec2[i].index-1].removed = true;
        }

        for (int k = 0; k < N; k++) {
            dist2[roadsVec2[i].u][k] = MAX;
        }
        fill(visited, visited+N, false);
    }

    cout << cost;
    
    
    return 0;
}