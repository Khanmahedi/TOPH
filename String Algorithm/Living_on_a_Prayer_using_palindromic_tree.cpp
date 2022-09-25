#include<bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
#define ll      long long int
#define pb      push_back
#define TT ll time;        cin >> time; while(time--)
#define FastIo  ios_base::sync_with_stdio(false);cin.tie(NULL) ;
const ll  INF = 5e18 , nmax = 2501 , block = 350 , N = 1e6 +10;
#ifndef ONLINE_JUDGE
#include "algodebug.h"
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

const ll Maxn = 1e4+10 ;   
ll last, sz, tree[Maxn][27], link[Maxn], len[Maxn];
ll cnt[Maxn] , num[Maxn];
ll Start[Maxn], End[Maxn];
struct Palindromic_Tree{
   string s ;
   ll t , idx , n;

   Palindromic_Tree(string &ss){
        s = ss ;
        n = s.size() ;
   }
   inline void extend(ll p){
      while(s[p - len[t] - 1] != s[p]) t = link[t] ;    // find first suitable suffix 
      ll x = link[t] ;
      while(s[p - len[x] - 1] != s[p]) x = link[x] ;    // find second suitable suffix for linking
      ll c = s[p] - 'A' ;                               // charge according to the requrements
      if(!tree[t][c]){
        tree[t][c] = ++idx ;
        len[idx] = len[t] + 2 ;
        link[idx] = len[idx] == 1? 2 : tree[x][c] ;
        num[idx] = 1 + num[link[idx]] ; 
        Start[idx] = p - len[idx] + 1 ;
        End[idx] = p ;                
      }
      t = tree[t][c] , ++cnt[t] ;
   }

   void init(){
     memset(tree , 0 , sizeof tree) ;
     memset(link, 0 , sizeof link) ;
     memset(cnt , 0 , sizeof cnt) ;
     len[1] = -1, len[2] = 0 ;
     link[1] = 1 , link[2] = 1 ;
     t = idx = 2 ;

   }
   void count(){
    for( ll i = idx ; i >= 0 ; i--) cnt[link[i]]+=cnt[i] ;
   }

 };

int main()
{
   ios_base::sync_with_stdio(0);
   cin.tie(0);

   ll tt ;
   cin >> tt ;
   while(tt--){
    string s ;

    ll k ;
    cin >> s >> k ;
    Palindromic_Tree pt(s) ;
    pt.init() ;

    for( ll i = 0 ; i < s.size() ; i++) pt.extend(i) ;  
    
    pt.count() ;

    vector < tuple < ll , ll , ll > > v ;
    for( ll i = 3 ; i <= pt.idx ; i++) v.push_back(make_tuple(Start[i] , End[i] ,cnt[i])) ;
    
      sort(v.begin(), v.end(), [&s](tuple<ll, ll, ll> &a, tuple<ll, ll, ll> &b) {
            return s.substr(get<0>(a), get<1>(a) - get<0>(a) + 1) < s.substr(get<0>(b), get<1>(b) - get<0>(b) + 1);
        });

      ll sum = 0 , ok = 0 ;
       for (ll i = 0 ; i < v.size() ; i++) {
        ll x = get<0>(v[i]) , y = get<1>(v[i]) , z = get<2>(v[i]) ;
            if (sum + z >= k) {
                ok = 1;
                string s1 = s.substr(x, y - x + 1) ;
                cout << s1 << endl ;
                break;
            }
            sum += z;
        }

        if(ok == 0){
          cout << "-1" << endl ;
        }
   
   }

  }
   
