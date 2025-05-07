//1.由括号表达式建树
#include<iostream>
#include<string>
#include<cctype>
using namespace std;

struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char x):val(x),left(nullptr),right(nullptr){}
};

class Binary_Tree {
public:
    TreeNode* root;

    //由括号表达式建树
    void buildFromBracketString(const string& s) {
        int pos = 0;
        root = parse(s, pos); //构造根节点
    }

    //后序遍历输出
    void postOrder(TreeNode* root) {
        if (root == nullptr) return;
        postOrder(root->left);
        postOrder(root->right);
        cout << root->val << " ";
    }

private:
    //提取结点
    TreeNode* parse(const string& s, int& pos) {
        if (pos >= s.size() || !isalpha(s[pos])) return nullptr;

        TreeNode* node = new TreeNode(s[pos++]);

        if (pos < s.size() && s[pos] == '(') {
            //不嵌套的话，会导致在没有 () 的节点上也尝试去解析左右孩子
            //因此嵌套表明：只在有子树结构时才去解析子树
            pos++; //跳过'('

            //遇到左孩子
            if (pos < s.size() && s[pos] != ',' && s[pos] != ')')
                node->left = parse(s, pos);
            //遇到','，说明下一个是右孩子
            if (pos < s.size() && s[pos] == ',') {
                pos++; //跳过','
                node->right = parse(s, pos);
            }

            if (pos < s.size() && s[pos] == ')') pos++; //跳过')'
        }
        return node;
    }
};

int main() {
    cout<<"请输入括号表达式："<<endl;
    string s;
    cin >> s; //输入如A(B(C),D)

    Binary_Tree Tree;
    Tree.buildFromBracketString(s);

    cout << "后序遍历是：" << endl; 
    Tree.postOrder(Tree.root);

    return 0;
}


//2.由层次遍历顺序建树
#include<iostream>
#include<string>
#include<queue>
using namespace std;

struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char x) :val(x), left(nullptr), right(nullptr) {}
};

class Binary_Tree {
public:
    TreeNode* root;

    void buildFromLevelOrder(const string& s) {
        if (s.empty() || s[0] == '#') return; //若输入为空或根节点为空，立即返回

        queue<TreeNode*>q; //创建队列
        int index = 0;
        root = new TreeNode(s[index++]); //创建根节点
        q.push(root);

        while (index < s.size() && !q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            //放入左孩子
            if (index < s.size() && s[index] != '#') {
                current->left = new TreeNode(s[index]);
                q.push(current->left);
            }
            index++;

            //放入右孩子
            if (index < s.size() && s[index] != '#') {
                current->right = new TreeNode(s[index]);
                q.push(current->right);
            }
            index++;
        }
    }

    //后序遍历输出
    void postOrder(TreeNode* root) {
        if (root == nullptr) return;
        postOrder(root->left);
        postOrder(root->right);
        cout << root->val << " ";
    }
};

int main() {
    cout << "请输入层次顺序：" << endl;
    string s;
    cin >> s; //输入如ABC#D##

    Binary_Tree Tree;
    Tree.buildFromLevelOrder(s);

    cout << "后序遍历是：" << endl;
    Tree.postOrder(Tree.root);

    return 0;
}


//3.由结点信息建树
/*输入一行如 A B C ,表示该结点值为A，它的左孩子是B，右孩子是C*/
#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>
using namespace std;

struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char x) :val(x), left(nullptr), right(nullptr) {}
};

class Binary_Tree {
public:
    TreeNode* root=nullptr;
    unordered_map<char, TreeNode*>nodes;
    unordered_set<char>children;

    void buildTree(int n) {
        for (int i = 0; i < n; i++) {
            char val, left, right;
            cin >> val >> left >> right;

            //未创建该结点
            if (!nodes[val])
                nodes[val] = new TreeNode(val);

            //左子树不为空
            if (left != '#') {
                if (!nodes[left]) nodes[left] = new TreeNode(left); //未创建该结点
                nodes[val]->left = nodes[left]; //链接左孩子
                children.insert(left); //加入children中
            }

            //右子树不为空
            if (right != '#') {
                if (!nodes[right]) nodes[right] = new TreeNode(right); //未创建该结点
                nodes[val]->right = nodes[right]; //链接右孩子
                children.insert(right); //加入children中
            }
        }

        //该结点不是任何结点的子结点
        for (auto& pair : nodes) {
            if (children.find(pair.first) == children.end()) {//未找到就会返回children.end()
                root = pair.second;
                break;
            }
        }
    }

    //后序遍历输出
    void postOrder(TreeNode* root) {
        if (root == nullptr) return;
        postOrder(root->left);
        postOrder(root->right);
        cout << root->val << " ";
    }
};

int main() {
    cout << "请输入结点个数：" << endl;
    int n;
    cin >> n;

    cout << "请输入结点信息：" << endl;
    Binary_Tree Tree;
    Tree.buildTree(n);

    cout << "后序遍历是：" << endl;
    Tree.postOrder(Tree.root);

    return 0;
}
/*输入如
7
A B C
B D E
C # F
D # #
E # #
F G #
G # #
*/
