

#ifndef ANIMAL_GAME_H
#define ANIMAL_GAME_H

#include "node.h"
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include "sstream"
#include <iostream>
#include <stack>
class Game {
public:
    node* read_game_tree(string file);
    void play_game(node* current);
    void expand_game(node* leaf);
    void save_game_tree(node* root);
    void delete_game_tree(node* root);
    void init();

private:
    queue<string> questions;
    queue<string> answers;
    stack<node*> nodes;
    void print_history();
    void read_preorder(node* tree, ifstream &fin);
    void write_preorder(node* tree, ofstream &fout);
    string get_yesno(string prompt);
    string create_treeline(string type);
    void append_tree(node* leaf, string newRoot, string newLeft);


};


#endif //ANIMAL_GAME_H
