#ifndef MOVE_H
#define MOVE_H

#include "Board.h"
#include <optional>

namespace Chess {

struct Move {
    int from{0};
    int to{0};
    std::optional<PieceType> promotion; // promotion piece if any
};

} // namespace Chess

#endif // MOVE_H
