#include<bits/stdc++.h>
#define ll long long 
#define pb push_back
#define all(n) n.begin(),n.end() 
#define vec vector<int>
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define vp(it,arr)  for(auto it:arr){cout<<it<<;}
#define LOOP(i,a,b) for(int i=a;i<b;i++)
using namespace std;
struct node {
    unordered_map<int,int>nbrs;
};
void add_vertex(int a,unordered_map<int,node>&arru){
      if(arru.count(a)){
          return;
      }else{
          node n1;
      arru.insert({a,n1});
     }
}

void add_an_edge(int a,int b,int weight,unordered_map<int,node>&arru){
      if(arru.count(a)&&arru.count(b)||arru[a].nbrs.count(b)||arru[b].nbrs.count(a)){
          return ;
      }else{
           arru[a].nbrs.insert({b,weight});
           arru[b].nbrs.insert({a,weight});
      }
}



int main(){
unordered_map<int,node>arru;





return 0;
}