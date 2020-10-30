

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>
#include "node.h"
#include "Game.h"

using namespace std;


int main() {
    Game game;
    node *root = game.read_game_tree("animal.txt");
    if (root == NULL) return -1;

    while (true) {
        string tmp;
        int choice;
        game.init();

        cout << "Welcome to 20 questions!" << endl;
        cout << "  1) Play the game" << endl;
        cout << "  2) Save the game file" << endl;
        cout << "  3) Quit" << endl;
        cout << "Please make your selection: ";
        getline(cin, tmp);
        choice = atoi(tmp.c_str());

        switch (choice) {
            case 1:
                game.play_game(root);
                break;
            case 2:
                game.save_game_tree(root);
                break;
            case 3:
                break;
            default:
                cout << "Sorry, I don't understand." << endl << endl;
        }
        if (choice == 3) break;
    }

    game.delete_game_tree(root);
    return 0;
}
