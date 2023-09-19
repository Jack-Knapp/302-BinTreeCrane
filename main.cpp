/*
Name: Jack Knapp, 302.3
Purpose: Practice with Binary Trees
Description: Program to validate torque balance for crane
Input: Objects for Crane to lift with Weights
What to do?:  Verify whether the objects are a balanced tree or not
    using recursive functions
Output: The pass fail results, printed to terminal
*/

#include "binaryTreeClasses.h"
#include <iostream>
#include <sstream>

using namespace std;

/* 
 * buildTree : A function to recursively build a tree based
    off a given input file
 * parameters: N/A
 * return value: a pointer to the root node of the tree
 */
binTreeNode* buildTree() {
    string data, item;
    double a,b,c,d;
    
    //input via linux redirection
    getline(cin, data);
    //cout << data<<endl;
    stringstream s(data);
    s >> item;

    //check object type
    if (item == "Joint") {
        binTreeNode* node = new binTreeNode;
        s >> item;
        a = stoi(item);
        s >> item;
        b = stoi(item);
        
        //recursive call for children
        binTreeNode* left = buildTree();
        binTreeNode* right = buildTree();

        node->setLeft(nullptr);
        node->setRight(nullptr);
        node->setLeft(left);
        node->setRight(right);

        left->setArmLength(a);
        right->setArmLength(b);

        return node;
    } 
    else {
        if (item == "Goped") {
            //create object and set pointers to null
            s >> item;
            a = stod(item);
            s >> item;
            b = stod(item);
            s >> item;
            c = stod(item);
            binTreeNode* gope = new goped(a,b,c);
            gope->setLeft(nullptr);
            gope->setRight(nullptr);
            return gope;    
        }
        else if (item == "Bike") {
            //create object and set pointers to null
            s >> item;
            a = stod(item);
            s >> item;
            b = stod(item);
            binTreeNode* bik = new bike(a,b);
            bik->setLeft(nullptr);
            bik->setRight(nullptr);
            return bik;
        }
        else if (item == "Car") {
            //create object and set pointers to null
            s >> item;
            a = stod(item);
            s >> item;
            b = stod(item);
            s >> item;
            c = stod(item);
            s >> item;
            d = stod(item);
            binTreeNode* cat = new car(a,b,c,d);
            cat->setLeft(nullptr);
            cat->setRight(nullptr);
            return cat; 
        }
    }  
}

/* 
 * howWeight : A function to recursively weigh a given tree
 * parameters: a bintreeNode pointer
 * return value: A double with the tree weight
 */
double howWeight(binTreeNode* r) {
    //create temp left and right pointers
    binTreeNode* left = r->getLeft();
    binTreeNode* right = r->getRight();

    //if node is a leaf, get the weight
    if (left == nullptr && right == nullptr) {
        return r->getWeight();
    }
    else {
        //recusrive call on children of joint
        double num1 = howWeight(left);
        double num2 = howWeight(right);

        //check if torque matches
        if (num1*left->getArmLength() == num2*right->getArmLength()) {
            return num1+num2;
        }
        else {
            return -1;
        }
    }  
}

/* 
 * deallocTree : A function to deallocate a given tree
 * parameters: a bintreeNode pointer
 * return value: N/A
 */
void deallocTree(binTreeNode* r) {
    //create temp left and right pointers
    binTreeNode* left = r->getLeft();
    binTreeNode* right = r->getRight();

    //if leaf node, delete
    if (left == nullptr && right == nullptr) {
        delete r;
        return;
    } 
        //recursive call on left and right children
        deallocTree(left);
        deallocTree(right);
        delete r;
}


int main(){
    //main program
    binTreeNode * root = buildTree();

    if (howWeight (root) != -1.0) {
        cout << " Crane can lift the items \n";
    }
    else {
        cout << " Well this is awkward \n";
    }

    deallocTree(root);

    return 0;
}
