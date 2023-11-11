#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <cstdio>
#include <algorithm>

#define SIZE 3240

using namespace std;



class Node {
   public:
  int datekey;
  int volumekey;
  Node *left;
  Node *right;
  int height;
};

// Calculate height
int height(Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

// New node creation
Node *newNode(int date, int volume) {
  Node *node = new Node();
  node->datekey = date;
  node->volumekey = volume;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Rotate right
Node *rightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left),height(y->right)) +1;
  x->height = max(height(x->left),height(x->right)) +1;
  return x;
}

// Rotate left
Node *leftRotate(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left),height(x->right)) +1;
  y->height = max(height(y->left),height(y->right)) +1;
  return y;
}

// Get the balance factor of each node
int getBalance(Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) -height(N->right);
}

// Insert a node
Node *insertNode(Node *node, int date, int volume) {
  // Find the correct postion and insert the node
  if (node == NULL)
    return (newNode(date, volume));
  if (date < node->datekey)
    node->left = insertNode(node->left, date, volume);
  else if (date > node->datekey)
    node->right = insertNode(node->right, date, volume);
  else
    return node;

  // Update the balance factor of each node and
  // balance the tree
  node->height = 1 + max(height(node->left),height(node->right));
  int balanceFactor = getBalance(node);
  if (balanceFactor > 1) {
    if (date < node->left->datekey) {
      return rightRotate(node);
    } else if (date > node->left->datekey) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1) {
    if (date > node->right->datekey) {
      return leftRotate(node);
    } else if (date < node->right->datekey) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}

Node* search( Node* node, int key)
{
    if(node!=NULL)
    {
        if(key < node->datekey)
            node->left = search(node->left,key);
        else if(key > node->datekey)
            node->right = search(node->right,key);
        else
        return node;
    }

  return node;
}

Node * minValueNode(Node* node)
{
    Node* current = node;
    while (current->left != NULL)
           current = current->left;

    return current;
}

Node* deleteNode(Node* node,int key)
{
      if(node==NULL)
          return node;
      if(key<node->datekey)
          node->left=deleteNode(node->left,key);
      else if(key>node->datekey)
          node->right=deleteNode(node->right,key);
      else
      {
          if( (node->left == NULL) ||(node->right == NULL) )
          {
               Node *temp = node->left ? node->left : node->right;
               if (temp == NULL)
               {
                   temp = node;
                   node = NULL;
               } else *node=*temp;
               free(temp);
          } else
          {
              Node* temp=minValueNode(node->right);
              node->datekey=temp->datekey;
              node->right=deleteNode(node->right,temp->datekey);
          }
      }

      if (node==NULL) return node;

      node->height = 1 +max(height(node->left),height(node->right));

      int balance=getBalance(node);

      if(balance > 1)
      {
          if(getBalance(node->left) >= 0)
          {
              return rightRotate(node);
          }else
          {
              node->left = leftRotate(node->left);
              return rightRotate(node);
          }
      }

      if(balance < -1)
      {
          if(getBalance(node->right) <= 0)
          {
              return leftRotate(node);
          }else
          {
              node->right = rightRotate(node->right);
              return leftRotate(node);
          }
      }

  return node;
}

void changeVolume(Node* node, int date, int vol)
{
    if(node!=NULL)
    {
        if(date < node->datekey)
            node->left = search(node->left,date);
        else if(date > node->datekey)
            node->right = search(node->right,date);
        else
        {
            node->volumekey = vol;
        }
    }
}

void inorder(Node *t)
{
    if(t == NULL)
        return;
    inorder(t->left);
    cout << t->datekey << " ";
    inorder(t->right);
}

int main()
{
    Node *root = NULL;
    string str, line, vol, tempstr, con;
    int i = 0, j = 0;
    int tempint, selection, loops;
    string sDATES[SIZE];
    string sVOLUMES[SIZE];
    int intDATES[SIZE];
    int intVOLUMES[SIZE];

    for(i=1;i<=SIZE;i++)
    {
        intDATES[i] = 0;
        intVOLUMES[i] = 0;
        sDATES[i] = "0";
        sVOLUMES[i] = "0";
    }

    ifstream file;

    file.open("agn.us.txt");
    if(!file.is_open())
    {
        cout <<"Cannot find file \nProgram will now exit\n";
        system("pause");
        exit(1);
    }

    if(file.good())
    {
            i = 1;
            j = 1;
            file.ignore(256,'n');
            while(getline(file,line))
            {
                getline(file,str,',');
                sDATES[i] = str;
                i++;
                getline(file,str,',');
                getline(file,str,',');
                getline(file,str,',');
                getline(file,str,',');
                getline(file,vol,',');
                sVOLUMES[j] = vol;
                j++;
            }
    }

    file.close();

    for(i = 1; i<SIZE; i++)
    {
        tempstr = sDATES[i];
        tempstr.erase(remove(tempstr.begin(),tempstr.end(),'-'),tempstr.end());
        tempint = stoi(tempstr);
        intDATES[i] = tempint;
    }

    for(i = 1; i<SIZE; i++)
    {
        tempstr = sVOLUMES[i];
        tempint = stoi(tempstr);
        intVOLUMES[i] = tempint;
    }

    for(i = 1; i<=SIZE; i++)
    {
        root = insertNode(root,intDATES[i], intVOLUMES[i]);
    }

cout << "The AVL tree has been made. Please select one of the following options to continue with the program.\n";
    cout << "(1)->Display the AVL tree inOrder, (2)->Search for a particular volume recorded at a certain date, (3)->Change the volume recorded at a certain date, (4)->Delete the record of a certain date, (5)->Exit the program.\n";
    cout << "If your selection is different to numbers 1,2,3,4 or 5 the program will automatically exit.\n";
    cin >> selection;

    if(selection < 1 || selection > 5)
    {
        cout <<"Wrong number input. \nProgram will now exit.\n";
        system("pause");
        exit(1);
    }

    loops = 1;
    while(loops)
    {
        switch(selection)
        {
        case 1:
            cout << "You selected option 1.In-Order traversal of the tree. \n";
            inorder(root);
            cout << endl;
            if(loops == 1)
            {
                cout << "Do you want to continue using the program?(Answer YES or NO) ";
                cin >> con;
                if(con == "NO")
                {
                    loops = 0;
                }
            }
            break;
        case 2:
        {
            cout << "You have selected option 2.Search and print the volume at a given date. \n";
            string tempdate, temp;
            int idate;
            cout << "Insert date to search for(In YYYYMMDD or YYYY-MM-DD form,from 20050103 to 20171110): ";
            cin >> tempdate;

            temp = tempdate;
            tempdate.erase(remove(tempdate.begin(),tempdate.end(),'-'),tempdate.end());
            idate = stoi(tempdate);

            if (idate < 20050103 || idate > 20171110)
            {
                cout<<"\nDate not found,program will now exit.\n";
                system("pause");
                exit(1);
            }

            Node* foundnode = search(root,idate);
            cout << "The volume at " << temp << " is: " << foundnode->volumekey << endl;

            if(loops == 1)
            {
                cout << "Do you want to continue using the program?(Answer YES or NO) ";
                cin >> con;
                if(con == "NO")
                {
                    loops = 0;
                }
            }
        }
            break;
        case 3:
        {
            cout << "You selected option 3.Change the volume of a given date.\n";
            string tempdate, temp;
            int idate, givenvol;
            cout << "Insert date to search for(In YYYYMMDD or YYYY-MM-DD form,from 20050103 to 20171110): ";
            cin >> tempdate;

            temp = tempdate;
            tempdate.erase(remove(tempdate.begin(),tempdate.end(),'-'),tempdate.end());
            idate = stoi(tempdate);

            if (idate < 20050103 || idate > 20171110)
            {
                cout<<"\nDate not found,program will now exit.\n";
                system("pause");
                exit(1);
            }

            cout << "Give the new volume for the given date: ";
            cin >> givenvol;

            changeVolume(root, idate, givenvol);
            cout << "The volume of the date " << temp << " has been changed to: "  << givenvol << endl;

            if(loops == 1)
            {
                cout << "Do you want to continue using the program?(Answer YES or NO) ";
                cin >> con;
                if(con == "NO")
                {
                    loops = 0;
                }
            }
        }

            break;
        case 4:
        {
            cout << "You have selected option 4.Delete a particular date from the tree.\n";
            string tempdate, temp;
            int idate;
            cout << "Insert date to search for(In YYYYMMDD or YYYY-MM-DD form,from 20050103 to 20171110): ";
            cin >> tempdate;

            temp = tempdate;
            tempdate.erase(remove(tempdate.begin(),tempdate.end(),'-'),tempdate.end());
            idate = stoi(tempdate);

            if (idate < 20050103 || idate > 20171110)
            {
                cout<<"\nDate not found,program will now exit.\n";
                system("pause");
                exit(1);
            }

            deleteNode(root,idate);\
            cout << "The date: " << temp << " has been deleted from the tree.\n";

            if(loops == 1)
            {
                cout << "Do you want to continue using the program?(Answer YES or NO) ";
                cin >> con;
                if(con == "NO")
                {
                    loops = 0;
                }
            }
        }
            break;
        case 5:
            cout <<"You choose to exit the program. \nProgram will now exit.\n";
            system("pause");
            exit(1);
            break;
        }
    }

    return 0;
}
