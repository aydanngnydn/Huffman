//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname:Aydan Günaydın
//---Student Number:150200012
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue()
{
    this->head = NULL;
};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node *newnode)
{
    if (head)
    {
        Node *tempHead = head; // temp variable used for iterating through queue
        if (newnode->token.val < tempHead->token.val)
        { // if newnode is smaller than head, directly place it
            newnode->next = head;
            head = newnode;
        }
        else
        {
            while (tempHead->next && (newnode->token.val >= tempHead->next->token.val))
            {
                tempHead = tempHead->next; // traverse and find the node before the greater valued node
            }
            newnode->next = tempHead->next; // place newnode
            tempHead->next = newnode;
        }
    }
    else
    {                   // if there is no head, new node is assigned to head directly
        head = newnode; // if there is no head, newnode is head
    }
};

//-------------Remove Node From Priority Queue-------------//
Node *PriorityQueue::dequeue()
{
    Node *tempHead = head;
    if (head)
    {
        if (head->next)
        {
            head = head->next;     // shift head to right
            tempHead->next = NULL; // temphead's nexts are head's nexts but we only need the head node
            return tempHead;
        }
        else // if head is the only node, queue is emptied
        {
            head = NULL;
            return tempHead;
        }
    }
    else // if queue is empty return null
        return NULL;
};

//-------------Initialize Tree-------------//
Tree::Tree()
{
    this->root = NULL;
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree()
{
    deleteTree(root);
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node *node)
{ // recursively deletes all nodes
    if (node == NULL)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

//-------------Merges Two Node Into One-------------//
Node *Tree::mergeNodes(Node *temp1, Node *temp2)
{
    Node *treeNode = new Node(); // treenode will be the merged node
    treeNode->token.val = temp1->token.val + temp2->token.val;
    treeNode->token.symbol = temp1->token.symbol + temp2->token.symbol; // temp1's symbol comes first
    return treeNode;                                                    // after asssigning values return treeNode
};

void Tree::printTree(Node *traverse, int level)
{
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t";

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if (traverse->left)
        printTree(traverse->left, level + 1);
    if (traverse->right)
        printTree(traverse->right, level + 1);
};