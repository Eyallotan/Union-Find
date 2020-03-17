//
// Created by eyall on 6/10/2019.
//
#ifndef WET2_UNIONFIND_H
#define WET2_UNIONFIND_H
#include "ReverseTreeNode.h"

template<typename T>
class UnionFind{

public:
    //c'tor & d'tor
    UnionFind(int n);
    ~UnionFind();

    // interface functions:
    ReverseTreeNode<T>* Makeset(int i);
    T* Find(int i);
    T* Union(int p, int q);

private:
    //helper functions:
    void shrinkPaths(ReverseTreeNode<T>* root, int i);
    void unionAux(int big_set, int small_set);

    //properties:
    int num_of_elements;
    ReverseTreeNode<T>** elements;
    typename ReverseTreeNode<T>::GroupInfo** groups;


};

template <typename T>
UnionFind<T>::UnionFind(int n) : num_of_elements(n) , elements(NULL), groups
(NULL) {
    elements = new ReverseTreeNode<T>*[n+1];
    groups= new typename ReverseTreeNode<T>::GroupInfo*[n+1];
    for (int i=0;i<=n;i++){
        elements[i]=NULL;
        groups[i]=NULL;
    }
}

template <typename T>
UnionFind<T>::~UnionFind(){
    for (int i=0;i<=num_of_elements;i++){
        if (elements[i]){
            delete elements[i];
        }
    }
    delete [] elements;
    delete [] groups;
}


template <typename T>
ReverseTreeNode<T>* UnionFind<T>::Makeset(int i) {
    ReverseTreeNode<T>* set= new ReverseTreeNode<T>(i);
    typename ReverseTreeNode<T>::GroupInfo* info=new typename
            ReverseTreeNode<T>::GroupInfo(i,set);
    set->setGroupInfo(info);
    elements[i]=set;
    groups[i]=info;
    return set;
}


template <typename T>
void UnionFind<T>::shrinkPaths(ReverseTreeNode<T> *root, int i) {
    ReverseTreeNode<T>* iterator=elements[i];
    while (iterator!=root){
        ReverseTreeNode<T>* temp=iterator->getParent();
        iterator->setParent(root);
        iterator=temp;
    }
}

template <typename T>
T* UnionFind<T>::Find(int i) {
    if (i<1 || i>num_of_elements){
        return NULL;
    }
    ReverseTreeNode<T>* iterator=elements[i];
    while (iterator->getParent()){ //find root
        iterator=iterator->getParent();
    }
    shrinkPaths(iterator,i);
    //return iterator->getGroupInfo()->getGroupIdentifier();
    return iterator->getData();
}

template <typename T>
void UnionFind<T>::unionAux(int big_set, int small_set) {
    ReverseTreeNode<T>* bigger_root=groups[big_set]->getGroupHead();
    ReverseTreeNode<T>* smaller_root=groups[small_set]->getGroupHead();
    if(bigger_root==smaller_root) return;
    //connect small set root to big set root
    smaller_root->setParent(bigger_root);
    //update union group size
    groups[big_set]->incrementGroupSize(groups[small_set]->getGroupSize());
    //update small group info
    groups[small_set]=groups[big_set];
    delete smaller_root->getGroupInfo();
    smaller_root->setGroupInfo(NULL);

}

template <typename T>
T* UnionFind<T>::Union(int p, int q) {
    if (q<1 || p<1 || q>num_of_elements || p>num_of_elements){
        return NULL;
}
    int size_p=groups[p]->getGroupSize();
    int size_q=groups[q]->getGroupSize();
    if (size_p>=size_q){
        unionAux(p,q);
        return groups[p]->getGroupHead()->getData();
    }
    else {
        unionAux(q,p);
        return groups[q]->getGroupHead()->getData();
    }
}








#endif //WET2_UNIONFIND_H
