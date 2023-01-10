//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname:Aydan Günaydın
//---Student Number:150200012
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char *argv)
{
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if (readKeyFile.is_open())
    {
        while (!readKeyFile.eof())
        {
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey()
{
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency()
{
    // DO NOT CHANGE THIS
    sortKey();
    // DO NOT CHANGE THIS

    int value = 1; // token's value
    int index = 0; // to iterate through string

    for (; index < (signed)sortedKey.length(); index++)
    {
        if (sortedKey[index + 1] && (sortedKey[index + 1] == sortedKey[index])) // if string is not finished and next element is the same, increase value
        {
            value++;
        }
        else // after string is iterated, create a new node with current values and put it into queue
        {
            Node *newNode = new Node();
            newNode->token.val = value;
            newNode->token.symbol = sortedKey[index];
            queue.enque(newNode);
            value = 1; // reset value
        }
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree()
{
    findFrequency(); // to fill in the priorityqueue
    Node *newNode = NULL;
    Node *leftNode = NULL;
    Node *rightNode = NULL;
    while (queue.head && queue.head->next)
    {
        leftNode = queue.dequeue(); // prior node is the left node
        rightNode = queue.dequeue();
        newNode = huffmanTree.mergeNodes(leftNode, rightNode);
        newNode->left = leftNode;
        newNode->right = rightNode;
        queue.enque(newNode);
    }
    huffmanTree.root = queue.dequeue(); // root is the greatest valued node so it is assigned lastly
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree()
{
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//
string Huffman::getTokenBinary(char tokenChar, Node *traverse, string tokenBinary)
{
    string s;
    s.push_back(tokenChar);
    if (s == traverse->token.symbol)
    { // finish recursion if node is found
        return tokenBinary;
    }
    else
    {
        if (traverse->left && (signed)traverse->left->token.symbol.find(tokenChar) != -1)
        {                                                                        // if left node doesnt contain searched char dont go left and continue, else go left
            return getTokenBinary(tokenChar, traverse->left, tokenBinary + "0"); // left's value is 0 so add 0 recursively
        }

        if (traverse->right && (signed)traverse->right->token.symbol.find(tokenChar) != -1) // if right doesnt contain searched char continue else go right
            return getTokenBinary(tokenChar, traverse->right, tokenBinary + "1");           // right's value is 1 so add 1 recursively
    }
    return NULL; // if no node contains the char, return null
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password)
{
    int index = 0;
    for (; password[index]; index++) // for each token find binary value and add it to encodedpassword
    {
        string newVal = getTokenBinary(password[index], huffmanTree.root, "");
        encodedBinaryPassword += newVal;
        encodedValPassword += to_string(newVal.length());
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword()
{
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword)
{

    int index = 0;
    for (int i = 0; i < (signed)encodedValPassword.length(); i++)
    { // by using values obtain tokens binary value then decode it
        string encodedToken = "";
        for (int j = 0; j < int(encodedValPassword[i] - 48); j++)
        { // minus 48 is for convertion between char and int
            encodedToken += encodedBinaryPassword[index++];
        }
        decodeToken(encodedToken);
    }
};

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken)
{
    int i = 0;
    Node *temp = huffmanTree.root; // starting from root iterate through the tree
    for (; i < (signed int)encodedToken.length(); i++)
    {
        if (encodedToken[i] == '0')
        { // 0 indicates left child
            temp = temp->left;
        }
        else if (encodedToken[i] == '1')
        { // 1 indicates right child
            temp = temp->right;
        }
    }
    decodedPassword += temp->token.symbol; // add iterated tokens value to password
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword()
{
    cout << "Decoded Password: " << decodedPassword << endl;
};