#include<bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
#define ll      long long
#define pb      push_back
#define TT ll time;        cin >> time; while(time--)
#define FastIo  ios_base::sync_with_stdio(false);cin.tie(NULL) ;
const ll int INF = 5e18 , nmax = 2501 , block = 350 , N = 1e6 +10;
#ifndef ONLINE_JUDGE
#include "algodebug.h"
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif
#define MAX_N 2000100                        
int RA[MAX_N], tempRA[MAX_N] , RANK[MAX_N];                 
int SA[MAX_N], tempSA[MAX_N], LCP[MAX_N];                 
int c[MAX_N];
struct SUffix_Array{
      string T ;
      int n ;
    SUffix_Array(string s){
           T = s ;
           n = s.size() ;
           BuildSA() ;
           Get_Lcp() ;

    }                                  
void countingSort(int k) {                      
            int i, sum, maxi = max(300, n);                
            memset(c, 0, sizeof c);  
            for (i = 0; i < n; i++)   
            c[i + k < n ? RA[i + k] : 0]++;
            for (i = sum = 0; i < maxi; i++){
              int t = c[i]; c[i] = sum; sum += t; 
            }
            for (i = 0; i < n; i++)  
              tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
            for (i = 0; i < n; i++)     
            SA[i] = tempSA[i];
}
void BuildSA() {    
        int i, k, r;
        for (i = 0; i < n; i++) RA[i] = T[i];          
        for (i = 0; i < n; i++) SA[i] = i;           
        for (k = 1; k < n; k <<= 1) {                 
        countingSort(k);                              
        countingSort(0);                               
        tempRA[SA[0]] = r = 0;                        
        for (i = 1; i < n; i++)                       
        tempRA[SA[i]] =                              
        (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
        for (i = 0; i < n; i++)                        
        RA[i] = tempRA[i];
        if (RA[SA[n-1]] == n-1) break;                 
} }
 // kasai ALgorithm for LCP Array
void Get_Lcp(){  // 0 indexed based
  for(ll i = 0 ; i < n ; i++) RANK[SA[i]] = i ;
  ll k = 0 ;
  for( ll i = 0 ; i < n ; i++){
      ll ind1 = RANK[i] , ind2 = ind1 - 1 ;
      if(ind1 != 0){
         while(T[i+k] == T[SA[ind2]+k]) k++ ;
         LCP[RANK[i]] = k ;if(k > 0) k-- ;
      }}
      return;
}
  void print(){
    for( ll i = 0 ; i < n ; i++){
      ll start = SA[i] ;
      for( ll j = start ; j < n ; j++) cout << T[j] ;
        cout << endl ;
    }
    cout << "Suffix Array : " << endl ;
    for( ll i = 0 ; i < n ; i++) cout << SA[i] << " " ;
      cout << endl ;
    cout << "LCP : " << endl;
    for(ll i = 0 ; i < n ; i++) cout << LCP[i] << " " ;
      cout << endl ;
  }

};
ll st[200000][22] , Jump_LOG[200000];
struct SPARSE_TABLE{
      ll   nn;
      SPARSE_TABLE(ll _n ){
         nn = _n ;
         for(ll i=2;i<=nn;i++)Jump_LOG[i]=Jump_LOG[i-1]+!(i&(i-1));
         for( ll i = 0 ; i < nn ; i++) st[i][0] = LCP[i] ;
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

vector < ll > Tree[N] ;
ll shuru[200005], siz[200005] ;
void build(ll node , ll b , ll e){
  if(b == e){
    Tree[node].push_back(SA[b-1]) ;
    return ;
  }
  ll mid = (b + e) / 2 ;
  build(node*2, b , mid) ;
  build(node*2+1, mid +1 , e) ;
  merge(Tree[node*2].begin(), Tree[node*2].end(), Tree[node*2+1].begin(), Tree[node*2+1].end(), back_inserter(Tree[node])) ;
}

ll Query(ll node , ll b, ll e, ll i , ll j , ll l , ll r){
  if(b > j or e < i) return 0 ;
  if(i <= b and j >= e){ 
    debug(Tree[node]) ;
    return upper_bound(Tree[node].begin(), Tree[node].end(), r) - lower_bound(Tree[node].begin(), Tree[node].end(), l) ;
  }
  ll mid = (b + e)/2 ;
  return Query(node*2, b , mid , i , j , l , r) + Query(node*2 +1 , mid +1 , e , i , j , l , r) ;
}

int main()
{
     ll n , id = 0 ;
     cin >> n ;
     string s , tem ;
     
     for( ll i = 0 ; i < n ; i++){
             shuru[i] = id ;
             cin >> tem ;
             siz[i] = (ll)tem.size() ;
             tem+='#' ;
             s+=tem ;
             id = s.size() ;
     }
     SUffix_Array sa(s) ;
     SPARSE_TABLE tree(s.size()) ;
     build(1, 1, s.size()) ;
    //  for( ll i = 0 ; i < n ; i++) cout << shuru[i] << " " ;
    //   cout << endl ;
    // for( ll i = 0 ; i < n ; i++) cout << siz[i] << " " ;
    //   cout << endl ;
     
     // sa.print() ;
     // for( ll i = 0 ; i < n ; i++){
     //  cout << shuru[i] << " " ;
     // }
     // cout << endl ;
     // for( ll i = 0 ; i < n ; i++){
     //  cout << siz[i] << " " ;
     // }
     // cout << endl ;
     ll q ;
     cin >> q ;
     for( ll i = 0 ; i < q ; i++){
      ll x, l , r, y ;
      cin >> x >> l >> r >> y ;
      x--, l--, r--, y-- ;
      ll b = shuru[x] + l ;
      ll be = 2 , en = RANK[b]+1 , pos1 = RANK[b]+1 , pos2 = RANK[b]+1 ;
      ll len = r - l + 1 ;
      debug(be , en , b) ;
      while(be <= en){
        ll mid = (be + en) / 2 ;
        if(tree.Query(mid , RANK[b]+1) >= len){
          pos1 = mid -1;
          en = mid - 1 ;
        }
        else be = mid + 1 ;
      }
      debug(s.size()) ;
      be = RANK[b]+2 , en = s.size() ;
      debug(be , en) ;
      while(be <= en){
        ll mid = (be + en) / 2 ;
        debug(tree.Query(be, mid) ,be , mid , LCP[mid - 1]) ;
        if(tree.Query(RANK[b]+2 , mid) >= len){
            pos2 = mid ;
            be = mid + 1 ;
        }
        else en = mid - 1 ;
      }
      // if(pos1 == pos2){
      //   cout << "0" <<  endl ;
      //   continue ;
      // }
      debug(b ,RANK[b] , be, pos1 , pos2 ,shuru[y], (shuru[y] + siz[y])) ;
      ll ans = Query(1, 1, s.size() , pos1, pos2 , shuru[y] , (shuru[y]+siz[y]-1)) ;
     cout << ans << endl ;
     }

}
