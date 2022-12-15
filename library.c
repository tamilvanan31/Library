#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

typedef struct nodebook{
  char book[20];
  struct nodebook* next;
}BOOK;

typedef struct node{
  char* studentname;
  int rollno;
  BOOK* books;
  struct node* left,*right;
}TREE;

typedef struct nodelist{
  char* bookname;
  char* author;
  int reference;
  struct nodelist* next;
}NODE;

typedef NODE* LIST;

LIST makeNode(char* bookname,char* author,int reference)
{
  LIST temp = NULL;
  temp = (LIST)malloc(sizeof(NODE));
  temp->bookname=(char *)malloc(sizeof(char)*strlen(bookname));
  temp->author=(char *)malloc(sizeof(char)*strlen(author));
  temp->bookname = strcpy(temp->bookname,bookname);
  temp->author = strcpy(temp->author,author);
  temp->reference = reference;
  temp->next = NULL;
  return temp;
}

TREE* makenodetree(char* name,int rollno,BOOK* bk)
{
  TREE* temp = NULL;
  temp = (TREE* )malloc(sizeof(TREE));
  temp->studentname = (char *)malloc(sizeof(char)*strlen(name));
  temp->studentname  = strcpy(temp->studentname,name);
  temp->rollno = rollno;
  temp->books = bk;
  temp->left = temp->right = NULL;
  return temp;
}

BOOK* makeBook(char* b)
{
  BOOK* t=malloc(sizeof(BOOK));
  strcpy(t->book,b);
  t->next=NULL;
  return t;
}

BOOK* insertbook(BOOK* b,char* book)
{
 if(!b) return makeBook(book);
 BOOK* temp = b;
 while(temp->next)
 {
   temp = temp->next;
 }
 temp->next = makeBook(book);
 return b;
}

TREE* inserttree(TREE* t,char* stdname,int rollno,BOOK* book)
{
  if(!t) return makenodetree(stdname,rollno,book);
  if(rollno < t->rollno)
  {
    t->left = inserttree(t->left,stdname,rollno,book);
  }
  else if(rollno > t->rollno)
  {
    t->right = inserttree(t->right,stdname,rollno,book);
  }
  return t;
}

LIST insert(LIST l,char* bookname,char* author,int reference)
{
  if(!l) return makeNode(bookname,author,reference);
  LIST temp = l;
  while(temp->next)
  {
    temp = temp->next;
  }
  temp->next = makeNode(bookname,author,reference);
  return l;
}

int search(LIST l,char *name)
{
  if(!l)
  {
    return 0;
  }
  while(l)
  {
    if(strcmp(l->bookname,name)==0)
      {
        return 1;
      }
       l=l->next;
    }
    return 0;
}

int searchrollno(TREE* t,int rollno)
{
    if(!t) return 0;
    if( t->rollno == rollno)
      {
        return 1;
      }
    if(t->rollno < rollno)
      {
        return searchrollno(t->right,rollno);
      }
      if(t->rollno > rollno)
        {
          return searchrollno(t->left,rollno);
        }
      //  return 0;
}
void display(LIST l)
{
  static int i;
  if(l)
  {
    printf("\n\t(%d)\n\tBook Name        : %s\n\tAuthor Name      : %s\n\tReference Number : %d\n",i+1,l->bookname,l->author,l->reference);
    i++;
    display(l->next);
  }
}

void displaybook(BOOK* b)
{
  while(b)
  {
    printf("\nBook : %s\n",b->book);
    b = b->next;
  }
}

void inorder(TREE* t)
{
  if(t)
  {
    inorder(t->left);
    printf("\nName : %s \nRollNo : 201850%d\n",t->studentname,t->rollno);
    inorder(t->right);
  }
}

void swap(LIST a, LIST b)
{
    int temp = a->reference;
    a->reference = b->reference;
    b->reference = temp;
}

void bubbleSort(LIST start)
{

    int swapped, i;
    LIST ptr1;
    LIST lptr = NULL;
    if (start == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = start;
        while (ptr1->next != lptr)
        {

            if (ptr1->reference > ptr1->next->reference)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

int search_book(BOOK* b,char* bookname)
{
   if(!b) return 0;
   while(b)
   {
     if(strcmp(b->book,bookname) == 0)
         return 1;
     b = b->next;
   }
   return 0;
}

TREE* search_tree(TREE* t,int rollno)
{
  if(t == NULL || t->rollno)
  {
    return t;
  }
  if(t->rollno < rollno)
   return search_tree(t->right,rollno);
  if(t->rollno > rollno)
   return search_tree(t->left,rollno);
}

void delete_book(BOOK** b,char* bookname)
{
  BOOK* temp = *b,*prev;
  if(temp != NULL && strcmp(temp->book,bookname) == 0)
  {
    *b = temp->next;
    free(temp);
    return ;
  }
  while(temp != NULL && strcmp(temp->book,bookname) != 0)
  {
    prev = temp;
    temp = temp->next;
  }
    if(temp == NULL) return ;
    prev->next = temp->next;
    free(temp);
}

TREE* delete_book_ll(TREE* t,char* bookname,int rollno)
{
  if(!t) return NULL;
  if(rollno == t->rollno)
  {
    BOOK* temp = t->books;
    while(temp)
    {
      if(search_book(temp,bookname))
      {
         delete_book(&temp,bookname);
      }
      else
      {
           temp = temp->next;
      }
    }
  }
  if(rollno < t->rollno)
    delete_book_ll(t->left,bookname,rollno);
  if(rollno > t->rollno)
    delete_book_ll(t->right,bookname,rollno);
  return t;
}

TREE* min(TREE* t)
{
  while(t->left != NULL)
  {
    t = t->left;
  }
  return t;
}

 void help()
 {
   printf("\nEnter choice is to enter valid choice...\nchoice 1 is to list the available books...\nchoice 2 is to display the stock in sorted order...\nchoice 3 is Register in the library...\nchoice 4 is to display borrowed books from the library...\nchoice 5 is to return a book...\nchoice 7 is to end the program...\n");
 }

int main()
{
  printf("\n\t\t\t\t\t\t\t\t****LIBRARY****\n");
  TREE* t1 = NULL;
  TREE* t2 = NULL;
  LIST l1 = NULL;
  BOOK* tb = NULL;
  char name[20],bookname[100];
  static int roll = 1;
  LIST ll = NULL;
  int rollno,ch,i,number,ref;
  ll = insert(ll,"The_Red_sari","Javier_Moro",120);
  ll = insert(ll,"Freedom_in_exile","Dalai_lama",135);
  ll = insert(ll,"Farishta","Kapil_Isapuari",104);
  ll = insert(ll,"God_of_Antartica","Master_Yashwardhan",360);
  ll = insert(ll,"I_do_what_I_do","Dr.Raghuram_Rajan",369);
  ll = insert(ll,"Hit_Refresh","Satya_Gidla",369);
  ll = insert(ll,"The_Turbulent_Years","Pranab_Mukerji",369);
  ll = insert(ll,"Early_Indians","Tony_Joseph",359);
  ll = insert(ll,"Exam_Warriors","Mr.Narendra_Modi",249);
  ll = insert(ll,"Why_I_am_a_Hindu?","Shashi_Nadella",239);
  ll = insert(ll,"Walden","Henry_David_Thoreua",869);
  ll = insert(ll,"The_Discovery_Of_India","Jawaharlal_Nehru",242);
  ll = insert(ll,"A_Wasted_Hour","Jeffrey_Archer",322);
  ll = insert(ll,"Two_Lives","Vikram_Seth",331);
  ll = insert(ll,"Geetanjali","Rabindranath_Tagore",404);
  ll = insert(ll,"The_Symposium","Plato",656);
  A:
  printf("\n\tEnter your choice...\n\t1.List available Books...\n\t2.Sort the stock by Reference Number...\n\t3.Register...\n\t4.Display the registerd students...\n\t5.Display Borrowed books...\n\t6.Return book...\n\t7.Help\n\t8.Terminate\n        $=>");
  scanf("%d",&ch);
  switch(ch)
  {
    case 1 :  display(ll);
              break;
    case 2 :  bubbleSort(ll);
              display(ll);
              break;

     case 3 :
                printf("\nEnter the student name...");
                scanf("%s",name);
                printf("\nEnter the last four digits of your Roll number...");
                scanf("%d",&rollno);
                df :
                printf("\nEnter the number of books...");
                scanf("%d",&number);
                if(number < 5)
                {
                  for(i=0;i<number;i++)
                  {
                    H:
                    printf("\nEnter the bookname...");
                    scanf("%s",bookname);
                    if(search(ll,bookname))
                    {
                      tb = insertbook(tb,bookname);
                    }
                    else
                    {
                      printf("\nThis book is not in library,try another....");
                      goto H;
                    }
                  }
                  t1 = inserttree(t1,name,rollno,tb);
                }
                else
                {
                  printf("\nYou can't take more than 5 books...");
                  goto df;
                }
               break;
     case 4 :   inorder(t1);
                break;
     case 5:    printf("\nBorrowed books from library...");
                 displaybook(tb);
                 printf("\n");
                 break;
     case 6 : printf("\nEnter the Roll Number...");
              scanf("%d",&rollno);
              if(searchrollno(t1,rollno))
              {
                Hbk :
                printf("\nEnter the name of the book...");
                scanf("%s",bookname);
                if(search_book(tb,bookname))
                {

                  t1 = delete_book_ll(t1,bookname,rollno);
                  printf("\nThe books you have are...\n");
                  displaybook(tb);
                  printf("\n%s",tb->next);
                }
                else
                {
                  printf("\nYou haven't taken that book,enter correctly...");
                  goto Hbk;
                }
              }
              break;
     case 7 : help();
              break;
     case 8 : exit(0);
              break;
    default:
            printf("\nEnter valid choice...");
            break;
  }
        goto A;
  return 0;
}
