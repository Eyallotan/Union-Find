//
// Created by eyall on 6/9/2019.
//
#ifndef WET2_REVERSETREENODE_H
#define WET2_REVERSETREENODE_H
#include <iostream>

template<typename T>
class ReverseTreeNode {
public:
    class GroupInfo {
    public:
        //c'tors & d'tor
        GroupInfo() = default;
        GroupInfo(int group_identifier ,ReverseTreeNode<T>* group_head);
        ~GroupInfo() = default;

        //helper functions:
        int getGroupSize();
        int getGroupIdentifier();
        void incrementGroupSize(int delta);
        ReverseTreeNode<T>* getGroupHead();
        void setGroupHead(ReverseTreeNode<T>*);

    private:
        //properties:
        int group_size;
        int group_identifier;
        ReverseTreeNode<T>* group_head;
    };

    //c'tors & d'tor
    ReverseTreeNode() = default;
    ReverseTreeNode(int key);
    ~ReverseTreeNode();
    //ReverseTreeNode(const ReverseTreeNode<T>& copy);

    //helper functions:
    int getKey();
    T* getData();
    void setData(T* data);
    ReverseTreeNode<T>* getParent();
    void setParent(ReverseTreeNode<T>*);
    GroupInfo* getGroupInfo();
    void setGroupInfo(GroupInfo*);

private:
    //properties:
    int key;
    T* data;
    GroupInfo* group_info;
    ReverseTreeNode<T>* parent;
};

////Reverse Tree Functions////

template <typename T>
ReverseTreeNode<T>::ReverseTreeNode(int key) :
key(key), data(NULL), group_info(NULL), parent(NULL) {}

template <typename T>
ReverseTreeNode<T>::~ReverseTreeNode() {
    if (group_info){
        group_info->setGroupHead(NULL);
        delete group_info;
    }
    delete data;
}

template <typename T>
int ReverseTreeNode<T>::getKey() {
    return key;
}

template <typename T>
T* ReverseTreeNode<T>::getData() {
    return data;
}

template <typename T>
void ReverseTreeNode<T>::setData(T* new_data) {
    data=new_data;
}

template <typename T>
void ReverseTreeNode<T>::setParent(ReverseTreeNode<T>* new_parent) {
    parent=new_parent;
}

template <typename T>
ReverseTreeNode<T>* ReverseTreeNode<T>::getParent() {
    return parent;
}

template <typename T>
typename ReverseTreeNode<T>::GroupInfo* ReverseTreeNode<T>::getGroupInfo() {
    return group_info;
}

template <typename T>
void ReverseTreeNode<T>::setGroupInfo(ReverseTreeNode<T>::GroupInfo*
new_group_info) {
    group_info=new_group_info;
}

//////GroupInfo functios//////

template <typename T>
ReverseTreeNode<T>::GroupInfo::GroupInfo(int group_identifier,
        ReverseTreeNode<T>*group_head) : group_size(1),
group_identifier(group_identifier), group_head(group_head) {}


template <typename T>
int ReverseTreeNode<T>::GroupInfo::getGroupSize() {
    return group_size;
}

template <typename T>
int ReverseTreeNode<T>::GroupInfo::getGroupIdentifier() {
    return group_identifier;
}

template <typename T>
void ReverseTreeNode<T>::GroupInfo::incrementGroupSize(int delta) {
    group_size+=delta;
}

template <typename T>
ReverseTreeNode<T>* ReverseTreeNode<T>::GroupInfo::getGroupHead() {
    return group_head;
}

template <typename T>
void ReverseTreeNode<T>::GroupInfo::setGroupHead(ReverseTreeNode<T>* new_head) {
    group_head=new_head;
}



#endif //WET2_REVERSETREENODE_H
