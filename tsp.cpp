#include <bits/stdc++.h>
#include <chrono>
#include <random>
using namespace std;
typedef long long ll;
#define rep(i, a, b) for (ll i=a; i<b; i++)
#define rrep(i, a, b) for (ll i=a; i>b; i--)
#define vrep(x, v) for (auto x: v)
#define srt(v) sort(v.begin(), v.end())
#define rsrt(v) sort(v.begin(), v.end(), greater<ll>())
#define copy(v1, v2) copy(v1.begin(), v1.end(), v2.begin())
#define vmax(v) *max_element(v.begin(), v.end())
#define vmin(v) *min_element(v.begin(), v.end())
#define vsum(v) accumulate(v.begin(), v.end(), ll(0))
#define rev(v) reverse(v.begin(), v.end())
#define vconcat(v1, v2) v1.insert(v1.end(), v2.begin(), v2.end())
#define now() chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count()
#define choice(in, out, n) sample(in.begin(), in.end(), back_inserter(out), n, mt)
#define bpq(v, T) priority_queue<T> v
#define spq(v, T) priority_queue<T, vector<T>, greater<T>> v
#define pb push_back
#define inf ll(1e18)

ll N;
vector<ll> X;
vector<ll> Y;
double ans_score = inf;
vector<ll> ans_v;

mt19937 mt(now());
ll rand(ll n) { return mt()%n; }

double calc_all(vector<ll> v){
    double cost = 0;
    rep(i, 1, v.size()){
        cost += sqrt(pow(X[v[i-1]]-X[v[i]], 2)+pow(Y[v[i-1]]-Y[v[i]], 2));
    }
    return cost;
}

double calc_diff(vector<ll> mn_v, vector<ll> tmp_v, ll i, double pre_score){
    double cost = pre_score;
    // 削除
    cost -= sqrt(pow(X[mn_v[i-1]]   - X[mn_v[i]],   2)  + pow(Y[mn_v[i-1]]  - Y[mn_v[i]],   2));
    cost -= sqrt(pow(X[mn_v[i]]     - X[mn_v[i+1]], 2)  + pow(Y[mn_v[i]]    - Y[mn_v[i+1]], 2));
    cost -= sqrt(pow(X[mn_v[i+1]]   - X[mn_v[i+2]], 2)  + pow(Y[mn_v[i+1]]  - Y[mn_v[i+2]], 2));
    // 追加
    cost += sqrt(pow(X[tmp_v[i-1]]  - X[tmp_v[i]],   2) + pow(Y[tmp_v[i-1]] - Y[tmp_v[i]],   2));
    cost += sqrt(pow(X[tmp_v[i]]    - X[tmp_v[i+1]], 2) + pow(Y[tmp_v[i]]   - Y[tmp_v[i+1]], 2));
    cost += sqrt(pow(X[tmp_v[i+1]]  - X[tmp_v[i+2]], 2) + pow(Y[tmp_v[i+1]] - Y[tmp_v[i+2]], 2));
    return cost;
}

vector<ll> kick(vector<ll> v){
    ll choice_num = 950;
    if (v.size()<choice_num+2) { return v; }

    vector<ll> indexes;
    rep(i, 1, v.size()-1) indexes.pb(i);

    vector<ll> r;
    choice(indexes, r, choice_num);

    ll first = v[r[0]];
    rep(i, 0, choice_num-1){
        v[r[i]] = v[r[i+1]];
    }
    v[r[choice_num-1]] = first;

    return v;
}

vector<ll> next_state(vector<ll> v){
    double mn = calc_all(v);
    double init_mn = mn;
    vector<ll> mn_v = v;

    rep(i, 1, v.size()-2){
        vector<ll> tmp_v = mn_v;
        ll tmp = tmp_v[i];
        tmp_v[i] = tmp_v[i+1];
        tmp_v[i+1] = tmp;
        double cost = calc_diff(mn_v, tmp_v, i, mn);
        if (cost<mn){
            mn = cost;
            mn_v = tmp_v;
        }
    }

    if (mn==init_mn){
        mn_v = kick(v);
    }

    return mn_v;
}

int main(){
    cin >> N;
    X.resize(N+1);
    Y.resize(N+1);
    ans_v.resize(N+1);
    rep(i, 0, N) cin >> X[i] >> Y[i];

    vector<ll> state(N+1);
    rep(i, 0, N) state[i] = i;
    state[N] = 0;
    X[N] = X[0];
    Y[N] = Y[0];
    ll start = now();
    const ll max_iter = 1e7;

    ll c = 0;
    while (c<=max_iter){
        c++;
        vector<ll> next = next_state(state);
        double cost = calc_all(next);
        if (cost<ans_score){
            ans_score = cost;
        }
        state = next;

        // debug
        if (c%200==0){
            cout << ans_score << endl;
        }
    }

    cout << setprecision(8) << ans_score << endl;
}