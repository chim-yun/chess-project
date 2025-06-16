#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Board.h"
#include <optional>

namespace Chess {

struct CastlingRights {
    bool whiteKingSide{true};
    bool whiteQueenSide{true};
    bool blackKingSide{true};
    bool blackQueenSide{true};
};

struct GameState {
    Board board{};
    Color toMove{Color::White};
    CastlingRights castling{};
    std::optional<int> enPassantTarget; // square index for en passant capture
    int halfmoveClock{0};
    int fullmoveNumber{1};
};

GameState MakeInitialState();

} // namespace Chess

#endif // GAMESTATE_H
