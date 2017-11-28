#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cstring>

using namespace std;

struct node{
public:
    unsigned int weight;
    unsigned char elem;
    node(){
        this->elem = '\0';
        this ->weight = 0;
    }
    node(unsigned  char elem,unsigned int weight){
        this->elem = elem;
        this->weight = weight;
    }
};

class treenode{
public:
    unsigned int weight = 0;
    unsigned char elem;
    treenode *left = nullptr;
    treenode *right = nullptr;
    treenode(unsigned int weight,treenode* left,treenode* right){
        this->elem = '\0';
        this->weight = weight;
        this->right = right;
        this->left = left;
    }
    treenode(unsigned  char elem,unsigned int weight){
        this->elem = elem;
        this->weight = weight;
    }
    treenode(){
        this->elem = '\0';
        this ->weight = 0;
        this->right = nullptr;
        this->left = nullptr;
    }
    bool isleave(){
        return (left == nullptr) &&  (right == nullptr);
    }
    void reset(){
        weight = 0;
        elem = '\0';
        left = nullptr;
        right = nullptr;
    }
};

void sort(vector<treenode> &array,int len){
    int i = 0;
    int j =0;
    for(i =0 ; i<len; i++){
        for(j = len-1  ;j > i;j-- ){
            if(array[j].weight < array[j-1].weight){
                treenode temp = array[j];
                array[j] = array[j-1];
                array[j-1] = temp;
            }
        }
    }

}

void build(treenode &root, char *str, int deep,string strArray[]){
    if(root.isleave()){
        strArray[root.elem] = str;
    }
    str[deep] = '0';
    if(root.left != nullptr){
        build(*root.left,str,deep+1,strArray);
    }
    str[deep] = '1';
    if(root.right != nullptr){
        build(*root.right,str,deep+1,strArray);
    }
    str[deep] = 0;
}

void HuffTree (vector<treenode> & vecValidNumberArray){
    treenode temp;
    while(vecValidNumberArray.size() != 1){
        sort(vecValidNumberArray,vecValidNumberArray.size());
        temp.reset();
        temp.weight = vecValidNumberArray[0].weight + vecValidNumberArray[1].weight;
        temp.left = new treenode();
        *temp.left = vecValidNumberArray[0];
        temp.right = new treenode();
        *temp.right = vecValidNumberArray[1];
        vecValidNumberArray.erase(vecValidNumberArray.begin());
        vecValidNumberArray[0] = temp;
    }
}


void pressTxt(string file)
{
    int roadlen = file.length();
    int i = roadlen;
    while(file[i-1] != '\\'){
        i--;
    }
    int j = i;
    ifstream infile;
    infile.open(file.data());   //将文件流对象与文件连接起来
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行

    char c;
    infile >> noskipws;
    int len = 0;
    vector<treenode>array;
    vector<node> nodeArray;
    while (!infile.eof())
    {
        c = infile.get();
        if(c =='\377')
            break;
        for(i = 0; i < len ;i++){
            if(array[i].elem == c){
                array[i].weight++;
                nodeArray[i].weight++;
                break;
            }
        }
        if(i == len){
            treenode  *temp = new treenode(c,1);
            node *nodeTemp = new node(c,1);
            array.push_back(*temp);
            nodeArray.push_back(*nodeTemp);
            len++;
            }
    }
    infile.close();
    string strArray[256];
    char str[256];
    HuffTree(array);             //建树
    build(array[0],str,0,strArray); //存节点的huffman编码
    string outfile = file.substr(0,j-1);
    string name = "2.txt";
    // cin>> "print your file name :">>name;
    outfile = outfile + "\\"+name ;
    ofstream ofile(outfile.data(), ios::binary);   //将文件流对象与文件连接起来;
    assert(ofile.is_open());   //若失败,则输出错误消息,并终止程序运行
    while(nodeArray.size() != 0){
        node nodetemp = nodeArray[nodeArray.size()-1];
        nodeArray.pop_back();
        ofile.write((char*)(&nodetemp), sizeof(nodetemp));
    }
    c = '\0';
    ofile.write((&c), sizeof(c));
    ofile.close();


    ofstream oufile(outfile.data(), ios::binary|ios::app);   //将文件流对象与文件连接起来;
    assert(oufile.is_open());   //若失败,则输出错误消息,并终止程序运行
    infile.open(file.data());
    assert(infile.is_open());
    infile >> noskipws;
    string stringWrite;
    while (!infile.eof()){
        c = infile.get();
        string temp = strArray[c];
        stringWrite += temp;
    }
    //cout <<stringWrite<<endl;
    infile.close();

    int size=(int)stringWrite.size();
    oufile.write((char *)(&size), sizeof(size));
    int less = size % 8;
    for(j =0 ; j<=size;j+=8){
        unsigned  char charWrite = '0';
        if(j+8 > size){
            i =0;
            while(j+i < size){
                char charTemp =stringWrite[j+i];
                if(charTemp == '0'){
                    charWrite<<=1;
                }else if(charTemp == '1'){
                    charWrite<<=1;
                    charWrite|=1;
                }
                i++;
            }
            charWrite<<=(8-less);
        }else{
            for( i =0;i<8;i++){
                char charTemp =stringWrite[j+i];
                if(charTemp == '0'){
                    charWrite<<=1;
                }else if(charTemp == '1'){
                    charWrite<<=1;
                    charWrite|=1;
                }
            }
        }

        oufile.write((char*)(&charWrite), sizeof(charWrite));
    }
     oufile.close();

}

void compress() {
    cout << "Please input source file name(size less than 4GB):";
    string file = "D:\\a.txt";
    //  cin >> file;
    pressTxt(file);

}

void depressTxt(string file)
{
    int roadlen = file.length();
    int i = roadlen;
    while(file[i-1] != '\\'){
        i--;
    }
    int j = i;
    ifstream infile;
    infile.open(file.data(),ios::binary);   //将文件流对象与文件连接起来
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行
    vector<node> nodeArray;
    while(!infile.eof()){

        node nodeTemp ;
        infile.read((char *)(&nodeTemp), sizeof(node));
        nodeArray.push_back(nodeTemp);
        if(infile.peek() == '\0')
            break;
    }
    char temp1;
    infile.get(temp1);
    int strSize;
    infile.read((char *)(&strSize), sizeof(strSize));
    vector<treenode> tree;
    while(nodeArray.size() !=0){
        treenode *temp = new treenode();
        temp->weight = nodeArray[nodeArray.size()-1].weight;
        temp->elem = nodeArray[nodeArray.size()-1].elem;
        tree.push_back(*temp);
        nodeArray.pop_back();
    }

    HuffTree(tree);             //建树
    treenode *ptree = &tree[0];
    unsigned char c;
    string outfile = file.substr(0,j-1);
    string name = "3.txt";
    // cin>> "print your file name :">>name;
    outfile = outfile + "\\"+name ;
    ofstream ofile(outfile.data());   //将文件流对象与文件连接起来;
    assert(ofile.is_open());   //若失败,则输出错误消息,并终止程序运行
    j =0;
    while(j< strSize){
        c = infile.get();
        for( i =0;i<8;i++){
            unsigned char temp ;
            temp = c&128;
            c<<=1;
            if(temp == 128){
                ptree =ptree->right;
            }else if(temp == 0){
                ptree = ptree->left;
            }
            if(ptree->isleave()){
                ofile << ptree->elem;
                ptree = &tree[0];
            }
            j++;
            if(j>= strSize)
                break;
        }


    }
    infile.close();
    ofile.close();
}

void decompress(){
    cout << "Please input source file name(size less than 4GB):";
    string file = "D:\\2.txt";
    //  cin >> file;
    depressTxt(file);
}

void toDo(){
    cout <<endl;
    cout << "1.Huffman compress." << endl;
    cout << "2.Huffman decompress."<<endl;
    cout << "3.Exit."<<endl;
    cout << "Please select :";
    int get;
    cin >> get ;
    if(get == 1){
        compress();
    }else if(get == 2){
        decompress();
    }else if(get == 3){
        exit(0);
    }
    toDo();


}

int main() {
    toDo();
    return 0;

}
