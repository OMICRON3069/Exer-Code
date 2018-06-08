//
// Created by Omicron3069 on 6/7/2018.
//

#include<cmath>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include <iomanip>

using namespace std;
int Hash[15];

struct node {
    int f, h, g; // f：当前代价  h：曼哈顿距离  g:迭代次数
    int x, y; //0 的位置
    char map[3][3];

    friend bool operator<(const node &a, const node &b) {
        if (a.f == b.f) return a.g < b.g;
        return a.f > b.f;
    }
};

node start;
bool vis[500000];
int to[4][2] = {0, -1, 0, 1, -1, 0, 1, 0};
int pos[][2] = {{0, 0}, //1
                {0, 1}, //2
                {0, 2}, //3
                {1, 2}, //4
                {2, 2}, //5
                {2, 1}, //6
                {2, 0}, //7
                {1, 0}, //8
                {1, 1}};//0
//目标位置

int target[3][3] = {{0, 1, 2},
                    {7, 8, 3},
                    {6, 5, 4}};//“1 - 0” 映射为 “0 - 8”


//判断是否有解
int check() {
    int i, j, k;
    int s[20];
    int cnt = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            s[target[i][j]] = start.map[i][j];
            if (s[target[i][j]] == 'x') continue;
            for (k = target[i][j] - 1; k >= 0; k--) {
                if (s[k] == 'x') continue;
                if (s[k] > s[target[i][j]]) cnt++;
            }
        }
    }
    if (cnt % 2) return 0;
    return 1;
}

void display(node asd) {
    cout << "***************************\n";
    for (auto &i : asd.map) {
        for (auto &j : i) {
            cout << setw(2) << j;
        }
        cout << "\n";
    }
    cout << "Current Step: " << asd.g << "  Current Weight:" << asd.f << "\n";
    cout << "***************************\n\n\n\n\n";
}

//康托展开
int solve(node a) {
    int i, j, k;
    int s[20];
    int ans = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            s[target[i][j]] = a.map[i][j];
            int cnt = 0;
            for (k = target[i][j] - 1; k >= 0; k--) {
                if (s[k] > s[target[i][j]]) cnt++;
            }
            ans = ans + Hash[target[i][j]] * cnt;
        }
    }
    return ans;
}

//计算h值,即曼哈顿距离
int get_h(node a) {
    int i, j;
    int ans = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (a.map[i][j] == 'x') continue;
            int k = a.map[i][j] - '1';
            ans += abs(pos[k][0] - i) + abs(pos[k][1] - j);
        }
    }
    return ans;
}

//启发式搜索
int bfs() {
    memset(vis, 0, sizeof(vis));
    priority_queue<node> Q;
    start.g = 0;
    start.h = get_h(start);
    start.f = start.h;
    vis[solve(start)] = true;
    if (solve(start) == 0) return 0;
    Q.push(start);
    node next;
    while (!Q.empty()) {
        node a = Q.top();
        Q.pop();
        int k_s = solve(a);
        vis[k_s] = true;
        for (auto &i : to) {
            next = a;
            next.x += i[0];
            next.y += i[1];
            if (next.x < 0 || next.y < 0 || next.x > 2 || next.y > 2) continue;
            next.map[a.x][a.y] = a.map[next.x][next.y];
            next.map[next.x][next.y] = 'x';
            next.g += 1;
            next.h = get_h(next);
            next.f = next.g + next.h;
            int k_n = solve(next);
            if (k_n == 0) {
                display(next);
                return next.g;
            }
            if (vis[k_n]) continue;
            Q.push(next);
            display(next);
        }
    }
}

int main() {
    Hash[0] = 1;
    for (int i = 1; i <= 9; i++) Hash[i] = Hash[i - 1] * i;
    int t;
    cin >> t;
    for (int k = 0; k < t; k++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                char a;
                cin >> a;
                start.map[i][j] = a;
                if (a == '0') {
                    start.map[i][j] = 'x';
                    start.x = i;
                    start.y = j;
                }
            }
        }
        if (!check()) {
            cout << "No Solution!\n";
        }
        else {
            int step = bfs();
            cout << "Steps: " << step << "\n";
        }
    }
}