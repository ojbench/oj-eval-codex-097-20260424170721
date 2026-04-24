// Problem 097 - Kth largest in BST from level-order input
#include <bits/stdc++.h>
using namespace std;

struct Node { int val; Node* left; Node* right; Node(int v): val(v), left(nullptr), right(nullptr) {} };

// Build BST by inserting values one by one (from arbitrary order)
static Node* insertBST(Node* root, int v){
    if(!root) return new Node(v);
    if(v < root->val) root->left = insertBST(root->left, v);
    else root->right = insertBST(root->right, v);
    return root;
}

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
    vector<int> nums;
    vector<int> rootVals;
    int cnt = -1;

    // Find content within brackets
    size_t lb = input.find('[');
    size_t rb = input.find(']');
    if(lb != string::npos && rb != string::npos && rb > lb){
        string arr = input.substr(lb+1, rb-lb-1);
        // split by comma or spaces
        string cur;
        for(char c: arr){
            if(c==',' || isspace((unsigned char)c)){
                if(!cur.empty()){ rootVals.push_back(stoi(cur)); cur.clear(); }
            }else{
                cur.push_back(c);
            }
        }
        if(!cur.empty()) rootVals.push_back(stoi(cur));
    }else{
        // Fallback: try to read space-separated ints from stdin, first n-1 are root until a non-int token? Not defined.
        // Exit gracefully
    }

    // Find cnt: look for "cnt" then parse following numbers; otherwise, parse last integer in input
    {
        // Extract all ints in the whole input
        long long sign = 1; long long val = 0; bool inNum=false; bool neg=false; vector<long long> all;
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

    // Build BST from given values (level-order of a BST is still the set of values; build by insertion to reconstruct a valid BST)
    Node* root=nullptr;
    for(int v: rootVals) root = insertBST(root, v);

    // Reverse in-order traversal to find kth largest
    int k = cnt; int ans=-1;
    vector<Node*> st; Node* cur=root;
    while(cur || !st.empty()){
        while(cur){ st.push_back(cur); cur = cur->right; }
        cur = st.back(); st.pop_back();
        if(--k==0){ ans = cur->val; break; }
        cur = cur->left;
    }

    if(ans!= -1) cout << ans;
    else cout << "";
    return 0;
}

