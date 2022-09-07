int pi[MAXN];

void Prefix(string &Pattern)
{
  int len = Pattern.size()-1;
  int j = 0; // 從dummy開始 
  for(int i = 2; i <= len; i++){
    while(j && Pattern[i] != Pattern[j+1]){
      j = pi[j];
    }
    if(Pattern[j+1] == Pattern[i]) j++;
    pi[i] = j;
  }
}

vector<int> KMP(string Text, string Pattern){
  // all 1-indexed
  int lT = Text.size(), lP = Pattern.size();
	Text = "#" + Text;
  Pattern = "#" + Pattern;
  vector<int> ans;
	Prefix(Pattern);
	for(int i = 1, j = 0; i <= lT; i++){
		while(j > 0 && Pattern[j+1] != Text[i])
			j = pi[j];
		if (Pattern[j+1] == Text[i])
			j ++;
		if (j == lP) 
		{
      // 如果match到了, 出現位置為 i-k (1-indexed)
			j = pi[j];
      ans.push_back(i-lP+1);
		} 
	}
  return ans;
}