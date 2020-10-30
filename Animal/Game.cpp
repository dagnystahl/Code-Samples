
#include "node.h"
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include "Game.h"
#include <stack>

void Game::init() {

    stack<node *> empty;
    queue<string> nothing;
    swap(nodes, empty);
    swap(questions, nothing);
    swap(answers, nothing);
}

node *Game::read_game_tree(string file) {
    node *root = new node;

    ifstream fin(file);
    if (fin.fail()) {
        root = NULL;
        return root;
    }
    read_preorder(root, fin);

    return root;
}

void Game::read_preorder(node *tree, ifstream &fin) {
    string type;
    fin >> type;
    fin.ignore();
    if (type == "#A") {
        tree->left = NULL;
        tree->right = NULL;
    } //base case *leaf
    string line;
    getline(fin, line);
    tree->data = line;

    if (type == "#Q") {
        tree->left = new node;
        tree->right = new node;
        read_preorder(tree->left, fin);
        read_preorder(tree->right, fin);
    }
}

void Game::play_game(node *root) {
    nodes.push(root);

    string ans = get_yesno(root->data);
    node *next = nullptr;
    questions.push(root->data);

    if (ans == "y") {
        answers.push("YES");
        next = root->left;
        if (next == NULL) {
            cout << "YAY! I guessed your animal!\n" << endl;
        } else { play_game(next); }
    }

    if (ans == "n") {
        answers.push("NO");
        next = root->right;
        if (next == NULL) {
            cout << "BOO! I don't know!\n" << endl;
            expand_game(nodes.top());
        } else { play_game(next); }
    }

}

void Game::expand_game(node *leaf) {
    string ans = get_yesno("Would you like to expand the game tree?");
    if (ans == "n") return;

    print_history();

    cout << "Enter a new animal in the form of a question," << endl;
    cout << "e.g., 'Is it a whale?' :" << endl;
    string newLeft = create_treeline("#A");
    cout << "Now enter a question for which the answer is 'yes' for your new \n "
            "animal, and which does not contradict your previous answers:" << endl;
    string newRoot = create_treeline("Q");

    append_tree(leaf, newRoot, newLeft);
}

void Game::print_history() {
    cout << "I asked the following:" << endl;
    while (!questions.empty() && !answers.empty()) {
        cout << questions.front() << " " << answers.front() << endl;
        questions.pop();
        answers.pop();
    }
}

string Game::get_yesno(string prompt) {
    string ans;
    while (true) {
        cout << prompt << "(y/n)" << endl;
        getline(cin, ans);
        if (ans == "y" || ans == "n") break;
        cout << "Could not recognize answer! Pleas enter 'y' or 'n' " << endl;
    }
    return ans;

}

string Game::create_treeline(string type) {
    string data;
    getline(cin, data);
    return data;
}

void Game::append_tree(node *leaf, string newRoot, string newLeft) {
    nodes.pop();
    node *l = new node;
    l->left = NULL;
    l->right = NULL;
    l->data = newLeft;
    node *root = new node;
    root->data = newRoot;
    root->left = l;
    root->right = leaf;


    if (nodes.top()->left == leaf) {
        nodes.top()->left = root;
    } else {
        nodes.top()->right = root;
    }

}

void Game::delete_game_tree(node *root) {
    delete root;
}

void Game::save_game_tree(node *root) {
    ofstream fout("GameTree.txt");
    write_preorder(root, fout);
    fout.close();
}

void Game::write_preorder(node *tree, ofstream &fout) {
    string line;
    string type;
    if (tree->left == NULL && tree->right == NULL) {
        type = "#A ";
    } else {
        type = "#Q ";
    }
    fout << type + tree->data << endl;
    if (type == "#Q ") {
        write_preorder(tree->left, fout);
        write_preorder(tree->right, fout);
    }
}
