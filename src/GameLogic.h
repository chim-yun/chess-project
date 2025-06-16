#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "GameState.h"
#include "Move.h"
#include <optional>

namespace Chess {

// Create the initial chess position
GameState MakeInitialState();

// Apply a move and return a new state if the move is legal
std::optional<GameState> ApplyMove(const GameState& state, const Move& move);

// Detect if the specified color is in check
bool IsInCheck(const GameState& state, Color color);

// Determine if the side to move has no legal moves and is in check
bool IsCheckmate(const GameState& state, Color color);

} // namespace Chess

#endif // GAMELOGIC_H
