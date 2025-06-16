#ifndef STOCKFISHAI_H
#define STOCKFISHAI_H

#include "GameLogic.h"
#include <optional>
#include <string>

namespace Chess {

// Convert a game state to FEN string
std::string ToFEN(const GameState& state);

// Parse UCI string (e2e4, g7g8q, etc.) to Move
std::optional<Move> MoveFromUCI(const std::string& uci);

// Query the Stockfish online API for the best move
std::optional<Move> QueryStockfish(const GameState& state);

} // namespace Chess

#endif // STOCKFISHAI_H
