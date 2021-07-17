#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MAX_TREE_HT 100
//#include<QStringRef>
 // QString MainWindow::temp ;
  QString line, temp,str ,format_str,minify_out;
   QString dir;
      int pos1,pos2,pos3,flag_buttom=0;
      QStack <QString> st ;
      QString karma;
      QVector <QString>karma_vec;
      QString temp1 , temp2 , k , source_file ,source_file1,out_string;
      int n = 1000 , i , j , len  ;
      bool Stack_is_empty = 0 , error_occure = 0 ;

QString  MainWindow:: sub( QString s , int start , int end )
      {
         QString result ;
         for( int i = start  ; ( (i <= end) && (i < s.length()) ) ; i++ )
         {
             result += s[i] ;
         }
         return result ;
      }

node*  MainWindow:: CreateNode(QString value,QString name,QString text)
          {
              node* newNode = new node();
              newNode->tag_value = value;
              newNode->tag_name =name;
              newNode->tag_text =text;
              return newNode;
          }
QString  MainWindow:: json(node *root,int level)
    {

        for(size_t i=0;i<level;i++)
            {
             temp2 += "\t";
            }
        temp2 += "\""+root->tag_name+"\""+":{"+"\"@"+root->tag_value+ "}";
        if (root->child.size()>0){
             temp2 += "\n";
        }
        // vector<node>::iterator it;
        QVector<node*>::iterator itr;
        for( itr= root->child.begin();itr!= root->child.end();itr++)
            {
                json(*itr,level+1);
            }
        if (root->child.size()>0)
            for(size_t i=0;i<level;i++)
            {
                     temp2 +="\t";
                }
            if(level==3)
                {
                    temp2 +="\n";
                    return 0;
                }
            temp2 += "}";
            temp2 += "\n";
            return temp2;
    }
QString MainWindow:: cut(int &i,QString file)
{

    QString ret;
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
QString  MainWindow::cut_text(int &i,QString file)
    {
       // cout<<"hello from Cut "<<endl;
        QString ret;
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
QString MainWindow::second_cut(QString whole_root)
    {
        QString root;
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
QString MainWindow::thierd_cut(QString whole_root)
    {
        int j,w;
        QString value;
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
QString MainWindow:: XmlTree_to_text(node*root,int level)
    {

        for(size_t i=0;i<level;i++)
            {
                format_str += "\t";
            }

        format_str += "<"+ root->tag_name +">"+root->tag_text + root->tag_value+ " ";
        if (root->child.size()>0){
            format_str += "\n";
        }
        QVector<node*>::iterator itr;
        for( itr = root->child.begin();itr!=root->child.end();itr++)
            {
                XmlTree_to_text(*itr,level+1);
            }
        if (root->child.size()>0)
            for(size_t i=0;i<level;i++)
                {
                    format_str += "\t";
                }
        format_str += "</" + root->tag_name + ">" + "\n";
        return format_str;
    }

QString MainWindow::termstring(QString s)
{
    int len=s.length();
    int i=0;
    while(i<len && s[len-1]==' ')
    {
        i++;
    }
    while (len>i && s[len-1]==' ')
    {
        len--;
    }

    if(i==len)
    {
        return "";
    }

   QString ss= sub(s,i,len-i);



    return ss;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow:: saveToFile( QString   temp)
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "",tr(" All Files(*.*);;Text File (*.txt);;XML File (*.xml) ;;JOSN File(*.json)"));
    if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadWrite)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }
         // QTextStream out(&file);
            file.write(temp.toUtf8()) ;
          //out.setVersion(QDataStream::Qt_6_1);
            //out <<temp;


               }
           }
void  MainWindow::on_pushButton_2_clicked()//select the file
{
     dir = QFileDialog::getOpenFileName(this,"Open a file",QDir::homePath());
    QFile file (dir);
    if(! file.open(QIODevice::ReadOnly))
                 QMessageBox::information(this,"info",file.errorString());
      QTextStream in (&file);
      //ui->textBrowser_3->setText(in.readAll());
      ui->textBrowser_2->setText(in.readAll());

      //source_file1= file.readAll();
     // qDebug()<<source_file1;
      source_file =in.readAll();
     //QString tt="ana t2bt bgd";

      // saveToFile(in.readAll());

}
QString MainWindow:: minify(){
    temp= "";
    QFile file (dir);
    if(dir== ""){
     QMessageBox::information(this,"info",file.errorString());
    }
    QTextStream in (&file);
     // str= source_file;
    if (file.open(QIODevice::ReadOnly))
       {
          QTextStream in(&file);
           while (!in.atEnd())
           {
              str = in.readLine();
           //  temp+= line;
               line= termstring(str);
             pos1 = line.indexOf("<!--");
             pos2 = line.indexOf("-->");
              //qDebug()<<pos1;

              // pos3 = line.indexOf("</");
               if(pos1 >=0){
                     //line.erase(pos1,(pos2-pos1+1));
                     line.remove(pos1,(pos2-pos1+3));
               }
               for(int i =0 ,j=0;i<line.length();i++)
               {
                   if(line[i]=='\t') continue;
                   if(i== pos1) {
                      continue;}
                   if(line[i]!='!'&& i>=line.indexOf('<')){
                    temp+= str[i]; }
               }

           }



        }
    return temp;
}
void MainWindow::on_pushButton_clicked() //minifiy
{
     minify_out =  minify();
          ui->textBrowser->setLineWrapColumnOrWidth(QTextEdit::NoWrap); // or just '0'

           ui->textBrowser->setText(minify_out);
        flag_buttom=1;

}


void MainWindow::on_pushButton_5_clicked() //reset
{   dir = "";
    source_file= "";
    temp ="";
    ui->textBrowser->clear();
    ui->textBrowser_2 ->clear();
    ui->textBrowser_3->clear();
   // file.close;
}

void MainWindow::on_pushButton_3_clicked() //errors2
{  //QString file_name = QFileDialog::getOpenFileName(this , "open a file" , QDir::homePath()) ;
    //  QMessageBox::information(this,"..",file_name);
      QFile file (dir) ;
      if( !file.open(QFile::ReadOnly | QFile::Text) )
      {
          QMessageBox::warning(this,"title","file not open");
      }
      QTextStream in (&file) ;

      source_file = in.readAll();
               /********************************************/
                   for( i = 0 ; i < source_file.length() ; i++ ){
                           if ( (source_file[i] == '<') && ( (source_file[i+1] == '?') || (source_file[i+1] == '!') ) )
                           {
                               error_occure = 0 ;
                               continue ;
                           }
                           if ( (source_file[i] == '<') && ( ( source_file[i+1] != '?') || ( source_file[i+1] != '!' ) ) )
                           {

                               if( ( source_file[i] == '<') && (source_file[i+1] != '/') )  /*****opening tag****/
                                   {
                                           for( int j = i+1 ; ( source_file[j] != '>' ) ;j++ ){
                                               temp1 += source_file[j] ;
                                           }
                                           /****self closing**/
                                           int temp1_len = temp1.length() ;
                                           if ( temp1[temp1_len - 1] != '/' )
                                           {
                                                       st.push(temp1) ;
                                                       temp1 = "" ;
                                                       continue ;
                                           }
                                           else if ( temp1[temp1_len - 1] == '/' )
                                           {
                                               QString temp1_update = sub( temp1 , 0 , temp1_len - 1 ) ;
                                               temp1_update = "" ;
                                               temp1 = "" ;
                                               error_occure = false ;
                                               continue ;
                                           }

                               }
                               /******/
                               if ( ( source_file[i] == '<' ) && ( source_file[i+1] == '/' ) )    /******closing tag*****/
                                   {
                                           if ( st.isEmpty() )
                                           {

                                   /*********************************************/
                                               error_occure = true ;
                                               break ;
                                           }
                                           else if ( !st.isEmpty() )
                                           {
                                           for( j = i+2 ; source_file[j] != '>' ;j++ ){
                                               temp2 += source_file[j] ;

                                           }
                                           QString k = st.top() , k_update ;
                                           int k_len = k.length() ;
                                                         if( k == temp2 ) {
                                                             temp2 = "" ;
                                                             st.pop() ;
                                                             error_occure = false ;
                                                         }
                                                         if( k != temp2 )
                                                         { //in case opening tag has attribute
                                                              for ( int n = 0 ; n < k_len ; n++ )
                                                               {
                                                                   if( k[n] == ' ' )
                                                                       {
                                                                           k_update = sub( k , 0, n - 1 ) ;
                                                                           if( k_update == temp2 )
                                                                           {
                                                                               st.pop() ;
                                                                               error_occure = false ;
                                                                               k_update = "" ;
                                                                               temp2 = "" ;

                                                                               break ;
                                                                           }
                                                                           if ( k_update != temp2 ) {
                                                                               error_occure = true ;
                                                                               break ;
                                                                           }

                                                                       }
                                                               }
                                                       }
                                                }

                           }
                       }

                   }

                           if (error_occure == false)
                           {
                               if( !st.isEmpty() )
                               {
                                   QMessageBox msgBox;
                                   msgBox.setText("The file has error");
                                   msgBox.exec();
                               }
                               else
                               {
                                   QMessageBox msgBox;
                                   msgBox.setText("The file has no error");
                                   msgBox.exec();
                               }
                           }
                           else if (error_occure == true)
                           {
                               QMessageBox msgBox;
                               msgBox.setText("The file has error");
                               msgBox.exec();

                           }

}

void MainWindow::on_pushButton_7_clicked()
{
}

QString MainWindow::on_pushButton_4_clicked() //Json

{  int flag =0,level=0,num_children=-1,num_children1=-1,num_children2=-1,num_children3=-1;
    int sum_num_children=0,sum_num_children1=0,sum_num_children2=0;
    QString temp_value,root,whole_root,value,atr;
       node *Root;
       QString temp_tag_name,temp_tag_valu;
    // source_file=on_pushButton_clicked();
    //int longe =source_file.length();

          QFile file (dir);
         if (file.open(QIODevice::ReadOnly))
            {
            // qDebug("hellllllllllllllllllllllllllllllo11");
               QTextStream in(&file);
                while (!in.atEnd())
                { //qDebug("hellllllllllllllllllllllllllllllo");
                   source_file1 = in.readAll();
                   source_file= termstring(source_file1);
                     QString tt= minify();
                ui->textBrowser_3->setText(tt);
                // qDebug()<<tt;


                    qDebug()<<tt.length();


         for(i=0;i<tt.length();i++)
                { //qDebug("hellllllllllllllllllllllllllllllo11");

        //*Root*
                    if (i==0)
                        {
                          //  XmlTree_node root;
                            int q =i+1;

                                i++;
                                whole_root=cut(i,source_file);

                                    root = second_cut(whole_root);
                                    value =thierd_cut(whole_root);
                                    atr=cut_text(i,source_file);

                                    Root=CreateNode(value,root,atr);

                                    /// now i have the root

                                    level=0;



                        }



               //check the opening tag/

                    if(source_file[i]=='<'&&source_file[i+1]!='/')
                        {
                            i+=1;
                            level++;
        //  *Root childs*
                                        if (flag==0)
                                        {
                                            num_children++;
                                            flag++;

                                            sum_num_children=sum_num_children+num_children;
                                            sum_num_children1=sum_num_children1+num_children;
                                            sum_num_children2=sum_num_children2+num_children;
                                            num_children1=-1;
                                            num_children2=-1;
                                            whole_root=cut(i,source_file);
                                            temp_tag_name = second_cut(whole_root);
                                            temp_tag_valu = thierd_cut(whole_root);
                                            atr=cut_text(i,source_file);
                                            (Root->child).push_back(CreateNode(temp_tag_valu,temp_tag_name,atr));

                                           node *temp=CreateNode(temp_tag_valu,temp_tag_name,atr);

                                                continue;
                                        }
       //the childs of the childs*

                        if(flag==1)
                            {

                           flag++;
                           num_children1++;
                           whole_root=cut(i,source_file);
                           temp_tag_name = second_cut(whole_root);
                           temp_tag_valu = thierd_cut(whole_root);
                           atr=cut_text(i,source_file);
                           (Root->child[num_children]->child).push_back(CreateNode(temp_tag_valu,temp_tag_name,atr));
                           node *temp=CreateNode(temp_tag_valu,temp_tag_name,atr);
                            num_children2=-1;

                           continue;
                          }
                          if(flag==2)
                            {

                           flag++;
                           num_children2++;
                           whole_root=cut(i,source_file);
                           temp_tag_name = second_cut(whole_root);
                           temp_tag_valu = thierd_cut(whole_root);
                           atr=cut_text(i,source_file);
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
                               // cout<<"Error"<<endl;
                                continue;
                            }
                        if(flag==-1)
                            {
                                //cout<<"Error45456"<<endl;
                                continue;
                            }




                   if(source_file[i]=='<'&&source_file[i+1]=='/')
                        {
                            level--;
                            flag--;


                        }


                } }}}

              QString out =json(Root,0);
            qDebug ()<<out.length();
          ui->textBrowser_3->setText(out);
            flag_buttom =3;

                    return out;

}


QString MainWindow::on_pushButton_6_clicked()  //FORMAT4

{
    QFile file (dir);
   // QTextStream out (&file);
   //qDebug()
    //if(! file.open(QIODevice::ReadOnly))
      // QMessageBox::information(this,"info",file.errorString());int longe =source_file.length();
    int flag =0,level=0,num_children=-1,num_children1=-1,num_children2=-1,num_children3=-1;
    int sum_num_children=0,sum_num_children1=0,sum_num_children2=0;
      QString temp_value,root,whole_root,value,atr;
         node *Root;
         QString temp_tag_name,temp_tag_valu;

             if (file.open(QIODevice::ReadOnly))
                {
                 //qDebug("hellllllllllllllllllllllllllllllo11");
                   QTextStream in(&file);
                    while (!in.atEnd())
                    { //qDebug("hellllllllllllllllllllllllllllllo");
                       source_file1 = in.readAll();
                       source_file= termstring(source_file1);
                         QString tt= minify();
                 //   ui->textBrowser_3->setText(tt);
                    // qDebug()<<tt;


           for(i=0;i<tt.length();i++)
                {
        //*Root*
                    if (i==0)
                        {
                                 //ui->textBrowser_3->setText(out.readAll());

                          //  XmlTree_node root;
                            int q =i+1;
                                i++;
                               // qDebug()<<source_file;
                                whole_root=cut(i,tt);
                                  //qDebug();
                                  // qDebug()<<whole_root;
                                    root = second_cut(whole_root);
                                    //qDebug("helllllllllo");
                                    //qDebug()<<root;
                                    value =thierd_cut(whole_root);
                                    //qDebug()<< value;
                                    atr=cut_text(i,tt);
                                    //qDebug("helllllllllo");
                                    //qDebug()<<atr;
                                    Root=CreateNode(value,root,atr);

                                    /// now i have the root

                                    level=0;



                        }



               //check the opening tag/

                    if(tt[i]=='<'&&tt[i+1]!='/')
                        {
                            i+=1;
                            level++;
        //  *Root childs*
                                        if (flag==0)
                                        {
                                            num_children++;
                                            flag++;

                                            sum_num_children=sum_num_children+num_children;
                                            sum_num_children1=sum_num_children1+num_children;
                                            sum_num_children2=sum_num_children2+num_children;
                                            num_children1=-1;
                                            num_children2=-1;
                                            whole_root=cut(i,tt);
                                            temp_tag_name = second_cut(whole_root);
                                            temp_tag_valu = thierd_cut(whole_root);
                                            atr=cut_text(i,tt);
                                            (Root->child).push_back(CreateNode(temp_tag_valu,temp_tag_name,atr));

                                           node *temp=CreateNode(temp_tag_valu,temp_tag_name,atr);

                                                continue;
                                        }
       //the childs of the childs*

                        if(flag==1)
                            {

                           flag++;
                           num_children1++;
                           whole_root=cut(i,tt);
                           temp_tag_name = second_cut(whole_root);
                           temp_tag_valu = thierd_cut(whole_root);
                           atr=cut_text(i,tt);
                           (Root->child[num_children]->child).push_back(CreateNode(temp_tag_valu,temp_tag_name,atr));
                           node *temp=CreateNode(temp_tag_valu,temp_tag_name,atr);
                            num_children2=-1;

                           continue;
                          }
                          if(flag==2)
                            {

                           flag++;
                           num_children2++;
                           whole_root=cut(i,tt);
                           temp_tag_name = second_cut(whole_root);
                           temp_tag_valu = thierd_cut(whole_root);
                           atr=cut_text(i,tt);
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
                               // cout<<"Error"<<endl;
                                continue;
                            }
                        if(flag==-1)
                            {
                                //cout<<"Error45456"<<endl;
                                continue;
                            }




                   if(tt[i]=='<' && tt[i+1]=='/')
                        {
                            level--;
                            flag--;


                        }


                }
}
                    }
             }
    temp2= XmlTree_to_text(Root,0);
    // qDebug()<<temp2.length();
     qDebug ("helllllo");
      qDebug ()<<temp2;
     flag_buttom =4;
     ui->textBrowser_3->setText(temp2);

     return temp2;
}


void MainWindow::on_save_button_clicked()

{   // QFile file1 (dir);
  //  if(! file1.open(QIODevice::ReadOnly))
   //  QMessageBox::information(this,"info",file1.errorString());
   // QTextStream ss (&file1);
   // qDebug()<<flag;
    if(flag_buttom==1){
       out_string=minify();
       saveToFile(out_string);
    }
    if(flag_buttom==3){
       out_string=on_pushButton_4_clicked();
       saveToFile(out_string);
    }
    if(flag_buttom==4){
       out_string=on_pushButton_6_clicked();
       saveToFile(out_string);
    }
   //QString ha ="fghjvbnmfghjkvbnfghjvbnvbnfghj";




}
void MainWindow::on_format_clicked(){

}
