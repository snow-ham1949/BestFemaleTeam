// record alphabets' occurence in text 
bitset<10000> mask[26];
string text;

// set up mask
void SetMask(){
  text = "#" + text; // let the text become 1-indexed
  for(int i = 1; i < text.size(); i++){
    mask[text[i]-'a'][i] = 1; // set up bit
  }
}

// modified mask and the string
void ChangeMask(int pos, char c){
  mask[text[pos]-'a'][pos] = 0;
  text[pos] = c;
  mask[text[pos]-'a'][pos] = 1;
}

// find pattern count in text[l..r]
int Substring(string pattern, int l, int r){
  // range validation
  if (r - l + 1 < pattern.size())
    return 0;
  // 1. set a ans_mask with all 1
  // 2. for i in pattern, ans_mask &= (mask[pattern[i] - 'a'] >> i);
  // 3. ans_mask >> (l-1).count - ans_mask >> (r-len+1).count
  bitset<MAX> ans_mask;
  ans_mask.set();
  pattern = "#" + pattern;
  for(int i = 1; i < pattern.size(); i++){
    ans_mask &= (mask[pattern[i] - 'a'] >> i);
  }
  return (ans_mask >> (l-1)).count() - (ans_mask >> (r - pattern.size() + 2)).count();
}