
//
// Created by Tom Guy on 11/18/2021.
//
#include <cmath>
#include <cstdio>
#include <exception>

#ifndef AVLTREE_H_
#define AVLTREE_H_

namespace wet1_dast
{

    const int NOT_EXIST = -1;

    template<class T>
    class AVLTree
    {

    private:
        class Node
        {
            friend class AVLTree<T>;

            T *value;
            Node *father;
            Node *right_son;
            Node *left_son;
            int height;

            explicit Node(T *val = nullptr, Node *father = nullptr) : value(val), father(father), right_son(nullptr),
                                                                      left_son(nullptr),
                                                                      height(0)
            {
                left_son=nullptr;
                right_son=nullptr;
            }
            ~Node()
            {

                father = nullptr;
                right_son = nullptr;
                left_son = nullptr;
                delete value;
//                delete this;
            }

            bool operator==(Node *other)
            {
                return (*value == *(other->value));
            }

            bool operator<=(Node *other)
            {
                return (*value <= *(other->value));
            }

            void Tree_Creator_AUX(int *size_of_tree, int height_of_tree);
        };

        Node *root; //belongs to AVLTree
        int size;
       //@param loc and father_of_loc are getting changed in this function according to the situaton.
       //@ver - the current vertex we are looking at.
       //@val - the value we are looking for.

        T *find_in_tree(Node *ver, const T &val, Node **loc, Node **father_of_loc)
        {
            if (*(ver->value) == val) //if we're in the location
            {
                //problem here.
                //valgrind says loc isn't inited.
                *loc = ver; // mark this as the location.
                *father_of_loc = ver->father;//mark father.
                return (ver->value); // return us the value.
            }
            //if left son doesn't exist , and the value we look for is lesser than the current vertex(meaning he doesn't;t exist in the tree according ot convention)
            //or alternatively ,right son doesn't exist and the current value we're looking for is larger than the current vertex value(meaning we want to go right according to convention,meaning he doesn't exist).
            if ((!ver->left_son && val <= *(ver->value)) || (!ver->right_son && *(ver->value) <= val))
            {

                *loc = nullptr; //the place doesn't exist.
                 *father_of_loc = ver; //mark him as his father.
                return nullptr; //return nullptr,we couldn't find him
            }

            if (val <= *(ver->value)) //if the value we are looking for is lesser than the current vertex ,go left.
            {
                return find_in_tree(ver->left_son, val, loc, father_of_loc);
            } else
            {
                //else go right,because he's larger than him.
                return find_in_tree(ver->right_son, val, loc, father_of_loc);
            }
        }

        int getHeight(Node *ver);
        int balance(Node *ver);

        void correctHeight(Node *ver);

        Node *easyCaseRemove(Node *loc, bool &easy_case);

        void rootCaseRemove();

        Node *swapWithNext(Node *loc);

        void checkForRolls(Node *start);

        void ll_roll(Node *first_ubl);

        void lr_roll(Node *first_ubl);

        void rl_roll(Node *first_ubl);

        void rr_roll(Node *first_ubl);

        void fixFatherAfterRoll(Node *old_son, Node *new_son);

        void inorderHelper(T *values, int index, Node *ver);

        void inorderIn(T *values, int index, Node *ver);

        void createEmptyTree(int size_of_tree);


    public:
        friend void combineTrees(AVLTree<T>& to_insert, AVLTree<T> &to_delete)
        {
            T* array_to_insert = (to_insert.inorderOut());
            T* array_to_delete = (to_delete.inorderOut());
            T * all_players = new T[to_insert.size + to_delete.size];
//         T** all_players = &all;
            int i = 0, j = 0, k;
            for (k = 0; k < to_insert.size + to_delete.size; k++)
            {
                if (to_insert.size - 1 == i || to_delete.size - 1 == j) break;
                if ((array_to_delete[j]) == (array_to_insert[i]))
                {
                    throw AVLTree<T>::ItemInBothTrees();
                }
                if ((array_to_insert[i]) <= (array_to_delete[j]))
                {
                    T temp=array_to_insert[i];
                    all_players[k] = temp;
//                array_to_insert[i] = nullptr;
                    i++;
                }
                if ((array_to_delete[j]) <= (array_to_insert[i]))
                {
                    T temp= array_to_delete[j];
                    all_players[k] = temp;
//                array_to_delete[j] = nullptr;
                    j++;
                }
            }
            for (; i < to_insert.size - 1; i++)
            { //array_to_insert.size
                all_players[k++] = array_to_insert[i];
//            array_to_insert[i] = nullptr;

            }
            for (; j < to_delete.size - 1; j++)
            { //array_to_delete.size
                all_players[k++] = array_to_delete[j];
//            array_to_delete[j] = nullptr;
            }
            int temp_size=to_insert.size;
            delete &to_insert;
            AVLTree<T> new_tree;
            new_tree.createEmptyTree(to_insert.size); //create tree in size of To_delete.size+this->size.
            new_tree.inorderIn(array_to_insert, 0, new_tree.root); //inserts inorder all player;
            to_insert.createEmptyTree(temp_size + to_delete.size);
            to_insert.inorderIn(all_players,0,to_insert.root);
            to_delete.inorderIn(array_to_delete, 0, to_delete.root);//inserts to in order.
            delete array_to_delete;
            delete array_to_insert;
            delete &to_delete;
            delete &new_tree;
        }
        int getSize() const;
        AVLTree() : size(0)
        {
            root=nullptr;
        }

        AVLTree(const AVLTree<T> &other) = delete; //TODO
        ~AVLTree() //todo
        {

            while (root!=nullptr)
            {
                remove(*(root->value));
            }
        }

        AVLTree &operator=(const AVLTree<T> &other) = delete;

        T *find(const T &val);

        void insert(T &val);

        void remove(const T &val);

        T *inorderOut() ;


        class exceptions : public std::exception
        {
        };

        class ItemExist : public exceptions
        {
        };

        class ItemNotExist : public exceptions
        {
        };

        class ItemInBothTrees : public exceptions
        {
        public:
            const char *what() const noexcept override
            {
                return "The same item is in both trees";
            }
        };

        T *findClosest(const T &value); // return thr closest from below to the value in the tree

    };
    static int max(int a, int b);

    template<class T>
    void AVLTree<T>::Node::Tree_Creator_AUX(int *size_of_tree, int height_of_tree)
    {
        if (*size_of_tree == -1 || height_of_tree == -1)
        {
            return;
        }
        father = nullptr;
        value = nullptr;
        (*size_of_tree)--;
        left_son->AVLTree<T>::Node::Tree_Creator_AUX(size_of_tree, height_of_tree - 1);
        right_son->AVLTree<T>::Node::Tree_Creator_AUX(size_of_tree, height_of_tree - 1);
        if (left_son != nullptr)
            left_son->father = this;
        if (right_son != nullptr)
            right_son->father = this;
    }

    template<class T>
    void AVLTree<T>::createEmptyTree(int size_of_tree)
    {
        //calculate the height based on size.
        //create the tree, for each conjunction , alloc node, perfferably in recursive way.
        int height_of_new_tree = (int) ceil(log2(size_of_tree + 1)) - 1;
        root->Tree_Creator_AUX(&size_of_tree, height_of_new_tree);
    }

    template<class T>
    int AVLTree<T>::getHeight(Node *ver)
    {
        return (!ver) ? NOT_EXIST : ver->height;
    }

    template<class T>
    int AVLTree<T>::balance(Node *ver)
    {
        if (!ver)
        {
            return 0;
        }
        return (this->getHeight(ver->left_son) - this->getHeight(ver->right_son));
    }

    template<class T>
    void AVLTree<T>::correctHeight(Node *ver)
    {
        while (ver)
        {
            ver->height = max(getHeight(ver->right_son), getHeight(ver->left_son)) + 1;
            ver = ver->father;
        }
    }


    template<class T>
    typename AVLTree<T>::Node *AVLTree<T>::easyCaseRemove(AVLTree<T>::Node *loc, bool &easy_case)
    {
        if (!(loc->right_son || loc->left_son))
        {
            if (loc->value <= loc->father->value)
            {
                loc->father->left_son = nullptr;
            } else
            {
                loc->father->right_son = nullptr;
            }
            Node *ver = loc->father;
            delete loc;
            easy_case = true;
            return ver;
        }

        if (loc->left_son && !loc->right_son)
        {
            if (loc->value <= loc->father->value)
            {
                loc->father->left_son = loc->left_son;
            } else
            {
                loc->father->right_son = loc->left_son;
            }
            Node *ver = loc->father;
            delete loc;
            easy_case = true;
            return ver;
        }

        if (!loc->left_son && loc->right_son)
        {
            if (loc->value <= loc->father->value)
            {
                loc->father->left_son = loc->right_son;
            } else
            {
                loc->father->right_son = loc->right_son;
            }
            Node *ver = loc->father;
            delete loc;
            easy_case = true;
            return ver;
        }
        easy_case = false;
        return nullptr;
    }


    template<class T>
    void AVLTree<T>::rootCaseRemove()
    {
        if (!(root->right_son) && !(root->left_son))
        {
            delete root;
            root = nullptr;
            return;
        } else if (!(root->right_son) && root->left_son)
        {
            Node *temp = root->left_son;
            delete root;
            root = temp;
        } else if (root->right_son && !(root->left_son))
        {
            Node *temp = root->right_son;
            delete root;
            root = temp;
        }
        Node *ver = swapWithNext(root);
        correctHeight(ver);
        checkForRolls(ver);
    }

    template<class T>
    typename AVLTree<T>::Node *AVLTree<T>::swapWithNext(Node *loc)
    {
        Node *temp = loc->right_son;
        while (temp->left_son)
        {
            temp = temp->left_son;
        }
        T *temp_value = temp->value;
        temp->value = loc->value;
        loc->value = temp_value;
        return temp;
    }


    template<class T>
    void AVLTree<T>::checkForRolls(Node *start)
    {
        while (start)
        {
            if (balance(start) > -2 && balance(start) < 2)
            {
                start = start->father;
                continue;
            } else
            {
                switch (getHeight(start))
                {
                    case 2:
                    {
                        if (balance(start->left_son) >= 0)
                        {
                            ll_roll(start);
                            return;
                        }
                        lr_roll(start);
                        return;
                    }
                    case -2:
                    {
                        if (balance(start->right_son) <= 0)
                        {
                            rr_roll(start);
                            return;
                        }
                        rl_roll(start);
                        return;
                    }
                    default:
                        rr_roll(start);
                }
            }
        }
    }

    static int max(int a, int b)
    {
        return (a >= b) ? a : b;
    }

    template<class T>
    void AVLTree<T>::ll_roll(Node *first_ubl)
    {
        //todo
        Node *temp = first_ubl->left_son;
        first_ubl->left_son = temp->right_son;
        temp->right_son = first_ubl;
        first_ubl->height = max(first_ubl->left_son->height, first_ubl->right_son->height) + 1;
        temp->height = max(temp->left_son->height, temp->right_son->height) + 1;
        fixFatherAfterRoll(first_ubl, temp);
    }

    template<class T>
    void AVLTree<T>::lr_roll(Node *first_ubl)
    {
        //todo
        Node *son = first_ubl->left_son;
        Node *grandson = son->right_son;
        first_ubl->left_son = grandson->right_son;
        son->right_son = grandson->left_son;
        grandson->left_son = son;
        grandson->right_son = first_ubl;
        first_ubl->height = max(first_ubl->left_son->height, first_ubl->right_son->height) + 1;
        son->height = max(son->left_son->height, son->right_son->height) + 1;
        grandson->height = max(grandson->left_son->height, grandson->right_son->height) + 1;
        fixFatherAfterRoll(first_ubl, grandson);
    }


    template<class T>
    void AVLTree<T>::rl_roll(Node *first_ubl)
    {
        //todo
        Node *son = first_ubl->right_son;
        Node *grandson = son->left_son;
        first_ubl->right_son = grandson->left_son;
        son->left_son = grandson->right_son;
        grandson->right_son = son;
        grandson->left_son = first_ubl;
        first_ubl->height = max(first_ubl->left_son->height, first_ubl->right_son->height) + 1;
        son->height = max(son->left_son->height, son->right_son->height) + 1;
        grandson->height = max(grandson->left_son->height, grandson->right_son->height) + 1;
        fixFatherAfterRoll(first_ubl, grandson);
    }


    template<class T>
    void AVLTree<T>::rr_roll(Node *first_ubl)
    {
        //todo
        Node *temp = first_ubl->right_son;
        first_ubl->right_son = temp->left_son;
        temp->left_son = first_ubl;
        first_ubl->height = max(first_ubl->left_son->height, first_ubl->right_son->height);
        temp->height = max(temp->left_son->height, temp->right_son->height);
        fixFatherAfterRoll(first_ubl, temp);
    }

    template<class T>
    void AVLTree<T>::fixFatherAfterRoll(Node *old_son, Node *new_son)
    {
        if (old_son == root)
        {
            root = new_son;
            return;
        }
        Node *father = old_son->father;
        old_son == father->left_son ? father->left_son = new_son : father->right_son = new_son;
    }

    template<class T>
    T *AVLTree<T>::find(const T &val)
    {
        if(root==nullptr) //if root is nullptr whats the point in checking the whole tree.
        {
            return nullptr;
        }
        Node **loc=new Node*();
        Node **father_of_loc=new Node*();
        T* to_return= find_in_tree(root, val, loc, father_of_loc);
        delete loc;
        delete father_of_loc;
        return to_return;
    }

    template<class T>
    void AVLTree<T>::insert(T &val)
    {

        if (root == nullptr)
        {
            root = new Node(&val);
            size++;
            return;
        }
        Node **loc=new Node*();
        Node **father_of_loc=new Node*();
        if (find_in_tree(root, val, loc, father_of_loc))
        {
            delete loc;
            delete father_of_loc;
            throw ItemExist();
        }
//        Node new_node(&val, *father_of_loc);
        if (val <= *((*father_of_loc)->value))
        {
            (*father_of_loc)->left_son =new Node(&val,*father_of_loc);
            correctHeight((*father_of_loc)->left_son);
            checkForRolls((*father_of_loc)->left_son);
        } else
        {
            (*father_of_loc)->right_son = new Node(&val,*father_of_loc);
            correctHeight((*father_of_loc)->right_son);
            checkForRolls((*father_of_loc)->right_son);
        }
        size++;
        delete loc;
        delete father_of_loc;

    }

    template<class T>
    void AVLTree<T>::remove(const T &val)
    {
        Node **loc=new Node*();
                Node **father_of_loc=new Node*();
        if (!find_in_tree(root, val, loc, father_of_loc))
        {
            delete loc;
            delete father_of_loc;
            throw ItemNotExist();
        }
        size--;
        if (*loc == root)
        {
            delete loc;
            delete father_of_loc;
            rootCaseRemove();
            return;
        }
        bool easy_case = false;
        Node *ver = easyCaseRemove(*loc, easy_case);
        if (easy_case)
        {
            correctHeight(ver);
            checkForRolls(ver);
            delete loc;
            delete father_of_loc;
            return;
        }
        ver = swapWithNext(*loc);
        easyCaseRemove(*loc, easy_case);
        correctHeight(ver);
        checkForRolls(ver);
        delete loc;
        delete father_of_loc;
    }

    template<class T>
    T *AVLTree<T>::inorderOut()   //todo
    {
        if (!root)
            return nullptr;
        T *values = new T[size];
        inorderHelper(values, 0, root);
        return values;
    }

    template<class T>
    void AVLTree<T>::inorderHelper(T *values, int index, Node *ver)
    {
        if (!ver)
            return;
        inorderHelper(values, index, ver->left_son);
        values[index++] = *(ver->value); //need to implement an assignment operator for class Player
        inorderHelper(values, index, ver->right_son);
    }

//    template<class T>
//    void combineTrees(AVLTree<T>& to_insert, AVLTree<T> &to_delete)
//    {
//         T* array_to_insert = (to_insert->inorderOut());
//         T* array_to_delete = (to_delete.inorderOut());
//         T * all_players = new T[to_insert.size + to_delete.size];
////         T** all_players = &all;
//        int i = 0, j = 0, k;
//        for (k = 0; k < to_insert.size + to_delete.size; k++)
//        {
//            if (to_insert.size - 1 == i || to_delete.size - 1 == j) break;
//            if ((array_to_delete[j]) == (array_to_insert[i]))
//            {
//                throw AVLTree<T>::ItemInBothTrees();
//            }
//            if ((array_to_insert[i]) <= (array_to_delete[j]))
//            {
//                T temp=array_to_insert[i];
//                all_players[k] = temp;
////                array_to_insert[i] = nullptr;
//                i++;
//            }
//            if ((array_to_delete[j]) <= (array_to_insert[i]))
//            {
//                T temp= array_to_delete[j];
//                all_players[k] = temp;
////                array_to_delete[j] = nullptr;
//                j++;
//            }
//        }
//        for (; i < to_insert.size - 1; i++)
//        { //array_to_insert.size
//            all_players[k++] = array_to_insert[i];
////            array_to_insert[i] = nullptr;
//
//        }
//        for (; j < to_delete.size - 1; j++)
//        { //array_to_delete.size
//            all_players[k++] = array_to_delete[j];
////            array_to_delete[j] = nullptr;
//        }
//        int size=to_insert.size;
//        delete &to_insert;
//        AVLTree<T> new_tree;
//        new_tree.createEmptyTree(to_insert.size); //create tree in size of To_delete.size+this->size.
//        new_tree.inorderIn(array_to_insert, 0, new_tree.root); //inserts inorder all player;
//        to_insert.createEmptyTree(size+to_delete.size);
//        to_insert.inorderIn(all_players,0,to_insert.root);
//        to_delete.inorderIn(array_to_delete, 0, to_delete.root);//inserts to in order.
//        delete array_to_delete;
//        delete array_to_insert;
//        delete &to_delete;
//        delete &new_tree;
//    }


    template<class T>
    void AVLTree<T>::inorderIn(T *values, int index, Node *ver)
    {
        if (!ver)
            return;
        inorderIn(values, index, ver->left_son);
        ver->value = &(values[index++]); //need to implement a assignment operator for Player. TODO
        inorderIn(values, index, ver->right_son);
    }

    template<class T>
    T *AVLTree<T>::findClosest(const T &value)
    {
        if (*(root->value) == value)
        {
            return nullptr;
        }
        //needs to be initialized.
        Node **loc=new Node*();
        Node **father_of_loc=new Node*();
        find_in_tree(root, value, loc, father_of_loc);
        if ((*loc)->right_son)
        {
            return (*loc)->right_son->value;
        }
        if (*father_of_loc)
        {
            return (*father_of_loc)->value;
        }
        return nullptr;
    }

    template<class T>
    int AVLTree<T>::getSize() const{
        return size;
    }
}


#endif // AVLTREE_H_