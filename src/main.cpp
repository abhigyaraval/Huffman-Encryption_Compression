#include <bits/stdc++.h>
using namespace std;


// Node class for implementing a node on the binary tree
class Node
{
    public:
    int val;
    char chr;
    char bin = (char) 0;
    Node* left = NULL;
    Node* right = NULL;

    Node(char chr1, int val1)
    {
        val = val1;
        chr = chr1;
    }
};

// Comparator for implementing min heap of Node objects
class comparator
{
 public:
   bool operator()(const Node* a, const Node* b)
   {
        return a->val>b->val;
   }
};

// Return data structures for encoding and decoding functions
struct encoded_data
{   
    string new_string;
    priority_queue <Node*, vector<Node*>, comparator> min_heap;
};





// Function declarations
map<char, int> count_occurences(string str1){
// Create a map of letters and the number of occurences
    map<char, int> li;
    for(auto chr=str1.begin(); chr!=str1.end(); chr++){
        char current = *chr;
        // string current;
        // current.push_back(current_char);
        map<char, int>::iterator iter = li.find(current);
        if(iter==li.end()){
            size_t cnt = count(str1.begin(), str1.end(), current);
            li.insert(make_pair(current, cnt));
        }
    }

    // for(auto pp = li.begin(); pp!=li.end(); pp++){
    //     // pair<string, int> p = *pp;
    //     cout << pp -> first << " -> " << pp -> second << endl << endl << endl;
    // };

    return li;
}

void find_binary_path(Node *head, map<char, string>&hash_fun, string bincode){

    bincode.push_back(head->bin);
    // map<string, string> hash_fun;
    if(head->left==NULL && head->right==NULL){
        // hash_fun = hash_fun_in;
        map<char, string>::iterator iter = hash_fun.find(head->chr);
        iter->second = bincode;
        return;
    }
    if(head->left!=NULL){
        // Go down the left path
        find_binary_path(head->left, hash_fun, bincode);
    }
    if(head->right!=NULL){
        // Go down the right path
        find_binary_path(head->right, hash_fun, bincode);
    }

    return;
}



int main(int argc, char **argv){

    // string str1 = "AAAAAAABBBCCCCCCCDDEEEEEE";
    string str1 = "Hey! Whats up!!!";
    
    auto li = count_occurences(str1);   // Getting a dict of chars in the string and their number of occurences

    // for(auto pp = li.begin(); pp!=li.end(); pp++){
    //     // pair<string, int> p = *pp;
    //     cout << pp -> first << " -> " << pp -> second << endl << endl << endl;
    // };
    
    // Encode string
    priority_queue <Node*, vector<Node*>, comparator> min_heap;
    
    for(auto chr=li.begin(); chr!=li.end(); chr++){
        min_heap.push(new Node(chr -> first, chr -> second));
    }

    // Lets start to encode
    while(min_heap.size() > 1){

        Node *left, *right, *top;

        left = min_heap.top();
        min_heap.pop();

        right = min_heap.top();
        min_heap.pop();

        left->bin = '0';
        right->bin = '1';

        top = new Node('_',left->val+right->val);
        top->left = left;
        top->right = right;
 
        // cout << "Left: " << left->chr << ", " << left->val << endl;
        // cout << "Right: " << right->chr << ", " << right->val << endl;
        
        min_heap.push(top);
    }


// Making sure tree is there
    // Node* current_head = min_heap.top();
    // int i = 0;
    // while( i < 5){
    //     cout << current_head->val << endl;
    //     current_head = current_head->left;
    //     i++;
    // }
// Get the code for encryption
    map <char, string> hash_fun;
    // auto node=li.begin();
    // node++;
    for(auto node=li.begin(); node!=li.end(); node++){
        hash_fun.insert(make_pair(node->first, "_"));
    }

    struct encoded_data answer;


    string bincode;
    Node* head = min_heap.top();
    // Node *headptr = &head;
    // auto *hsh = &hash_fun;
    find_binary_path(head, hash_fun, bincode);

    for(auto node=hash_fun.begin(); node!=hash_fun.end(); node++){
        // cout << node->first << ": " << node->second << endl;
    }

    string coded_string;
    for(auto chr=str1.begin(); chr!=str1.end(); chr++){
        map<char, string>::iterator itr = hash_fun.find(*chr);
        coded_string.append(itr->second);
    }

cout << coded_string << endl;

    answer.min_heap = min_heap;
    answer.new_string = coded_string;



//     // Decode string

    string decode_data;
    Node* current = min_heap.top();
    auto bin=coded_string.begin();
    bin++;
    for(bin; bin!=coded_string.end(); bin++){
        int current_bin = (int)*bin;

        if(current_bin == '0'){
            current = current->left;
        }
        else if(current_bin == '1'){
            current = current->right;
        }
        else if (current_bin != '0' && current_bin != '1'){
            decode_data.push_back(current->chr);
            current = min_heap.top();
        }

    }
    
    cout << decode_data << endl;

    cout << endl << endl;
    return 0;
}



