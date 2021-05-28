/* Implement an autocomplete system. That is, given a query string s and a set of all possible query strings, 
return all strings in the set that have s as a prefix.
For example, given the query string de and the set of strings [dog, deer, deal], return [deer, deal].
Hint: Try preprocessing the dictionary into a more efficient data structure to speed up queries. */


//We use a normal Trie datastructure. If we don't have the given prefix anywhere in our trie we return -1 else we check for all the words
//whose prefix matches with the given one and isEoW flag was set.

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)

//trie node
typedef struct Trie{
    //It holds true if that character(node) represents end of the word.
    bool leaf;
    struct Trie* child[26];
}trie;

//create and return a new empty node with leaf initialised to false and all children to NULL
trie* create(){
    trie* temp = new trie();
    temp->leaf = false;
    for(ll i=0;i<26;i++) temp->child[i] = NULL;
    return temp;
}

//If it's not present, inserts the given string into trie
void insert(trie* root1, string s){
    trie* root = root1;
    for(ll i=0;i<s.size();i++){
        if(root->child[s[i] - 'a'] == NULL) root->child[s[i] - 'a'] = create();
        root = root->child[s[i] - 'a'];
    }
    root->leaf = true;
}

bool isLastNode(trie* current1){
    trie* current = current1;
    for(ll i=0;i<26;i++)
        if(current->child[i]) return false;
    return true;
}

//For each prefix if we reach end of word add it to our vector. Else find all the next possible letters that
//were available in the trie and recursively make the function calls
void check_recursive(trie* root1, string prefix,vector<string> &ans){
    trie* root = root1;
    if(root->leaf)
        ans.push_back(prefix);
    if(isLastNode(root)) return;
    for(ll i=0;i<26;i++){
        if(root->child[i]){
            prefix += (i+'a');
            check_recursive(root->child[i],prefix,ans);
            prefix.pop_back();
        }
    }
}

//If the given prefix itself doesn't exist in the trie we return 0 else we call the check_recursive function
ll populate(trie* root1, string prefix, vector<string> &ans){
    trie* root = root1;
    for(ll i=0;i<prefix.size();i++){
        if(root->child[prefix[i] - 'a'] == NULL) return 0;
        root = root->child[prefix[i] - 'a'];
    }
    if(isLastNode(root) == false){
        check_recursive(root,prefix,ans);
        return 1;
    }
}



int32_t main()
{ 
    vector<string> ans;
    trie* root = create();
    insert(root, "hello");
    insert(root, "dog");
    insert(root, "hell");
    insert(root, "cat");
    insert(root, "a");
    insert(root, "hel");
    insert(root, "help");
    insert(root, "helps");
    insert(root, "helping");
    if(populate(root,"gel",ans) == 0) cout << "Nothing found\n";
    for(ll i=0;i<ans.size();i++) cout << ans[i] << ' ';
    
    return 0;
}