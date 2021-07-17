#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QQueue>
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include<QTextStream>
#include<QMessageBox>
#include<QString>
#include<QStack>
#include<QDir>
#include<QChar>
#include <QVector>
#include <QMap>
#include <cstdlib>
#include <QSaveFile>
class node
    {
    public:

        QString tag_value; /// the attributes
        QString tag_name;
        QString tag_text; /// text content
        QVector<node*>child;
       // vector<node*>::iterator itr;
        //node *child[100];
      //  list<node*>child;
    };
class Tree
    {
        node *root;
    public:
        Tree()
            {
                root = 0;
            }

 /*
void Insert(node* root,QString tag_val,QString tag_nam) {
   // int index_child =0;
    node* t = root;
    node* p;
    node* r;
    QQueue<node*> q;
    // root is empty
    if (root == 0){
        //cout<<"hello from root"<<endl;
        p = new node;
        p->tag_value= tag_val;
        p->tag_name= tag_nam;
        //cout<<"the I value is "<<endl;
        root = p;
        return;
    }
    q.push_back(root);
    while(!q.empty())
    {      //the root not equal null
       // cout<<" hello Hager "<<endl;
        node* temp = q.front();
        q.pop_front();
           // if (temp->child.empty()!= 0)
             //   q.push(temp->child);
           // else
             //   {
                 //   cout<<"hello from else "<<endl;
                    temp->child.push_back(CreateNode(tag_val,tag_nam));
                     break;
               // }
    }*/
   /* node Search(node *p, string key) {
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
    }*/
};
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString termstring(QString s);
    QString sub( QString s , int start , int end );
    void swapMinHeapNode(struct MinHeapNode** a,struct MinHeapNode** b);
     void minHeapify(struct MinHeap* minHeap, int idx);
     int isSizeOne(struct MinHeap* minHeap);
     void insertMinHeap(struct MinHeap* minHeap,struct MinHeapNode* minHeapNode);
     void buildMinHeap(struct MinHeap* minHeap);
     int isLeaf(struct MinHeapNode* root);
     void  printCodes(struct MinHeapNode* root, int arr[], int top);
     struct  MinHeap* createAndBuildMinHeap(QChar data[], int freq[], int size){};
     void HuffmanCodes(QChar data[], int freq[], int size);
     void decode(QString file,QMap<QChar, QString> scheme_code) ;
     struct MinHeapNode* newNode(QChar data, unsigned freq){};
     node* CreateNode(QString value,QString name,QString text);
     QString  json(node *root,int level);
     QString cut_text(int &i,QString file);
     QString cut(int &i,QString file);
     QString second_cut(QString whole_root);
     QString thierd_cut(QString whole_root);
     QString XmlTree_to_text(node*root,int level);
      void  saveToFile(QString temp);
       QString  minify();

private slots:
    void on_pushButton_clicked();

    void  on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

   QString on_pushButton_4_clicked();

    QString on_pushButton_6_clicked();

    void on_Format_clicked();

    void on_save_button_clicked();

       void on_format_clicked();
private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
