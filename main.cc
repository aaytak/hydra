
#include "controller.h"
using namespace std;


// Main function, instantiates controller
int main(int argc, char** argv) {
    bool test = false;
    if (argc != 0  &&  argv[0] == "-testing") {
        test = true;
    }

    // Make controller for the game
    Controller c(test);

    // Setup & start game
    c.setupGame();
    c.startGame();

    // Play game
    c.playGame(); ////


    return 0;
}
