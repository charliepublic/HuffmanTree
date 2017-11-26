#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

class node{
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


void readTxt(string file)
{
    int roadlen = file.length();
    int i = roadlen;
    while(file[i-1] != '\\'){
        i--;
    }
    string outfile = file.substr(0,i-1);
    string name = "2.txt";
   // cin>> "print your file name :">>name;
    outfile = outfile + name ;
    ifstream infile;
    infile.open(file.data());   //将文件流对象与文件连接起来
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行
    ofstream ofile(outfile.data());   //将文件流对象与文件连接起来;
    assert(ofile.is_open());   //若失败,则输出错误消息,并终止程序运行
    char c;
    infile >> noskipws;
    int len = 0;
    vector<treenode>array;
    vector<node> nodeArray;
    while (!infile.eof())
    {
        infile>>c;
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
    build(array[0],str,0,strArray);

    infile.open(file.data());
    assert(infile.is_open());
    infile.clear();
    infile.seekg(0);
    infile.close();             //关闭文件输入流
    ofile.close();

}


void compress() {
    cout << "Please input source file name(size less than 4GB):";
    string file = "D:\\a.txt";
  //  cin >> file;
    readTxt(file);
}

void decompress(){

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
    }else{
        toDo();
    }

}

int main() {
    toDo();
    return 0;

}
