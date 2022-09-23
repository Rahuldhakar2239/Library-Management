#include<fstream>
#include<iostream>
#include<iomanip>
#include<string.h>
using namespace std;

class Library
{
 int BookId;
 float Price;
 int Pages;
char Author[20];
char Title[20];
char Category[20];

 public:
  //Accessor Functions
 int getID(){return BookId;}
  char* getTitle(){return Title;}
  char* getAuthor(){return Author;}
  char* getCategory(){return Category;}
  float getPrice(){return Price;}

  //Default constructor
 Library()
  {
   BookId=0;
   strcpy(Title,"");
   strcpy(Author,"");
   strcpy(Category,"");
  Pages=0;
   Price=0;
 }

 void getBook();
 void listView();
 void showBook();
 void header();
}l;

void Library::getBook()
{
 cout<<"\tEnter Book Id : ";
 cin>>BookId;
 cout<<"\tEnter Book Title : ";
 cin.get();
 cin.getline(Title,20);
 cout<<"\tEnter Book Author: ";
 cin.getline(Author,20);
 cout<<"\tEnter Book Category: ";
 cin.getline(Category,20);
 cout<<"\tEnter No. of Pages : ";
 cin>>Pages;
 cout<<"\tEnter Price of Book: ";
 cin>>Price;
 cout<<endl;
}

//For displaying all the details of book.
void Library::showBook()
{
 cout<<endl;
 cout<<"Book ID      : "<<BookId<<endl;
 cout<<"Book Title   : "<<Title<<endl;
 cout<<"Author Name  : "<<Author<<endl;
 cout<<"Category     : "<<Category<<endl;
 cout<<"No. of Pages : "<<Pages<<endl;
 cout<<"Price of Book: "<<Price<<endl;
}

//For displaying header
void Library::header()
{
 cout.setf(ios::left);
 cout<<setw(5)<<"I.D."
  <<setw(20)<<"Book Title"
  <<setw(20)<<"Book Author"
  <<setw(15)<<"Category"
  <<setw(6)<<"Pages"
  <<setw(6)<<"Price"<<endl;
 for(int i=1;i<=72;i++)
  cout<<"=";
 cout<<endl;
}

//For displaying in the tabular form
void Library::listView()
{
 cout.setf(ios::left);
 cout<<setw(5)<<BookId
  <<setw(20)<<Title
  <<setw(20)<<Author
  <<setw(15)<<Category
  <<setw(6)<<Pages
  <<setw(6)<<Price<<endl;
}

//Function prototyping for project
void drawLine(char);//Function for drawing line on screen.
void heading();  //Function for heading
void menu();  //Function for displaying program options.
void searchMenu(); //Function for displaying searching options.
void addBook();  //Function for writing data to file.
void displayBooks();//Function for reading data from file.
//Function for searching data from file.
void searchByID();
void searchByTitle();
void searchByCategory();
void searchByPrice();
void searchByAuthor();
void dispose();  //Function to shift books from main file to other file.
void modify();  //Function to modify the book details.
void displayDisposed();//Function to display the list of disposed off books

// Global Functions Definitions

//for drawing line
void drawLine(char ch)
{
 for(int i=1;i<120;i++)
  cout<<ch;
 cout<<endl;
}

void heading()
{
 cout<<"\n\t\t\t\tL I B R A R Y   M A N A G E M E N T   S Y S T E M\n";
 drawLine('*');
}

//Function for adding new book in file.
void addBook()
{
 ofstream fout;
 fout.open("book.dat",ios::app);
 l.getBook();
 fout.write((char*)&l,sizeof(l));
 cout<<"Book data saved in file...\n";
 fout.close();
}

//for reading data from file.
void displayBooks()
{
 ifstream fin("book.dat");
 int rec=0;
 while(fin.read((char*)&l,sizeof(l)))
 {
  if(rec<1)
   l.header();
  l.listView();
  rec++;
 }
 fin.close();
 cout<<"\nTotal "<<rec<<" Records in file...\n";
}

//for searching data from file.
void searchByID()
{
 int n,flag=0;
 ifstream fin("book.dat");
 cout<<"Enter Book ID : ";
 cin>>n;
 while(fin.read((char*)&l,sizeof(l)))
 {
  if(n==l.getID())
  {
   l.showBook();
   flag++;
  }
 }
 fin.close();
 if(flag==0)
  cout<<"Book Number with ID:"<<n<<" not available...\n";
}

// for searching data from file.
void searchByTitle()
{
 int flag=0;
 char title[20];
 ifstream fin("book.dat");
 cout<<"Enter Book Title : ";
 cin.ignore();
 cin.getline(title,20);
 while(fin.read((char*)&l,sizeof(l)))
 {
  if(strcmpi(title,l.getTitle())==0)
  {
   l.showBook();
   flag++;
  }
 }
 fin.close();
 if(flag==0)
  cout<<"Book with Title: "<<title<<" not available...\n";
}

//Fx for searching data from file.
void searchByCategory()
{
 int flag=0,rec=0;
 char cat[20];
 ifstream fin("book.dat");
 cout<<"Enter Book Category : ";
 cin.ignore();
 cin.getline(cat,20);
 while(fin.read((char*)&l,sizeof(l)))
 {
  if(strcmpi(cat,l.getCategory())==0)
  {
   if(rec<1)
    l.header();
   l.listView();
   flag++;
   rec++;
  }
 }
 fin.close();
 if(flag==0)
  cout<<"Book with Category: "<<cat<<" not available...\n";
}

//for searching data from file.
void searchByAuthor()
{
 int flag=0,rec=0;
 char aut[20];
 ifstream fin("book.dat");
 cout<<"Enter Book Author : ";
 cin.ignore();
 cin.getline(aut,20);
 while(fin.read((char*)&l,sizeof(l)))
 {
  if(strcmpi(aut,l.getAuthor())==0)
  {
   if(rec<1)
    l.header();
   l.listView();
   flag++;
   rec++;
  }
 }
 fin.close();
 if(flag==0)
  cout<<"Book with Author name: "<<aut<<" not available...\n";
}

//for searching data from file.
void searchByPrice()
{
 int flag=0,rec=0;
 float minrate, maxrate;
 ifstream fin("book.dat");
 cout<<"Enter Minimum Price of Book : ";
 cin>>minrate;
 cout<<"Enter Maximum Price of Book : ";
 cin>>maxrate;

 while(fin.read((char*)&l,sizeof(l)))
 {
  if(l.getPrice()>=minrate && l.getPrice()<=maxrate)
  {
   if(rec<1)
    l.header();
   l.listView();
   flag++;
   rec++;
  }
 }
 fin.close();
 if(flag==0)
  cout<<"Books between Price Range: "<<minrate
      <<" and "<<maxrate<<" not available...\n";
}

//for shifting books from main file to dispose file.
void dispose()
{
 int n,flag=0;
 ifstream fin("book.dat");
 ofstream fout("dispose.dat",ios::out);
 cout<<"Enter Book ID : ";
 cin>>n;
 while(fin.read((char*)&l,sizeof(l)))
 {
  if(n==l.getID())
  {
   l.showBook();
   flag++;
  }
  else
  {
   fout.write((char*)&l,sizeof(l));
  }
 }
 fin.close();
 fout.close();
 if(flag==0)
  cout<<"Book Number with ID:"<<n<<" not available...\n";
}

// for modifying data in file.
void modify()
{
 int n,flag=0,pos;
 fstream fin("book.dat",ios::in|ios::out);
 cout<<"Enter Book ID : ";
 cin>>n;
 while(fin.read((char*)&l,sizeof(l)))
 {
  if(n==l.getID())
  {
   pos=fin.tellg();
   cout<<"Following data will be edited...\n";
   l.showBook();
   flag++;
   fin.seekg(pos-sizeof(l));
   l.getBook();
   fin.write((char*)&l,sizeof(l));
   cout<<"\nData Modified successfully...\n";
  }
 }
 fin.close();
 if(flag==0)
  cout<<"Book Number with ID:"<<n<<" not available...\n";
}

//to display the list of disposed off books
void displayDisposed()
{
 ifstream fin("disposes.dat");
 int rec=0;
 while(fin.read((char*)&l,sizeof(l)))
 {
  if(rec<1)
   l.header();
  l.listView();
  rec++;
 }
 fin.close();
 cout<<"\nTotal "<<rec<<" Records in disposed off file...\n";
}

//for displaying program options.
void menu()
{
 int ch;
 do
 {
  system("cls");
  heading();
  cout<<"0. EXIT.\n";
  cout<<"1. Add New Book\n";
  cout<<"2. Display All Books\n";
  cout<<"3. Search Books\n";
  cout<<"4. Disposed Off Books\n";
  cout<<"5. Modify Details\n";
  cout<<"6. List of Disposed Books\n";
  cout<<"Enter Your Choice : ";
  cin>>ch;
  system("cls");
  heading();
  switch(ch)
  {
   case 1: system("COLOR 5E"); addBook(); break;
   case 2: system("COLOR 5F"); displayBooks(); break;
   case 3: system("COLOR 6E"); searchMenu(); break;
   case 4: system("COLOR 6F"); dispose(); break;
   case 5: system("COLOR 4E"); modify(); break;
   case 6: system("COLOR 4F"); displayDisposed(); break;
  }
  system("pause");
 }while(ch!=0);
}

void searchMenu()
{
 int ch;
 do
 {
  system("cls");
  heading();
  cout<<"BOOK SEARCH OPTIONS\n";
  cout<<"0. Back\n";
  cout<<"1. By ID\n";
  cout<<"2. By Title\n";
  cout<<"3. By Category\n";
  cout<<"4. By Author\n";
  cout<<"5. By Price Range\n";
  cout<<"Enter Your Choice : ";
  cin>>ch;
  system("cls");
  heading();
  switch(ch)
  {
   case 1: system("COLOR 6E"); searchByID(); break;
   case 2: system("COLOR 4E"); searchByTitle(); break;
   case 3: system("COLOR 6F"); searchByCategory(); break;



   case 4: system("COLOR 5F"); searchByAuthor(); break;
   case 5: system("COLOR 6F"); searchByPrice();break;
   default: cout<<"\a";
  }
  system("pause");
 }while(ch!=0);
}

int main()
{
 system("COLOR 60");
 menu();
 return 0;
}
