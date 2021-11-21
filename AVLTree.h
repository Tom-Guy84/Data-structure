//
// Created by Tom Guy on 11/18/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
const int NOT_EXIST = -1;
template <class T>
class AVLTree
{
private:
    class Node
    {
        friend class AVLTree<T>;
        T* value;
        Node* father;
        Node* right_son;
        Node* left_son;
        int height;
        Node* root;
        Node(T* val,Node* father, Node* right_son, Node* left_son, Node* r) : value(val),
            father(father=nullptr), right_son(right_son=nullptr), left_son(left_son=nullptr),
            root(r), height(0){}

        ~Node() {
            father = nullptr;
            right_son = nullptr;
            left_son = nullptr;
            root = nullptr;
            delete value;
            delete *this;
        }

        Node(Node* other) = default;

        bool operator==(Node* other)
        {
            return (*value == *(other->value));
        }

        bool operator<=(Node* other)
        {
            return (*value <= *(other->value));
        }
        friend Node* Tree_Creator_AUX(Node* vertex, int* size, int height);
    };
    Node* root;
    int size;

    template <class S>
    T& find_in_tree(Node* ver, const S& val, Node* loc, Node* father_of_loc)
    {
        if(ver->value == val)
        {
            loc = ver;
            father_of_loc = ver->father;
            return *ver;
        }

        if((!ver->left_son && val <= ver->value) || (!ver->right_son && ver->value <=val))
        {
            loc = nullptr;
            father_of_loc = ver;
            return nullptr;
        }

        if(val <= ver->value)
        {
            return find_in_tree(ver->left_son, val);
        }
        else
        {
            return find_in_tree(ver->right_son, val);
        }
    }

    int getHeight(Node* ver);
    int balance(Node* ver);
    void correctHeight(Node* father, Node* son);
    Node* easyCaseRemove(Node* loc, bool& easy_case);
    void rootCaseRemove();
    Node* swapWithNext(Node* loc);
    void checkForRolls(Node* start);
    void ll_roll(Node* first_ubl);
    void lr_roll(Node* first_ubl);
    void rl_roll(Node* first_ubl);
    void rr_roll(Node* first_ubl);
    void fixFatherAfterRoll(Node* old_son, Node* new_son);
    void inorderHelper(T* values, int index, Node* ver);
    void inorderIn(T* values, int index, Node* ver);
    static friend AVLTree<T>& createEmptyTree(int size);



public:
    AVLTree()
    {
        size = 0;
        root = nullptr;
    }

    AVLTree(const AVLTree<T>& other) = delete; //TODO
    ~AVLTree()
    {
        while (root)
        {
            remove(*root);
        }
    }
    AVLTree& operator=(const AVLTree<T>& other) = delete;

    template <class S>
    T& find(const S& val);

    void insert(const T& val);
    void remove(const T& val);

    T* inorderOut();

    void combineTrees(const AVLTree<T>& to_delete);

};

template<class T>
AVLTree<T>::Node* Tree_Creator_AUX(int* size, int height)
{
    if(*size==-1 || height ==-1 )
    {
        return nullptr;
    }

    AVLTree<T>::Node* Root=new AVLTree<T>::Node();
    Root->father=nullptr;
    (*size)--;
    Root->left_son=Tree_Creator_AUX(size, height - 1);
    Root->right_son=Tree_Creator_AUX( size, height - 1);
    if(Root->left_son!= nullptr)
    Root->left_son->father=Root;
    if(Root->right_son!= nullptr)
    vertex->right_son->father=Root;
    return Root;
}

static AVLTree<T>& createEmptyTree(int size);

template <class T>
int AVLTree<T>::getHeight(Node* ver)
{
    if(!ver)
    {
        return NOT_EXIST;
    }
    return ver->height;
}

template <class T>
int AVLTree<T>::balance(Node* ver)
{
    if (!ver)
    {
        return 0;
    }
    return (ver->getHeight(ver->left_son)-ver->getHeight(ver->right_son));
}

template <class T>
void AVLTree<T>::correctHeight(Node* father, Node* son)
{
    while(father)
    {
        if(father->height < son->height + 1)
        {
            father->height ++;
        }
        else
        {
            break;
        }
        son = father;
        father = temp->father;
    }
}


template <class T>
typename AVLTree<T>::Node*  AVLTree<T>::easyCaseRemove(AVLTree<T>::Node* loc, bool& easy_case)
{
    if(!(loc->right_son || loc->left_son))
    {
        if(loc->value <= loc->father->value)
        {
            loc->father->left_son = nullptr;
        }
        else
        {
            loc->father->right_son = nullptr;
        }
        Node* ver = loc->father;
        delete *loc;
        easy_case = true;
        return ver;
    }

    if(loc->left_son && !loc->right_son)
    {
        if(loc->value <= loc->father->value)
        {
            loc->father->left_son = loc->left_son;
        }
        else
        {
            loc->father->right_son = loc->left_son;
        }
        Node* ver = loc->father;
        delete *loc;
        easy_case = true;
        return ver;
    }

    if(!loc->left_son && loc->right_son)
    {
        if(loc->value <= loc->father->value)
        {
            loc->father->left_son = loc->right_son;
        }
        else
        {
            loc->father->right_son = loc->right_son;
        }
        Node* ver = loc->father;
        delete *loc;
        easy_case = true;
        return ver;
    }
    easy_case = false;
    return nullptr;
}


template <class T>
void AVLTree<T>::rootCaseRemove()
{
    if(!(root->right_son && root->left_son))
    {
        delete *root;
        root = nullptr;
    }
    else if(!(root->right_son) && root->left_son)
    {
        Node* temp = root->left_son;
        delete *root;
        root = temp;
    }
    else if(root->right_son && !(root->left_son))
    {
        Node* temp = root->right_son;
        delete *root;
        root = temp;
    }
    Node* ver = swapWithNext(root);
    correctHeight(ver->father, ver);
    checkForRolls(ver);
}

template <class T>
Node* AVLTree<T>::swapWithNext(Node* loc)
{
    Node* temp = loc->right_son;
    while(temp->left_son)
    {
        temp = temp->left_son;
    }
    T* temp_value = temp->value;
    temp->value = loc->value;
    loc->value = temp_value;
    return temp;
}


template <class T>
void AVLTree<T>::checkForRolls(Node* start)
{
    while(start)
    {
        if(balance(start) > -2 && balance(start) < 2)
        {
            start = start->father;
            continue;
        }
        break;
    }
    if(start)
    {
        switch(getHight(start))
        {
            case 2:
            {
                if (balnace(start->left_son) >= 0)
                {
                    ll_roll(start);
                    return;
                }
                lr_roll(start);
                return;
            }
            case -2:
            {
                if(balance(start->right_son) <= 0)
                {
                    rr_roll(start);
                    return;
                }
                rl_roll(start);
                return;
            }
            default: rr_roll(start);
        }
    }
}

template <class T>
void AVLTree<T>::ll_roll(Node* first_ubl)
{
    Node* temp = first_ubl->left_son;
    first_ubl->left_son = temp->right_son;
    temp->right_son = first_ubl;
    first_ubl->height = max(first_ubl->left_son->height, first_ubl->right_son->height) +1;
    temp->height = max(temp->left_son->height, temp->right_son->height) +1;
    fixFatherAfterRoll(first_ubl, temp);
}

template <class T>
void AVLTree<T>::lr_roll(Node* first_ubl)
{
    Node* son = first_ubl->left_son;
    Node* grandson = son->right_son;
    first_ubl->left_son = grandson->right_son;
    son->right_son = grandson->left_son;
    grandson->left_son = son;
    grandson->right_son = first_ubl;
    first_ubl->height = max(first_ubl->left_son->height, first_ubl->right_son->height) +1;
    son->height = max(son->left_son->height, son->right_son->height) +1;
    grandson->height = max(grandson->left_son->height, grandson->right_son->height) +1;
    fixFatherAfterRoll(first_ubl, grandson);
}


template <class T>
void AVLTree<T>::rl_roll(Node* first_ubl)
{
    Node* son = first_ubl->right_son;
    Node* grandson = son->left_son;
    first_ubl->right_son_son = grandson->left_son;
    son->left_son = grandson->right_son;
    grandson->right_son = son;
    grandson->left_son = first_ubl;
    first_ubl->height = max(first_ubl->left_son->height, first_ubl->right_son->height) +1;
    son->height = max(son->left_son->height, son->right_son->height) +1;
    grandson->height = max(grandson->left_son->height, grandson->right_son->height) +1;
    fixFatherAfterRoll(first_ubl, grandson);
}


template <class T>
void AVLTree<T>::rr_roll(Node* first_ubl)
{
    Node* temp = first_ubl->right_son;
    first_ubl->right_son = temp->left_son;
    temp->left_son = first_ubl;
    first_ubl->height = max(first_ubl->left_son->height, first_ubl->right_son->height);
    temp->height = max(temp->left_son->height, temp->right_son->height);
    fixFatherAfterRoll(first_ubl, temp);
}

template <class T>
void AVLTree<T>::fixFatherAfterRoll(Node* old_son, Node* new_son)
{
    if(old_son == root)
    {
    root = new_son;
    return;
    }
    Node* father = old_son->father;
    old_son == father->left_son ? father->left_son = new_son : father->right_son = new_son;
}

template <class T>
template <class S>
T& AVLTree<T>::find(const S& val)
{
    Node** loc, father_of_loc;
    return find_in_tree(root, val, &loc, &father_of_loc);
}

template <class T>
void AVLTree<T>::insert(const T& val)
{
    Node** loc, father_of_loc;
    if(root == nullptr)
    {
        Node new_node(val);
        *root = new_node;
        size++;
        return;
    }
    if(find_in_tree(root, val, &loc, &father_of_loc))
    {
        throw; //TODO
    }
    Node new_node(val, *father_of_loc);
    if(val <= *father_of_loc->value)
    {
        *father_of_loc->left_son = &new_node;
    }
    else
    {
        *father_of_loc->right_son = &new_node;
    }
    correctHeight(new_node->father, new_node);
    check_for_rolls(new_node);
    size++;
}

template <class T>
void AVLTree<T>::remove(const T& val)
{
    Node** loc, father_of_loc;
    if(!find_in_tree(root, val, &loc, &father_of_loc))
    {
        throw; //TODO
    }
    size--;
    if(*loc == root)
    {
        rootCaseRemove();
        return;
    }
    bool easy_case = false;
    Node* ver = easyCaseRemove(*loc, easy_case);
    if(easy_case)
    {
        correctHeight(ver->height, ver);
        check_for_rolls(ver);
        return;
    }
    ver = swapWithNext(*loc);
    easyCaseRemove(*loc);
    correctHeight(ver->height, ver);
    checkForRolls(ver);
}

template <class T>
T* AVLTree<T>::inorderOut()
{
    if(!root)
        return;
    T* values = new T[size];
    inorderHelper(values, 0, root);
    return values;
}

template <class T>
void AVLTree<T>::inorderHelper(T* values, int index, Node* ver)
{
  if(!ver)
      return;
  inorderHelper(values, i, ver->left_son);
  values[i++] = ver->value; //need to implement a assignment operator for all classes. TODO
  inorderHelper(values, i, ver->right_son);
}

template <class T>
void AVLTree<T>::combineTrees(const AVLTree<T>& to_delete)
{
    T* array_to_insert = this->inorderOut();
    T* array_to_delete = to_delete.inorderOut();
    T* all = new T[this->size + to_delete.size];
    int i = 0, j = 0, k;
    for(k = 0; k < this->size + to_delete.size; k ++)
    {
        if(array_to_delete[j] == array_to_insert[i])
        {
            throw ; //TODO
        }
        if(array_to_insert[i] <= array_to_delete[j])
        {
            all[k] = array_to_insert[i++];
        }
        if(array_to_delete[j] <= array_to_insert[i])
        {
            all[k] = array_to_delete[j++];
        }
    }
    if(i < this->size - 1)
    {
        for(i; i < array_to_insert.size - 1; i++)
        {
            all[k++] = array_to_insert[i];
        }
    }
    if(j < to_delete.size - 1)
    {
        for(j; j < array_to_delete.size - 1; j++)
        {
            all[k++] = array_to_delete[j];
        }
    }
    delete array_to_delete;
    delete array_to_insert;
    AVLTree<T> new_tree = createEmptyTree(to_delete.size + to_insert.size);
    new_tree.inorderIn(all, 0, new_tree.root);
    delete to_delete;
    delete *this;
    *this = new_tree;
}

template <class T>
 AVLTree<T>& createEmptyTree(int size)
{
    AVLTree<T> tree;
    //calculate the height based on size.
    //create the tree, for each conjuction , alloc node, perfferably in recursive way.
    int height=ceil(log2(size+1)) -1 ;
    tree.root= Tree_Creator_AUX<T>(&size,height);
    return tree;

}

template <class T>
void AVLTree<T>::inorderIn(T* values, int index, Node* ver)
{
    if(!ver)
        return;
    inorderHelper(values, i, ver->left_son);
     ver->value=values[i++] ; //need to implement a assignment operator for all classes. TODO
    inorderHelper(values, i, ver->right_son);
}