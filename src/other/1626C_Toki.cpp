#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll>pll;
bool cmp(pll&a,pll&b){
    if(a.first==b.first)return a.second<b.second;
    return a.first<b.first;
}
void Tokisaki(){
    //思路：注意到施法是很多1至n的等差数列，考虑区间合并
    ll n;
    cin>>n;
    vector<ll>k(n+10),h(n+10);
    vector<pll>a;//记录合并区间
    ll end=0;
    for(ll i=1;i<=n;i++)cin>>k[i];
    for(ll i=1;i<=n;i++)cin>>h[i];
    for(int i=1;i<=n;i++){
        a.push_back({k[i]-h[i]+1,k[i]});//储存原始区间
    }
    sort(a.begin(),a.end(),cmp);
    vector<pll>ans;
    pll res={-1,-1};
    for(auto i:a){
        if(i.first>res.second){
            if(res.first!=-1)ans.push_back({res.first,res.second});//装入区间
            res=i;//更新维护的区间
        }
        else{
            res.second=i.second;//更新右端点
        }
    }
    if(res.first!=-1)ans.push_back({res.first,res.second});//装入区间
    for(auto i:ans){
        ll cnt=i.second-i.first+1;
        end+=(1+cnt)*cnt/2;
    }
    cout<<end<<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int _;
    cin>>_;
    while(_--)Tokisaki();
}