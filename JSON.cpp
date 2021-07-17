//#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <vector>
#include <map>
using namespace std;
///

map<char, string> scheme;
string code="";
#define MAX_TREE_HT 100

///
std::string readFile1( string filename )   // @JLBorges : direct from stream buffer
{
   std::ifstream file( "data-sample.xml");
   return { istreambuf_iterator<char>(file), {} };
}
class node
    {
    public:

        string tag_value; /// the attributes
        string tag_name;
        string tag_text; /// text content
        vector<node*>child;
       // vector<node*>::iterator itr;
        //node *child[100];
      //  list<node*>child;
    };
node* CreateNode(string value,string name,string text)
    {
        node* newNode = new node();
        newNode->tag_value = value;
        newNode->tag_name =name;
        newNode->tag_text =text;
        return newNode;
    }

string karma;
vector <string>karma_vec;



class Tree
    {
        node *root;
    public:
        Tree()
            {
                root = 0;
            }
        node* getRoot()
            {
                 return root;
            }
        string get_tag_val(node *temp)
            {
                return temp->tag_value;
            }
        string get_tag_name(node *temp)
            {
                return temp->tag_name;
            }
        void Insert(node* root,string tag_val,string tag_nam);
        node* rSearch(node *p, string key);
    };
/*
void Tree::Insert(node* root,string tag_val,string tag_nam) {
   // int index_child =0;
    node* t = root;
    node* p;
    node* r;
    queue<node*> q;
    // root is empty
    if (root == 0){
        cout<<"hello from root"<<endl;
        p = new node;
        p->tag_value= tag_val;
        p->tag_name= tag_nam;
        cout<<"the I value is "<<endl;
        root = p;
        return;
    }
    q.push(root);
    while(!q.empty())
    {      //the root not equal null
       // cout<<" hello Hager "<<endl;
        node* temp = q.front();
        q.pop();
           // if (temp->child.empty()!= 0)
             //   q.push(temp->child);
           // else
             //   {
                 //   cout<<"hello from else "<<endl;
                    temp->child.push_back(CreateNode(tag_val,tag_nam));
                     break;
               // }
    }
}*/
/*node* Tree::rSearch(node *p, string key) {
    cout<<"Hello from rsearch"<<endl;
    if (p == 0){
         cout<<" the root "<<endl;
        return 0;
    }

    if (key == p->tag_name)
        {
        cout<<"A child and it is "<<p->tag_name<<endl;
        return p;
        }
     else {
         for(int i=0;i<p->child.size();i++){

            return rSearch(p->child[i], key);
         }
    }
}
*/
/*struct XmlTree_node
    {
        string tag_name;
        string tag_value;
        list<XmlTree_node*>children;
        XmlTree_node( string name, string value):tag_name(name),tag_value(value)
        {}
        void inser(XmlTree_node * node)
            {
                children.push_back(node);
            }
    };*/
void json(node *root,int level)
    {
          vector<node*>::iterator itr;
      /*  if(level==0)
            {
        //        cout<<"Hello"<<endl;
                cout<<"{"<<endl;
                karma=root->tag_name;
           //     if(root->tag_text!=" ")
                //karma_vec.pop_back();
            }
        else{
                if(karma==root->tag_name)
                    {
                    //    cout<<"hello from child"<<endl;
                        karma_vec.push_back(root->tag_text);
                        for( itr= root->child.begin();itr!= root->child.end();itr++)
                            {
                                json(*itr,level);
                            }
                    }
                    else
                        {
                            karma=root->tag_name;
                            karma_vec.push_back(root->tag_text);
                        }
        }*/
       // cout<<"What if"<<endl;
        for(size_t i=0;i<level;i++)
            {
                cout<<"\t";
            }
        cout<<"\""<<root->tag_name<<"\""<<":";
        if(root->tag_value!=" ")
            {
                cout<<"{"<<"\"#"<<root->tag_value<<",}";
                if(level==3)
                    cout<<" ";
                else{
                    cout<<"["<<endl;
                    for(size_t i=0;i<level;i++)
                    {
                    cout<<"\t";
                    }
                    cout<<"{";
                }
            }
            else
                {
                    if(level==3)
                        cout<<" ";
                    else
                        cout<<"[";
                }
        if(root->tag_text!=" ")
                {
                    cout<<"Hi";
                   // cout<<"[";
                  //  cout<<"Here?"<<endl;
                    if(!karma_vec.empty()){
                            cout<<"WhaAasd"<<endl;
                            cout<<karma_vec.front()<<endl;
                        while(!karma_vec.empty())
                            {
                                cout<<karma_vec.front()<<",";
                                karma_vec.pop_back();
                            }
                        }
                       // cout<<"Wakals"<<endl;
                  //  cout<<"]";
                }
     /*   if (root->child.size()>0){
            cout<<endl;
        }*/
        // vector<node>::iterator it;

        for( itr= root->child.begin();itr!= root->child.end();itr++)
            {
                json(*itr,level+1);
            }
        if (root->child.size()>0)
            for(size_t i=0;i<level;i++)
            {
                    cout<<"\t";
                }
            if(level==3)
                {
                    cout<<endl;
                    return;
                }
        if(level==2)
            cout<<"},"<<endl;
        else
            cout<<"}"<<endl;
    }
int XmlTree_to_text(node*root,int level)
    {

        for(size_t i=0;i<level;i++)
            {
                cout<<"\t";
            }

        cout<<"<"<<root->tag_name<<">"<<root->tag_text<<root->tag_value<<" ";
        if (root->child.size()>0){
            cout<<endl;
        }
        vector<node*>::iterator itr;
        for( itr = root->child.begin();itr!=root->child.end();itr++)
            {
                XmlTree_to_text(*itr,level+1);
            }
        if (root->child.size()>0)
            for(size_t i=0;i<level;i++)
                {
                    cout<<"\t";
                }
        cout<<"</"<<root->tag_name<<">"<<endl;
    }



    ///cut_text
string cut_text(int &i,string file)
    {
       // cout<<"hello from Cut "<<endl;
        string ret;
        int j;
        i--;
        if(file[i]==' '||file[i]=='<')
            {
                return " ";
            }
        for(j=i;j<file.length();j++,i++)
            {
                if (file[j]=='<')
                    {
                        i--;
                        break;
                    }
                ret+=file[j];
            }
        return ret;
    }

string cut(int &i,string file)
    {
       // cout<<"hello from Cut "<<endl;
        string ret;
        int j;
        for(j=i;j<file.length();j++,i++)
            {
                if (file[j]=='>')
                    {
                        i+=2;
                        break;
                    }
                ret+=file[j];
            }
        return ret;
    }
string second_cut(string whole_root)
    {
        string root;
        int j;
        for(j=0;j<whole_root.length();j++)
            {
                if(whole_root[j]==' ')
                    {
                        return root;
                    }
                root+=whole_root[j];
            }
           return root;
    }
string thierd_cut(string whole_root)
    {
        int j,w;
        string value;
        for(j=0;j<whole_root.length();j++)
            {
                if(whole_root[j]==' ')
                    {
                        for(w=j+1;w<whole_root.length();w++)
                            {
                                value+=whole_root[w];
                            }
                        return value;
                    }
            }
            return " ";
    }
int main()
{

    std::string file_content , s1 , s2 , temp1 , temp2;
    string file =readFile1("data-sample.xml");
    int longe =file.length(),i,j,w;
    int flag =0,level=0,num_children=-1,num_children1=-1,num_children2=-1,num_children3=-1;
    int sum_num_children=0,sum_num_children1=0,sum_num_children2=0;
    int coco=0;
    string temp_value,root,whole_root,value,atr;
    Tree Xmll;
    node *Root;


    string temp_tag_name,temp_tag_valu;

   // cout<<"the length is"<<longe<<endl;


    for(i=0;i<=longe;i++)
        {

///        **Root**
            if (i==0)
                {
                  //  XmlTree_node root;
                    int q =i+1;

                        i++;
                        whole_root=cut(i,file);

                            root = second_cut(whole_root);
                            value =thierd_cut(whole_root);
                            atr=cut_text(i,file);

                            Root=CreateNode(value,root,atr);

                            /// now i have the root

                            level=0;



                }



          /*check the opening tag*/

            if(file[i]=='<'&&file[i+1]!='/')
                {
                    i+=1;
                    level++;
///                       **Root childs**
                                if (flag==0)
                                {
                                    num_children++;
                                    flag++;

                                    sum_num_children=sum_num_children+num_children;
                                    sum_num_children1=sum_num_children1+num_children;
                                    sum_num_children2=sum_num_children2+num_children;
                                    num_children1=-1;
                                    num_children2=-1;
                                    whole_root=cut(i,file);
                                    temp_tag_name = second_cut(whole_root);
                                    temp_tag_valu = thierd_cut(whole_root);
                                    atr=cut_text(i,file);
                                    (Root->child).push_back(CreateNode(temp_tag_valu,temp_tag_name,atr));

                                   node *temp=CreateNode(temp_tag_valu,temp_tag_name,atr);

                                        continue;
                                }
///          **the childs of the childs**

                if(flag==1)
                    {

                   flag++;
                   num_children1++;
                   whole_root=cut(i,file);
                   temp_tag_name = second_cut(whole_root);
                   temp_tag_valu = thierd_cut(whole_root);
                   atr=cut_text(i,file);
                   (Root->child[num_children]->child).push_back(CreateNode(temp_tag_valu,temp_tag_name,atr));
                   node *temp=CreateNode(temp_tag_valu,temp_tag_name,atr);
                    num_children2=-1;

                   continue;
                  }
                  if(flag==2)
                    {

                   flag++;
                   num_children2++;
                   whole_root=cut(i,file);
                   temp_tag_name = second_cut(whole_root);
                   temp_tag_valu = thierd_cut(whole_root);
                   atr=cut_text(i,file);
                   (Root->child[num_children]->child[num_children1]->child).push_back(CreateNode(temp_tag_valu,temp_tag_name,atr));
                    node *temp=CreateNode(temp_tag_valu,temp_tag_name,atr);
                    if(temp_tag_name=="frame")
                    {
                        flag--;
                    }
                   continue;
                  }
                  if(flag==3)
                    {
                        flag--;
                        cout<<"Error"<<endl;
                        continue;
                    }
                if(flag==-1)
                    {
                        cout<<"Error45456"<<endl;
                        continue;
                    }
                  // Xmll.Insert(child,temp_tag_valu,temp_tag_name);
                 //  cout<<child.child<<endl;
                /*if(child_name==temp_tag_name)
                    {
                        ///the closing tag of the child
                        level=1;
                        continue;
                    }
                else
                    {
                        /// a new child of the tag
                        level=2;
                        Xmll.Insert(&Root,temp_tag_valu,temp_tag_name);
                    }

          /*  if (temp_tag_name==root)
                {
                    cout<<"The End "<<temp_tag_name<<endl;
                    }*/
            }
    ///            To get the  text content
           /* if(file[i]==' ')
            {
                continue;
            }
            if(file[i]!=' '&&file[i]!='<'&&file[i]!='>'&&file[i]!='/')
                {
                   whole_root=cut_text(i,file);
                   cout<<"the text "<<whole_root<<endl;

                }*/


            /**/




///          **check the closing tag**
           if(file[i]=='<'&&file[i+1]=='/')
                {
                    level--;
                    flag--;
                    //num_children--;
                    //cout<<"hi";
                    //first i will check for the closing tag of the root
                    //*i+=2;
                 //   cot<<
                   // whole_root=cut(i,file);
                   // cout<<"pls?"<<endl;
                    //temp_tag_name = second_cut(whole_root);
                   // temp_tag_valu =thierd_cut(whole_root);
                    //cout<<temp_tag_name<<endl;
                    //node *tempo = Xmll.rSearch(child, temp_tag_name);
//                    child = tempo;
                    //cout<<tempo->tag_name<<endl;
                  //  cout<<tempo->tag_value<<endl;
                    //cout<<temp_tag_name  <<endl;
                    if (temp_tag_name==root)
                        {
                           // cout<<"The End "<<temp_tag_name<<endl;
                        }
                }


        }

  //  driver();

    json(Root,0);
    //XmlTree_to_text(Root,0);

}
