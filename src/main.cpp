#include "GameLogic.h"
#include "UserSystem.h"
#include <iostream>

using namespace Chess;

int main() {
    UserDatabase db = EmptyDatabase();
    db = RegisterUser(db, "user1", "pass");

    if (LoginUser(db, "user1", "pass"))
        std::cout << "Login successful\n";
    else
        std::cout << "Login failed\n";

    GameState state = MakeInitialState();
    // Example: move white pawn from e2 to e4 (index 12 -> 28)
    Move m{12, 28};
    auto next = ApplyMove(state, m);
    if (next) {
        std::cout << "Move applied\n";
        std::cout << "White in check? " << (IsInCheck(*next, Color::White) ? "yes" : "no") << "\n";
        std::cout << "Black in checkmate? " << (IsCheckmate(*next, Color::Black) ? "yes" : "no") << "\n";
    }
    return 0;
}
