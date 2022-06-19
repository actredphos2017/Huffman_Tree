#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <fstream>
using namespace std;
#define MAX 101

struct HTreeNode
{
    char data = '\0';
    int weight;
    int parent;
    int lchild;
    int rchild;
};

HTreeNode ht[MAX];
map<char, string> htcode;
map<string, char> Tranhtcode;
string str[MAX];
int n;
ofstream oF;
ifstream iF;

#include <list>
#define SEP ":"

int depth(int loc = n-1) {
    int max = htcode.begin()->second.size();
    for (auto& line : htcode)
        if (line.second.size() > max)
            max = line.second.size();
    return max + 1;
}

void BuildFullTree(vector<HTreeNode>& _ht, int loc, int depth) {
    depth--;
    if (depth == 0)
        return;
    if (_ht[loc].lchild == -1) {
        _ht[loc].lchild = _ht.size();
        _ht.push_back(HTreeNode{ '\0', 0, loc, -1, -1 });
    }
    if (_ht[loc].rchild == -1) {
        _ht[loc].rchild = _ht.size();
        _ht.push_back(HTreeNode{ '\0', 0, loc, -1, -1 });
    }
    BuildFullTree(_ht, _ht[loc].lchild, depth);
    BuildFullTree(_ht, _ht[loc].rchild, depth);
    return;
}

vector<HTreeNode> Full_Level_Tree() {
    vector<HTreeNode> copy_tree;
    for (int i = 0; i < n; i++)
        copy_tree.push_back(ht[i]);
    list<HTreeNode> l;
    l.push_back(copy_tree.back());
    vector<char> mainc;
    vector<HTreeNode> res;
    res.push_back(copy_tree.back());
    BuildFullTree(copy_tree, copy_tree.size() - 1, depth());
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

void filful_str(string& str, int n) {
    while (str.size() < n)
        str += " ";
}

string ctos(char c) {
    string str = "";
    str += c;
    return str;
}

string data_put(HTreeNode htn) {
    if (htn.data == '\0')
        return " ";
    if (htn.data == '\n')
        return string("\\n") + SEP + to_string(htn.weight);
    if (htn.data != '#')
        return ctos(htn.data) + SEP + to_string(htn.weight);
    return ctos('^') + SEP + to_string(htn.weight);
}

void VisualPrint() {
    int t = 0;
    vector<HTreeNode> full_tree = Full_Level_Tree();
    auto it = full_tree.rbegin();
    vector<string> lines;
    list<int> l;
    list<bool> has_value;
    int _d = depth();
    for (int k = _d - 1; k >= 0; k--) {
        if (k == _d - 1) {
            string temp = "";
            int flag = 0;
            for (int i = 0; i < (int)pow(2, k); i++) {
                has_value.push_back(it->data != '\0');
                temp += data_put(*(it++));
                flag++;
                if (flag % 2 == 1)
                    l.push_back(temp.size() - 1);
                if (i != (int)pow(2, (_d - 1)) - 1)
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
                string str = data_put(*it);
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









//建树
void CreateHTree()
{
    for (int i = 0; i < n; i++)
    {
        ht[i].parent = -1;
        ht[i].lchild = -1;
        ht[i].rchild = -1;
    }
    for (int i = n; i < n * 2 - 1; i++)
    {
        ht[i].parent = -1;
        ht[i].lchild = -1;
        ht[i].rchild = -1;
        ht[i].data = '#';
    }
    int s1, s2;
    for (int i = n; i < n * 2 - 1; i++)
    {
        s1 = -1;
        s2 = -1;
        for (int j = 0; j <= i - 1; j++)
        {
            if (ht[j].parent == -1)
            {
                if (s1 == -1)
                    s1 = j;
                else if (ht[j].weight < ht[s1].weight)
                    s1 = j;
            }
        }
        for (int k = 0; k <= i - 1; k++)
        {
            if (ht[k].parent == -1 && k != s1)
            {
                if (s2 == -1)
                    s2 = k;
                else if (ht[k].weight < ht[s2].weight)
                    s2 = k;
            }
        }

        ht[s1].parent = i;
        ht[s2].parent = i;
        ht[i].lchild = s1;
        ht[i].rchild = s2;
        ht[i].weight = ht[s2].weight + ht[s1].weight;
    }

}

//建哈夫曼编码
void CreateHCode()
{
    int *t = new int[3 * n];
    int start = 0;
    int end = 0;
    t[++end] = 2 * n - 2;
    str[2 * n - 2] = "";
    while (start != end)
    {
        start++;
        if (ht[t[start]].rchild != -1)
        {
            t[++end] = ht[t[start]].rchild;
            str[ht[t[start]].rchild] = str[t[start]] + "1";
        }
        if (ht[t[start]].lchild != -1)
        {
            t[++end] = ht[t[start]].lchild;
            str[ht[t[start]].lchild] = str[t[start]] + "0";
        }
    }
    for (int i = 0; i < n; i++)
        htcode[ht[i].data] = str[i];
}

//功能列表
void show()
{
    system("cls");
    cout << "------------------哈夫曼树系统------------------" << endl;
    cout << "当前状态：" << endl;
    if (ht[0].data == '\0')
        cout << "哈夫曼树不存在" << endl;
    else
        cout << "哈夫曼树存在" << endl;
    if (htcode.empty())
        cout << "哈夫曼编码不存在" << endl;
    else
        cout << "哈夫曼编码存在" << endl;
    cout << "功能列表：" << endl;
    cout << "1.初始化" << endl;
    cout << "2.编码" << endl;
    cout << "3.译码" << endl;
    cout << "4.打印哈夫曼编码" << endl;
    cout << "Q.退出" << endl;
    cout << "请选择要使用的功能:  ";
}

//初始化
void Initialization()
{
    int choice2;
    string name;
    cout << endl << "选项：" << endl;
    cout << "1.直接输入" << endl;
    cout << "2.通过文件输入" << endl;
    cout << "3.返回" << endl;
    cout << "请选择数据的输入方式：";
    cin >> choice2;
    switch (choice2)
    {
    case 1:
        cout << "请输入字符的个数：";
        cin >> n;
        cout << "请输入全部字符及其权值" << endl;
        for (int i = 0; i < n; i++)
        {
            string temp = "";
            while (temp == "") getline(cin, temp, '\n');
            if (temp.substr(0, 2) == "\\n") {
                ht[i].data = '\n';
                ht[i].weight = atoi(temp.substr(3).c_str());
            }

            else {
                ht[i].data = temp[0];
                ht[i].weight = atoi(temp.substr(2).c_str());
            }

            temp == "";
        }
        CreateHTree();
        break;

    case 2:
        cout << "请输入读取文件名称(默认为sourcefile.txt):";
        getline(cin, name, '\n');
        if (name.empty())
            iF.open("sourcefile.txt");
        else
            iF.open(name);
        while (!iF.good())
        {
            cout << "文件不存在请重新输入：";
            getline(cin, name, '\n');
            if (name.empty())
                iF.open("sourcefile.txt");
            else
                iF.open(name);
        }
        int i = 0;
        iF >> n;
        while (i < n)
        {
            string temp = "";
            while (temp == "") getline(iF, temp);
            if (temp.substr(0, 2) == "\\n") {
                ht[i].data = '\n';
                ht[i].weight = atoi(temp.substr(3).c_str());
            }

            else {
                ht[i].data = temp[0];
                ht[i].weight = atoi(temp.substr(2).c_str());
            }
            i++;
        }
        CreateHTree();
        iF.close();
        break;

    case 3:
        system("cls");
        return;
        break;

    default:cout << "未存在该功能,请重新选择";
    }
    oF.open("hfmTree.txt");
    int i = 0;
    oF << n << endl;
    while (i < 2 * n - 1)
    {
        if (ht[i].data == '\n')
            oF << "\\n" << " ";
        else
            oF << ht[i].data << " ";
        oF << ht[i].weight << " " << ht[i].parent << " " << ht[i].lchild << " " << ht[i++].rchild << endl;
    }
    oF.close();
    system("pause");
}

//编码
void Encoding()
{
    int i, choice2;
    char ch;
    char* ch_;
    ch_ = (char*)malloc(sizeof(char) * 3);
    ch_[2] = '\0';
    cout << endl << "1.内存" << endl;
    cout << "2.文件" << endl;
    cout << "3.返回" << endl;
    cout << "请选择使用的哈夫曼树来源：";
    cin >> choice2;
    switch (choice2)
    {
    case 1:CreateHCode();
        break;

    case 2:
        iF.open("hfmTree.txt");
        i = 0;
        iF >> n;
        iF.read(ch_, 1);
        while (i < 2 * n - 1)
        {
            iF.read(ch_, 2);
            if (string(ch_, 2) == "  ")
                ht[i].data = ' ';
            else if (string(ch_, 2) == "\\n")
                ht[i].data = '\n';
            else
            {
                ht[i].data = ch_[0];
            }
            iF >> ht[i].weight >> ht[i].parent >> ht[i].lchild >> ht[i++].rchild;
            iF.read(ch_, 1);
        }
        iF.close();
        CreateHCode();
        break;

    case 3:
        system("cls");
        return;
        break;

    default:cout << "未存在该功能,请重新选择";
    }
    oF.open("hfmcode.txt");
    i = 0;
    while (i < n)
    {
        if (ht[i].data == '\n')
            oF << "\\n" << " " << str[i++] << endl;
        else
            oF << ht[i].data << " " << str[i++] << endl;
    }
    oF.close();
    iF.open("ToBeTran.txt");
    oF.open("CodeFile.txt");
    while (1)
    {
        iF.read(ch_, 1);
        if (iF.eof())break;
        ch = ch_[0];
        oF << htcode[ch];
    }
    oF.close();
    iF.close();
    system("pause");
}

//译码
void Decoding()
{
    char ch;
    char* ch_;
    ch_ = (char*)malloc(sizeof(char) * 3);
    string str_;
    iF.open("hfmcode.txt");
    while (true)
    {
        iF.read(ch_, 2);
        if (iF.eof())
            break;
        if (string(ch_, 2) == "  ")
            ch = ' ';
        else if (string(ch_, 2) == "\\n")
            ch = '\n';
        else
        {
            ch = ch_[0];
        }
        iF >> str_;
        Tranhtcode[str_] = ch;
        iF.read(ch_, 1);
    }
    iF.close();
    iF.open("CodeFile.txt");
    str_ = "";
    oF.open("Textfile.txt");
    while (!iF.eof())
    {
        iF >> ch;
        str_ = str_ + ch;
        if (Tranhtcode.find(str_) != Tranhtcode.end())
        {
            oF << Tranhtcode[str_];
            str_ = "";
        }
    }
    iF.close();
    oF.close();
    system("pause");
}

//打印哈夫曼编码
void Print()
{
    cout << "哈夫曼编码：" << endl;
    for (auto& c : htcode)
    {
        if (c.first == '\n')
            cout << "\\n " << c.second << endl;
        else
            cout << c.first << " " << c.second << endl;
    }
    system("pause");
}

int main()
{
    char choice1;
    while (choice1 != 'Q')
    {
        show();
        cin >> choice1;
        switch (choice1)
        {
        case '1':Initialization();
            break;

        case '2':Encoding();
            break;

        case '3':Decoding();
            break;

        case '4':Print();
            break;

        case 'Q':
            return 0;
            break;

        default:cout << "未存在该功能,请重新选择" << endl;
            system("pause");
        }
    }
    return 0;
}