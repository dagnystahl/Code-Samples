
#include <string>
#include <vector>

#ifndef ANIMAL_NODE_H
#define ANIMAL_NODE_H

using namespace std;


class node {
public:
    ~node(){
        delete left;
        delete right;
    }
    string data;
    node* left;
    node* right;
private:

};


#endif //ANIMAL_NODE_H
