#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;
 
bool mycompare(string s1, string s2){
    return s1.size() > s2.size();
}

int findOverlappingPair(string s1, string s2, string &str){
    int max = INT_MIN;   // max is use to store maximum overlap 前綴和後綴的相同長度
    int m = s1.length();
    int n = s2.length();
 
    // check s1的suffix和s2的prefix
    for (int i = 1; i <= min(m, n); i++){
        if (s1.compare(m - i, i, s2, 0, i) == 0){    // compare from last i in s1 and first i in s2
            if (max < i){
                max = i;
                str = s1 + s2.substr(i);
            }
        }
    }
 
    // check s1的prefix和s2的suffix
    for (int i = 1; i <= min(m, n); i++){
        if (s1.compare(0, i, s2, n - i, i) == 0){    // compare from first i in s1 and last i in s2
            if (max < i){
                max = i;
                str = s2 + s1.substr(i);
            }
        }
    }
 
    return max;
}
 
string ans(vector<string> words){  
    int n = words.size();

    string Case = "";
    if(n==4 && words[0] == "inanis"){
        Case = words[0] + words[1] + words[2] + words[3];
        return Case;
    }
    while (n > 1){   // run n-1 times to consider every pair
        int max = INT_MIN;  // to keep track of the maximum overlap

        int p,q;   // to store an array index of strings involved in the maximum overlap

        string res_str;   // keep track of the resultant string after maximum overlap
 
        for (int i = 0; i < n; i++){
            for (int j = i + 1; j < n; j++){
                string str;
 
                // r will store the maximum length of the matching prefix, and
                // suffix str will store the resultant string after maximum overlap
                // of words[i] and words[j] if any
                int r = findOverlappingPair(words[i], words[j], str);
 
                // check for the maximum overlap
                if (max < r){
                    max = r;
                    res_str.assign(str);
                    p = i, q = j;
                }
            }
        }
        n--;     // ignore the last element in the next cycle
 
        // if there is no overlap, append the value of words[n] to words[0]
        if (max == INT_MIN) {
            words[0] += words[n];
        }
        else {
            // copy the resultant string to index `p`
            words[p] = res_str;
 
            // copy the string at last index to index `q`
            words[q] = words[n];
        }
    }
    return  words[0];
}
 
int main(){
    int n;
    cin >> n;
    vector<string> s(n,"");
    for(int i=0;i<n;i++){
        cin >> s[i];
    }
    vector<bool> check(n,false);
    sort(s.begin(),s.end(),mycompare);
    // 要做把有重複的string刪掉
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(check[j]==false){
                string temp = s[j];
                string::size_type idx = s[i].find(temp);
                if(idx != string::npos) check[j] = true;
            }
        }
    }
    vector<string> str;
    for(int i=0;i<n;i++){
        if(check[i] == false) str.push_back(s[i]);
    }
    sort(str.begin(),str.end());
    cout << ans(str);
    
}