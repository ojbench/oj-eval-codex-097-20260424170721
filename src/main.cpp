// Problem 097 - Kth largest in BST from level-order input
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read entire stdin
    string input;
    {
        ostringstream oss; oss << cin.rdbuf(); input = oss.str();
    }
    if(input.empty()) return 0;

    // Normalize by removing spaces around '=' and commas handling
    // Expected patterns include: root = [a,b,...], cnt = k
    // We'll extract numbers within the first [...] as root, and the last number as cnt
    vector<int> rootVals;
    int cnt = -1;

    // Find content within brackets and extract all integers inside
    size_t lb = input.find('[');
    size_t rb = input.find(']');
    if(lb != string::npos && rb != string::npos && rb > lb){
        string arr = input.substr(lb+1, rb-lb-1);
        long long val = 0; bool inNum=false; bool neg=false;
        for(char ch : arr){
            if((ch=='-' && !inNum) || isdigit((unsigned char)ch)){
                if(!inNum){ inNum=true; neg=false; val=0; if(ch=='-'){ neg=true; continue; } }
                if(isdigit((unsigned char)ch)) val = val*10 + (ch-'0');
            }else{
                if(inNum){ rootVals.push_back((int)(neg? -val : val)); inNum=false; }
            }
        }
        if(inNum){ rootVals.push_back((int)(neg? -val : val)); }
    }else{
        // Fallback: try to read space-separated ints from stdin, first n-1 are root until a non-int token? Not defined.
        // Exit gracefully
    }

    // Find cnt: look for "cnt" then parse following numbers; otherwise, parse last integer in input
    {
        // Extract all ints in the whole input
        long long val = 0; bool inNum=false; bool neg=false; vector<long long> all;
        for(size_t i=0;i<input.size();++i){
            char c=input[i];
            if(c=='-' && !inNum){ inNum=true; neg=true; val=0; }
            else if(isdigit((unsigned char)c)){
                if(!inNum){ inNum=true; neg=false; val=0; }
                val = val*10 + (c-'0');
            }else{
                if(inNum){ all.push_back(neg?-val:val); inNum=false; }
            }
        }
        if(inNum){ all.push_back(neg?-val:val); }
        if(!all.empty()){
            // If we parsed rootVals earlier, take cnt as last of all ints but not in the bracket list length unknown.
            // Safer: try regex for cnt = number
            std::smatch m; std::regex re("cnt\\s*=\\s*(-?\\d+)");
            if(std::regex_search(input, m, re)){
                cnt = stoi(m[1]);
            }else{
                // fallback: the last integer after the closing bracket position
                cnt = (int)all.back();
            }
        }
    }

    if(rootVals.empty() || cnt<=0){
        return 0; // Nothing to do
    }

    // Find kth largest using nth_element for O(n) average
    int n = (int)rootVals.size();
    if(cnt > n) cnt = n; // safe-guard
    int idx = n - cnt; // 0-based index for kth largest in ascending order
    nth_element(rootVals.begin(), rootVals.begin() + idx, rootVals.end());
    cout << rootVals[idx];
    return 0;
}
