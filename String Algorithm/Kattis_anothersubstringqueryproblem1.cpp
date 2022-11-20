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
#define MAX 2000050 
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

//Kasai's LCP algorithm (O(n))
void buildLCP(string s, int *sa, int n){
    int i,j,k=0;
    for(i=1; i<=n; i++) Rank[sa[i]]=i;
    for(i=0; i<n; LCP[Rank[i++]]=k)
         for(k?k--:0, j=sa[Rank[i]-1]; s[i+k]==s[j+k]; k++);
    return;
} 
  void print(ll n, string s){
    for( ll i = 1 ; i <= n ; i++){
      ll start = sa[i] ;
      cout << (i) << " " ;
      for( ll j = start ; j < n ; j++) cout << s[j] ;
        cout <<"   " <<  sa[i] ;
        cout << endl ;
    }
    cout << "Suffix Array : " << endl ;
    for( ll i = 1 ; i <= n ; i++) cout << sa[i] << " " ;
      cout << endl ;
    cout << "LCP : " << endl;
    for(ll i = 1 ; i <= n ; i++) cout << LCP[i] << " " ;
      cout << endl ;
  }

ll st[2000000][22] , Jump_LOG[2000000];
struct SPARSE_TABLE{
      ll   nn;
      SPARSE_TABLE(ll _n ){
         nn = _n ;
         for(ll i=2;i<=nn;i++)Jump_LOG[i]=Jump_LOG[i-1]+!(i&(i-1));
         for( ll i = 0 ; i < nn ; i++) st[i][0] = LCP[i+1] ;
          BuildTree() ;
      }
      void BuildTree(){
        for( ll i = 1 ; i <= 21 ; i++){
           for( ll j = 0 ; j + (1ll << i) <= nn ; j++){
            st[j][i] = min(st[j][i - 1] , st[j + (1ll << (i - 1))][i - 1]) ;
           }
        }
      }
      
      ll Query(ll l , ll r){
        ll len , one , two , k ;
        --l , --r ;
        len = (r - l + 1) , k = Jump_LOG[len] ;
        one = st[l][k] , two = st[l + len - (1ll << k)][k] ;
        return min(one , two) ;
      }
};

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
  if(b > j or e < i) return 0 ;
  if(i <= b and j >= e){ 
    return  (lower_bound(Tree[node].begin(), Tree[node].end(), l) - Tree[node].begin());
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
     ll n , id = 0 ;
     
     string s , tem ;
     cin >> s ;
     cin >> n ;
     ll in = s.size();
     s+='#' ;
     id = s.size() ;
     vector <node> v ;
     for( ll i = 0 ; i < n ; i++){
             shuru[i] = id ;
             int k ;
             cin >> tem >> k ;
             v.pb({tem , k , (int)id}) ;
             tem+='#' ;
             s+=tem ;
             id = s.size() ;
     }
     // debug(s) ;
     buildSA(s, sa, s.size()+1, 300) ;
     buildLCP(s, sa, s.size()) ;
     // sa.print() ;
     SPARSE_TABLE tree(s.size()) ;
     build(1, 1, s.size()) ;
     unordered_map < int , int > mp ;
     // print(s.size(), s) ;
     for(int i = 1 ; i <= s.size() ; i++) mp[sa[i]] = i ;

     for(int i = 0; i < n ; i++){
           string ss ;
           int k , pos , sz;
           ss = v[i].a , k = v[i].b , pos = mp[v[i].c] ;
           int l = pos+1 , r = s.size()  ,  lr = pos , rr = pos;
           sz = ss.size() ;
           // debug(pos , v[i].c);
           while(l <= r){
            int mid = (l + r) / 2 ;
            ll val = tree.Query(l, mid) ;
            if(val >= sz){
              l = mid + 1 ;
              rr = mid ;
            }
            else r = mid - 1 ;
           }
           l = 1 , r = pos;
           while(l <= r){
            int mid = (l + r) / 2 ;
            ll val = tree.Query(mid , r) ;
            if(val >= sz){
              r = mid - 1 ;
              lr = mid -  1 ;
            }
            else l = mid +1 ; 
           }
           ll L = lr, R = rr;
            // debug(L, R) ;
           // debug(l1, r1) ;
             ll ans = - 1 ;
             l =  1 , r = s.size() ;
            while(l <= r){
              ll m = (l + r)/ 2 ;
              ll tot = Query(1, 1, s.size(), L, R , m);
              // debug(tot, k , m );
              if(tot >= k) ans = m , r = m - 1 ;
              else l = m + 1 ; 
            }
            if(ans > in) ans = - 1 ;
            cout << ans << '\n' ;
     }
}

// abababcacadddqqqqqq
// 4
// ab 3
// qqqqq 2
// qqqqqq 2
// dddqqqqqq 1
