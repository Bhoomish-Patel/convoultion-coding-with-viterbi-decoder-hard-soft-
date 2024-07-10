#include<bits/stdc++.h>
using namespace std;
vector<int>decoding(int kc,vector<int>generation_polynomials,vector<int>inp){
    int ns=(1<<(kc-1));
    int n=generation_polynomials.size();
    vector<vector<int>>mtr((inp.size()/n)+1,vector<int>(ns,1e9));
    vector<vector<pair<int,int>>>previous_states((inp.size()/n+1),vector<pair<int,int>>(ns,{1e9,1e9}));
    int idx=0;
    for(int t=0;t<(inp.size()/n);t++){
        for(int st=0;st<ns;st++){
            if(t==0 && st==0){
                mtr[t][st]=0;
            }
            for(int input_bits=0;input_bits<2;input_bits++){
                int curstate=st;
                int next_state=(curstate>>1)|(input_bits<<(kc-2));
                int hamming_distance=0;
                for(int i=0;i<n;i++){
                    int output=0;
                    int poly=generation_polynomials[i];
                    int regvalue=(curstate|input_bits<<(kc-1));
                    for(int k=0;k<kc;k++){
                        output^=((((poly)>>k)&1)&(regvalue>>(k)&1)); 
                    }
                    if(output!=inp[idx+i])hamming_distance++;
                }
                int a=mtr[t+1][next_state];
                int b=mtr[t][curstate];
                if(a>b+hamming_distance){
                    mtr[t+1][next_state]=b+hamming_distance;
                    previous_states[t+1][next_state]={curstate,input_bits};
                }
            }
        }
        idx+=n;
    }
    vector<int>ans;
    pair<int,int>temp=previous_states[inp.size()/n][0];
    ans.push_back(temp.second);
    int cur=inp.size()/n-1;
    while(cur>0){
        temp=previous_states[cur][temp.first];
        ans.push_back(temp.second);
        cur--;
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
vector<int>encoding(int kc,vector<int>generation_polynomials,vector<int>inp){
    int n=generation_polynomials.size();
    vector<int>ans;
    int regval=0;
    for(int i=0;i<inp.size();i++){
        int curbit=inp[i];
        regval=((regval>>1)|(curbit<<(kc-1)));
        for(int j=0;j<n;j++){
            int cur_poly=generation_polynomials[j];
            int output=0;
            for(int k=0;k<kc;k++){
                output^=((((cur_poly)>>k)&1)&(regval>>(k)&1)); 
            }
            ans.push_back(output);
        }
    }
    return ans;
}
int main(){
    vector<int>inp={1,1,0,1,0,0};
    vector<int>ans;
    int kc=3;
    int n=2;
    vector<int>generation_polynomials={5,7};
    ans=encoding(kc,generation_polynomials,inp);
    for(auto i:ans)cout<<i<<" ";
    cout<<endl;
    vector<int>decoded_message=decoding(kc,generation_polynomials,ans);
    for(auto i:decoded_message)cout<<i<<" ";
    cout<<endl;
    return 0;
}