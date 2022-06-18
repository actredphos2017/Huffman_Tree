#pragma once

using namespace std;

struct HTree_Node {
    char data;
    int weight;
    int parent;
    int lchild;
    int rchild;
};

typedef vector<HTree_Node> HTreeType;

struct NodeType {
    int no;
    char data;
    int weight;
};

list<NodeType> Get(map<char, int> char_weight);
NodeType push_min(list<NodeType>& hl);
char random_char();
bool ifRepeat(char c, vector<char> v);
void filful_str(string& str, int n);
string ctos(char c);
string data_put(HTree_Node htn, vector<char> mcode);
int _pow(int n, int m);

struct Circle {
    int x, y;
    HTree_Node Target_Node;
    void shadow_print(vector<char> mcode);
    void print(vector<char> mcode);
};

struct douC {
    Circle c[2];
};

typedef vector<Circle> circles;

struct Line {
    Circle dc[2];
    void print();
};

typedef vector<Line> lines;

class Huffman {
public:
    HTreeType tree;
    map<char, string> code;
    vector<char> cmap;
public:
    void BuildTree(map<char, int>& char_weight);
    void BuildCode(map<char, int>& char_weight);
    void BuildCode(size_t n);
    void clear();
    void Hfmtree_Output(ofstream& oF, map<char, int>& char_weight);
    int Depth();
    void BuildFullTree(HTreeType& Tree, int loc, int depth);
    vector<HTree_Node> Full_Level_Tree();
    void VisualPrint();
    void Visual_Print_EasyX();
};

unsigned int count_of_decimal_digits(double x);
map<char, int> double_map_to_int(map<char, double> m);
double string_to_double(string s);

string filename(string path);
string filedir(string path);
string filenamewithoutext(string path);

Huffman design_code(string path);
Huffman build_code(string path);