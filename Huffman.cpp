#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <cmath>
#include <string>
#include <iostream>
#include <graphics.h>
#include <queue>
#include "Huffman.h"

#define DESTENCE 50
#define HEIGTH 75
#define MAX_DES 1920
#define MAX_HEI 1080
#define SAVE_DES 100
#define RADIUS 20
#define DATA_TEXTSIZE 35
#define WEIGHT_TEXTSIZE 25
#define SHADOW_DISTENCE 3
#define SHADOW_COLOUR 0x77787b
#define FILL_COLOUR 0xa3cf62
#define TEXTFONT "JetBrains Mono"
#define SEP ":"

using namespace std;

list<NodeType> Get(map<char, int> char_weight) {
    list<NodeType> ht;
    for (auto& c : char_weight) {
        NodeType node;
        node.no = ht.size();
        node.data = c.first;
        node.weight = c.second;
        ht.push_back(node);
    }
    return ht;
}

NodeType push_min(list<NodeType>& hl) {
    NodeType min;
    list<NodeType>::iterator min_loc = hl.begin();
    for (auto i = hl.begin(); i != hl.end(); i++) {
        if (i == hl.begin()) {
            min = *i;
            min_loc = i;
        }
        else if (i->weight < min.weight) {
            min = *i;
            min_loc = i;
        }
    }
    hl.erase(min_loc);
    return min;
}

char random_char() {
    char c = '\0';
    while (c == '\0')
        c = rand() % 127;
    return c;
}

bool ifRepeat(char c, vector<char> v) {
    for (auto i : v)
        if (i == c)
            return true;
    return false;
}

void filful_str(string& str, int n) {
    while (str.size() < n)
        str += " ";
}

string ctos(char c) {
    string str = "";
    str += c;
    return str;
}

string data_put(HTree_Node htn, vector<char> mcode) {
    if (htn.data == '\0')
        return " ";
    if (htn.data == '\n')
        return string("\\n") + SEP + to_string(htn.weight);
    if (find(mcode.begin(), mcode.end(), htn.data) != mcode.end())
        return ctos(htn.data) + SEP + to_string(htn.weight);
    return ctos('^') + SEP + to_string(htn.weight);
}

void Circle::shadow_print(vector<char> mcode) {
    if (this->Target_Node.data == '\0')
        return;
    setfillcolor(SHADOW_COLOUR);
    solidcircle(SAVE_DES + this->x + SHADOW_DISTENCE, SAVE_DES + this->y + SHADOW_DISTENCE, RADIUS + 1);
}

void Circle::print(vector<char> mcode) {
    if (this->Target_Node.data == '\0')
        return;
    setfillcolor(FILL_COLOUR);
    solidcircle(SAVE_DES + this->x, SAVE_DES + this->y, RADIUS);
    if (find(mcode.begin(), mcode.end(), this->Target_Node.data) != mcode.end()) {
        char _arr[3];
        if (this->Target_Node.data == '\n') {
            _arr[0] = '\\';
            _arr[1] = 'n';
            _arr[2] = '\0';
        }
        else {
            _arr[0] = this->Target_Node.data;
            _arr[1] = '\0';
        }
        int width = textwidth(_arr);
        int heigh = textheight(_arr);
        setbkmode(TRANSPARENT);
        outtextxy(SAVE_DES + this->x - width / 2, SAVE_DES + this->y - heigh / 2, _arr);
    }
}

void Line::print() {
    if (this->dc[0].Target_Node.data == '\0' || this->dc[1].Target_Node.data == '\0')
        return;
    line(SAVE_DES + this->dc[0].x, SAVE_DES + this->dc[0].y, SAVE_DES + this->dc[1].x, SAVE_DES + this->dc[1].y);
    string str = to_string(this->dc[1].Target_Node.weight);
    int width = textwidth(str.c_str());
    int heigh = textheight(str.c_str());
    setbkmode(OPAQUE);
    outtextxy(SAVE_DES + (this->dc[0].x + this->dc[1].x) / 2 - width / 2, SAVE_DES + (this->dc[0].y + this->dc[1].y) / 2 - heigh / 2, str.c_str());
}

int _pow(int n, int m) {
    int r = 1;
    while (m-- > 0)
        r *= n;
    return r;
}

void Huffman::BuildTree(map<char, int>& char_weight) {
    srand(time(NULL));
    for (auto& c : char_weight)
        tree.push_back(HTree_Node{ c.first, c.second, -1, -1, -1 });
    list<NodeType> l = Get(char_weight);
    vector<char> v;
    v.push_back('\0');
    for (auto& c : char_weight) {
        v.push_back(c.first);
        this->cmap.push_back(c.first);
    }
    while (l.size() > 1) {
        NodeType min[2];
        min[0] = push_min(l);
        min[1] = push_min(l);
        char temp = random_char();
        while (ifRepeat(temp, v))
            temp = random_char();
        v.push_back(temp);
        tree.push_back(HTree_Node{ temp, min[0].weight + min[1].weight, -1, min[0].no, min[1].no });
        tree[min[0].no].parent = tree.size() - 1;
        tree[min[1].no].parent = tree.size() - 1;
        l.push_back(NodeType{ (int)tree.size() - 1, temp, min[0].weight + min[1].weight });
    }
}

void Huffman::BuildCode(map<char, int>& char_weight) {
    for (int i = 0; i < char_weight.size(); i++) {
        code[tree[i].data] = "";
        int p = i;
        while (tree[p].parent != -1) {
            if (p == tree[tree[p].parent].lchild)
                code[tree[i].data] = "0" + code[tree[i].data];
            else
                code[tree[i].data] = "1" + code[tree[i].data];
            p = tree[p].parent;
        }
    }
}

void Huffman::BuildCode(size_t n) {
    for (int i = 0; i < n; i++) {
        code[tree[i].data] = "";
        int p = i;
        while (tree[p].parent != -1) {
            if (p == tree[tree[p].parent].lchild)
                code[tree[i].data] = "0" + code[tree[i].data];
            else
                code[tree[i].data] = "1" + code[tree[i].data];
            p = tree[p].parent;
        }
    }
}

void Huffman::clear() {
    this->code.clear();
    this->cmap.clear();
    this->tree.clear();
}

void Huffman::Hfmtree_Output(ofstream& oF, map<char, int>& char_weight) {
    for (auto& c : this->code)
        if (char_weight.find(c.first) != char_weight.end())
            oF << c.second << " " << c.first << endl;
}

int Huffman::Depth() {
    int max = 0;
    for (auto& line : this->code)
        if (line.second.size() > max)
            max = line.second.size();
    return max + 1;
}

void Huffman::BuildFullTree(HTreeType& Tree, int loc, int depth) {
    depth--;
    if (depth == 0)
        return;
    if (Tree[loc].lchild == -1) {
        Tree[loc].lchild = Tree.size();
        Tree.push_back(HTree_Node{ '\0', 0, loc, -1, -1 });
    }
    if (Tree[loc].rchild == -1) {
        Tree[loc].rchild = Tree.size();
        Tree.push_back(HTree_Node{ '\0', 0, loc, -1, -1 });
    }
    BuildFullTree(Tree, Tree[loc].lchild, depth);
    BuildFullTree(Tree, Tree[loc].rchild, depth);
    return;
}

vector<HTree_Node> Huffman::Full_Level_Tree() {
    HTreeType copy_tree = this->tree;
    BuildFullTree(copy_tree, copy_tree.size() - 1, this->Depth());
    vector<char> mainc;
    vector<HTree_Node> res;
    res.push_back(this->tree.back());
    list<HTree_Node> l;
    l.push_back(copy_tree[tree.size() - 1]);
    while (!l.empty()) {
        if (l.front().lchild != -1) {
            l.push_back(copy_tree[l.front().lchild]);
            res.push_back(copy_tree[l.front().lchild]);
        }
        if (l.front().rchild != -1) {
            l.push_back(copy_tree[l.front().rchild]);
            res.push_back(copy_tree[l.front().rchild]);
        }
        l.pop_front();
    }
    return res;
}

void Huffman::VisualPrint() {
    int t = 0;
    vector<HTree_Node> full_tree = this->Full_Level_Tree();
    auto it = full_tree.rbegin();
    vector<string> lines;
    list<int> l;
    list<bool> has_value;
    for (int k = this->Depth() - 1; k >= 0; k--) {
        if (k == this->Depth() - 1) {
            string temp = "";
            int flag = 0;
            for (int i = 0; i < (int)pow(2, k); i++) {
                has_value.push_back(it->data != '\0');
                temp += data_put(*(it++), this->cmap);
                flag++;
                if (flag % 2 == 1)
                    l.push_back(temp.size() - 1);
                if (i != (int)pow(2, (this->Depth() - 1)) - 1)
                    temp += "  ";
            }
            lines.push_back(temp);
        }
        else {
            string temp = "";
            int flag = 0;
            list<int> _l = l;
            l.clear();
            while (!_l.empty()) {
                has_value.push_back(it->data != '\0');
                filful_str(temp, _l.front());
                _l.pop_front();
                string str = data_put(*it, this->cmap);
                temp += str;
                flag++;
                if (flag % 2 == 0)
                    l.push_back((temp.size() - str.size() - t) / 2 + t - 1);
                else
                    t = temp.size();
                it++;
            }
            lines.push_back(temp);
        }
        if (k != 0) {
            string temp = "";
            list<int> _l = l;
            while (!_l.empty()) {
                filful_str(temp, _l.front());
                _l.pop_front();
                temp += has_value.front() ? "/ " : "  ";
                has_value.pop_front();
                temp += has_value.front() ? "\\" : " ";
                has_value.pop_front();
            }
            lines.push_back(temp);
        }
    }
    cout << endl;
    cout << "==========================================" << endl;
    cout << "         Visual Huffman Tree" << endl << endl;
    for (auto rit = lines.rbegin(); rit != lines.rend(); rit++)
        cout << *rit << endl;
    cout << endl;
    cout << "==========================================" << endl;
}

void Huffman::Visual_Print_EasyX() {
    int depth = 1;
    vector<HTree_Node> Full_Tree = this->Full_Level_Tree();
    while (_pow(2, depth) - 1 < Full_Tree.size())
        depth++;
    if (_pow(2, depth) - 1 != Full_Tree.size())
        exit(-1);
    if (2 * SAVE_DES + DESTENCE * (_pow(2, depth - 1) - 1) > MAX_DES || 2 * SAVE_DES + HEIGTH * (depth - 1) > MAX_HEI) {
        cout << "This graph is too big!" << endl;
        return;
    }
    auto it = Full_Tree.begin();
    circles cs;
    lines ls;
    queue<Circle> q;
    douC dc;
    for (int i = 0; i < depth; i++) {
        int y = i * HEIGTH;
        int x = (_pow(2, depth - i - 1) - 1) * DESTENCE / 2;
        for (int j = 0; j < _pow(2, i); j++, x += _pow(2, depth - i - 1) * DESTENCE) {
            Circle c = { x, y, *(it++) };
            cs.push_back(c);
            q.push(c);
            dc.c[j % 2] = c;
            if (j % 2 == 1) {
                Circle headc = q.front();
                q.pop();
                ls.push_back(Line{ headc, dc.c[0] });
                ls.push_back(Line{ headc, dc.c[1] });
            }
        }
    }
    initgraph(2 * SAVE_DES + DESTENCE * (_pow(2, depth - 1) - 1), 2 * SAVE_DES + HEIGTH * (depth - 1));
    setbkcolor(WHITE);
    cleardevice();
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 3);
    settextcolor(BLACK);
    settextstyle(WEIGHT_TEXTSIZE, 0, TEXTFONT);
    outtextxy(SAVE_DES + cs[0].x - textwidth(to_string(cs[0].Target_Node.weight).c_str()) / 2,
        SAVE_DES + cs[0].y - textheight(to_string(cs[0].Target_Node.weight).c_str()) - RADIUS,
        to_string(cs[0].Target_Node.weight).c_str());
    for (auto it : cs) {
        it.shadow_print(this->cmap);
    }
    for (auto it : ls)
        it.print();
    settextstyle(DATA_TEXTSIZE, 0, TEXTFONT);
    for (auto it : cs) {
        it.print(this->cmap);
    }

}

string filename(string path) {
    int i = path.length() - 1;
    while (path[i] != '/') {
        i--;
    }
    return path.substr(i + 1);
}

string filedir(string path) {
    int i = path.length() - 1;
    while (path[i] != '/') {
        i--;
    }
    return path.substr(0, i + 1);
}

string filenamewithoutext(string path) {
    int i = path.length() - 1;
    while (path[i] != '.') {
        i--;
    }
    return path.substr(0, i);
}

Huffman design_code(string path) {
    string fn = filename(path);
    cout << "File name: " << fn << endl;
    ifstream iF(path);
    map<char, double> _char_weight;
    for (string line; getline(iF, line); )
        if (line.substr(0, 2) == "\\n")
            _char_weight['\n'] = string_to_double(line.substr(3));
        else
            _char_weight[line[0]] = string_to_double(line.substr(2));
    iF.close();
    map<char, int> char_weight = double_map_to_int(_char_weight);
    Huffman huffman;
    huffman.BuildTree(char_weight);
    huffman.BuildCode(char_weight);
    return huffman;
}

Huffman build_code(string path) {
    string fn = filename(path);
    cout << "File name: " << fn << endl;
    ifstream iF(path);
    vector<string> lines;
    for (string line; getline(iF, line); )
        lines.push_back(line);
    iF.close();
    map<char, int> char_weight;
    for (auto& line : lines) {
        for (auto& c : line)
            char_weight[c] ++;
        char_weight['\n'] ++;
    }
    Huffman huffman;
    huffman.BuildTree(char_weight);
    huffman.BuildCode(char_weight);
    return huffman;
}