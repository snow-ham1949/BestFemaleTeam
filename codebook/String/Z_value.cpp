int z[MAXN];
void getz(string s){
    int l=0;
    for(int i = 0; i < sz(s); i++){
        if(l+z[l]>i) z[i]=min(z[i-l],l+z[l]-i);
        while(i+z[i]<sz(s)&&s[z[i]]==s[i+z[i]]) z[i]++;
        if(i+z[i]>l+z[l]) l=i;
    }
}