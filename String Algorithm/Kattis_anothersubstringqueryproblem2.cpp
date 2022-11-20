#include<bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
#define ll      long long
#define pb      push_back
#define TT ll time;        cin >> time; while(time--)
#define FastIo  ios_base::sync_with_stdio(false);cin.tie(NULL) ;
const ll int INF = 5e18 , nmax = 2501 , block = 350 , N = 1e6 +10;
// #ifndef ONLINE_JUDGE
// #include "algodebug.h"
// #define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
// #else
// #define debug(x...)
// #endif
#define MAX 200005 
int wa[MAX],wb[MAX],wv[MAX],Ws[MAX] ;
int cmp(int *r, int a, int b, int l){return r[a] == r[b] && r[a+l] == r[b+l];}

int sa[MAX],Rank[MAX],LCP[MAX];

void buildSA(string s, int* sa, int n, int m){
  int i,j,p,*x=wa,*y=wb,*t;
  for(i=0; i<m; i++) Ws[i] = 0;
  for(i=0; i<n; i++) Ws[x[i]=s[i]]++;
  for(i=1; i<m; i++) Ws[i]+=Ws[i-1];
  for(i=n-1; i>=0; i--) sa[--Ws[x[i]]]=i;
  for(j=1,p=1; p<n; j<<=1,m=p){
    for(p=0,i=n-j; i<n; i++) y[p++]=i;
    for(i=0; i<n; i++) if(sa[i]>=j) y[p++]=sa[i]-j;
    for(i=0; i<n; i++) wv[i]=x[y[i]];
    for(i=0; i<m; i++) Ws[i]=0;
    for(i=0; i<n; i++) Ws[wv[i]]++;
    for(i=1; i<m; i++) Ws[i]+=Ws[i-1];
    for(i=n-1; i>=0; i--) sa[--Ws[wv[i]]]=y[i];
    for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1; i<n; i++)
           x[sa[i]]=cmp(y,sa[i-1],sa[i],j)? p-1 : p++;
  }
}




vector < ll > Tree[4*N] ;
ll shuru[200005], siz[200005] ;
void build(ll node , ll b , ll e){
  if(b == e){
    Tree[node].push_back(sa[b]) ;
    return ;
  }
  ll mid = (b + e) / 2 ;
  build(node*2, b , mid) ;
  build(node*2+1, mid +1 , e) ;
  merge(Tree[node*2].begin(), Tree[node*2].end(), Tree[node*2+1].begin(), Tree[node*2+1].end(), back_inserter(Tree[node])) ;
}

ll Query(ll node , ll b, ll e, ll i , ll j , ll l ){
  // debug(b, e, i, j) ;
  if(b > j or e < i) return 0 ;
  if(i <= b and j >= e){ 
    ll ind = lower_bound(Tree[node].begin(), Tree[node].end(), l) - Tree[node].begin() ;
    // debug(Tree[node] , ind , l, node) ;
    return ind;
  }
  ll mid = (b + e)/2 ;
  return Query(node*2, b , mid , i , j , l ) + Query(node*2 +1 , mid +1 , e , i , j , l) ;
}
struct node{
    string a ;
    int b , c ;
};
int main()
{
     ll q , id = 0 , k;
     
     string s , tem ;
     cin >> s ;
     int n = s.size() ;
     cin >> q ;
     int sA[n+1]={} ;
     // debug(s) ;
     buildSA(s, sa, n+1, 330);

    

     build(1, 1, s.size()) ;
     for(int i = 0; i < q ; i++){
          cin >> tem >> k ;
          int len = tem.size(), L = -1, R = -1, l= 1, r = n ;
          while(l <= r)
          {
              int m = (l + r) / 2 ;
              string tt = s.substr(sa[m], len);
              if(tt == tem)
              {
                L = m;
                r = m-1 ;
              }
              else if(tem < tt) r = m - 1 ;
              else l = m + 1 ;
          }
          l = 1 , r = n ;
          while(l <= r){
            int m = (l + r) / 2 ;
            string tt = s.substr(sa[m], len);
            if(tt == tem){
              R = m ;
              l = m + 1 ;
            }
            else if(tem < tt) r = m - 1 ;
            else l = m + 1 ;
          }
          // debug(L, R );
          if(L == -1 && R == -1) cout << "-1" << '\n' ;
          else if((R - L + 1) < k) cout << "-1" << '\n';
          else{
            l =1 , r = n ;
            ll ans = - 1 ;
            while(l <= r){
              ll m = (l + r)/ 2 ;
              ll tot = Query(1, 1, n, L, R , m);
              // debug(tot, k , m );
              if(tot >= k) ans = m , r = m - 1 ;
              else l = m + 1 ; 
            }
            cout << ans << '\n' ;
          }
     }
}

// abababcacadddqqqqqq
// 4
// ab 3
// qqqqq 2
// qqqqqq 2
// dddqqqqqq 
