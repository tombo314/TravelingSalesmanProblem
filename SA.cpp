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

mt19937 mt(now());
ll rand(ll n) { return mt()%n; }

double calc(vector<ll> v){
    double cost = 0;
    rep(i, 1, v.size()){
        ll a = v[i-1];
        ll b = v[i];
        cost += sqrt(pow(X[a]-X[b], 2)+pow(Y[a]-Y[b], 2));
    }
    return cost;
}

vector<ll> next_state(vector<ll> v, ll i){
    ll tmp = v[i];
    v[i] = v[i+1];
    v[i+1] = tmp;
    return v;
}

double calc_diff(vector<ll> v, ll i){
    vector<ll> tmp_v = next_state(v, i);
    double cost = 0;
    // 削除
    ll a = v[i-1];
    ll b = v[i];
    ll c = v[i+1];
    ll d = v[i+2];
    cost -= sqrt(pow(X[a]-X[b], 2) + pow(Y[a]-Y[b], 2));
    cost -= sqrt(pow(X[b]-X[c], 2) + pow(Y[b]-Y[c], 2));
    cost -= sqrt(pow(X[c]-X[d], 2) + pow(Y[c]-Y[d], 2));
    // 追加
    a = tmp_v[i-1];
    b = tmp_v[i];
    c = tmp_v[i+1];
    d = tmp_v[i+2];
    cost += sqrt(pow(X[a]-X[b], 2) + pow(Y[a]-Y[b], 2));
    cost += sqrt(pow(X[b]-X[c], 2) + pow(Y[b]-Y[c], 2));
    cost += sqrt(pow(X[c]-X[d], 2) + pow(Y[c]-Y[d], 2));
    return cost;
}

double prob(double new_score, double pre_score, double temp){
    double e = 2.7;
    double ret = pow(e, (pre_score-new_score)/temp);
    return ret;
}

int main(){
    cin >> N;
    X.resize(N);
    Y.resize(N);
    rep(i, 0, N) cin >> X[i] >> Y[i];

    vector<ll> state(N+1);
    rep(i, 0, N) state[i] = i;
    state[N] = 0;
    double score = calc(state);
    double temp = 100;
    double ans = inf;
    const ll max_iter = 3e7;
    ll start = now();

    ll c = 0;
    while (c<=max_iter){
        c++;

        // 2-optで焼きなまし
        ll r = rand(N-3)+1;
        double new_score = score+calc_diff(state, r);
        vector<ll> next = next_state(state, r);
        ans = min(ans, new_score);
        double p = prob(new_score, score, temp)*100;

        // prob()の確率で遷移する
        if (p>rand(100)){
            state = next;
            score = new_score;
        }

        // 温度関数を更新する
        temp *= 0.9999999;

        // n回ごとにdebugする
        if (c%ll(1e6)==0){
            // cout << temp << endl;
            cout << "temp: " << temp << " score: " << ans << endl;
        }
    }

    // 答えを出力する
    cout << setprecision(20) << ans << endl;
    // 時間を計測
    cout << now()-start << " ms" << endl;
}