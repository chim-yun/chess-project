#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <optional>

namespace Chess {

enum class PieceType { None, Pawn, Knight, Bishop, Rook, Queen, King };

enum class Color { None, White, Black };

struct Piece {
    PieceType type{PieceType::None};
    Color color{Color::None};
};

using Board = std::array<Piece, 64>; // 8x8 board

} // namespace Chess

#endif // BOARD_H
