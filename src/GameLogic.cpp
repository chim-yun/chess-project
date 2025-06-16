#include "GameLogic.h"
#include <cmath>
#include <algorithm>

namespace Chess {

bool IsInCheck(const GameState& state, Color color); // forward declaration

namespace {
// Helper to map board coordinates
constexpr int Index(int file, int rank) { return rank * 8 + file; }

Color Opposite(Color c) {
    return c == Color::White ? Color::Black : Color::White;
}

static bool IsOpponent(Color a, Color b) {
    return (a == Color::White && b == Color::Black) || (a == Color::Black && b == Color::White);
}

static bool IsPathClear(const GameState& state, int from, int to, int step) {
    for (int pos = from + step; pos != to; pos += step) {
        if (state.board[pos].type != PieceType::None)
            return false;
    }
    return true;
}

static bool IsSquareAttacked(const GameState& state, int sq, Color by) {
    int r = sq / 8, f = sq % 8;
    // Pawns
    int dir = (by == Color::White) ? 1 : -1;
    int pawnRank = r - dir;
    if (pawnRank >= 0 && pawnRank < 8) {
        if (f > 0) {
            const Piece& p = state.board[Index(f-1, pawnRank)];
            if (p.type == PieceType::Pawn && p.color == by) return true;
        }
        if (f < 7) {
            const Piece& p = state.board[Index(f+1, pawnRank)];
            if (p.type == PieceType::Pawn && p.color == by) return true;
        }
    }

    // Knights
    const int knightSteps[8][2] = {{1,2},{2,1},{-1,2},{-2,1},{1,-2},{2,-1},{-1,-2},{-2,-1}};
    for (auto s : knightSteps) {
        int nf = f + s[0];
        int nr = r + s[1];
        if (nf>=0 && nf<8 && nr>=0 && nr<8) {
            const Piece& p = state.board[Index(nf,nr)];
            if (p.type == PieceType::Knight && p.color == by) return true;
        }
    }

    // Sliding pieces
    const int bishopSteps[4] = {9, 7, -7, -9};
    for (int step : bishopSteps) {
        for (int pos = sq + step; pos >=0 && pos < 64 && abs((pos%8)-(sq%8))==abs((pos/8)-(sq/8)); pos += step) {
            const Piece& p = state.board[pos];
            if (p.type != PieceType::None) {
                if ((p.type == PieceType::Bishop || p.type == PieceType::Queen) && p.color == by)
                    return true;
                break;
            }
        }
    }
    const int rookSteps[4] = {8,-8,1,-1};
    for (int step : rookSteps) {
        for (int pos = sq + step; pos >=0 && pos < 64 && (step==1||step==-1?pos/8==sq/8:true); pos += step) {
            const Piece& p = state.board[pos];
            if (p.type != PieceType::None) {
                if ((p.type == PieceType::Rook || p.type == PieceType::Queen) && p.color == by)
                    return true;
                break;
            }
        }
    }

    // King
    for (int dr=-1; dr<=1; ++dr) for (int df=-1; df<=1; ++df) if (dr||df) {
        int nf = f+df, nr = r+dr;
        if (nf>=0 && nf<8 && nr>=0 && nr<8) {
            const Piece& p = state.board[Index(nf,nr)];
            if (p.type == PieceType::King && p.color == by) return true;
        }
    }
    return false;
}

static bool BasicMoveLegal(const GameState& state, const Move& move) {
    const Piece& piece = state.board[move.from];
    if (piece.type == PieceType::None) return false;
    if (state.board[move.to].color == piece.color) return false;
    int fr = move.from / 8, ff = move.from % 8;
    int tr = move.to / 8, tf = move.to % 8;
    int dr = tr - fr, df = tf - ff;

    switch (piece.type) {
    case PieceType::Pawn: {
        int dir = piece.color == Color::White ? 1 : -1;
        // simple move
        if (df == 0 && dr == dir && state.board[move.to].type == PieceType::None)
            return true;
        // double move
        if (df == 0 && dr == 2*dir && ((fr==1&&piece.color==Color::White)||(fr==6&&piece.color==Color::Black))) {
            int intermediate = move.from + dir*8;
            if (state.board[intermediate].type == PieceType::None && state.board[move.to].type == PieceType::None)
                return true;
        }
        // capture
        if (abs(df)==1 && dr==dir && state.board[move.to].type!=PieceType::None && IsOpponent(piece.color, state.board[move.to].color))
            return true;
        // en passant checked separately
        return false;
    }
    case PieceType::Knight:
        return (abs(df)==1 && abs(dr)==2) || (abs(df)==2 && abs(dr)==1);
    case PieceType::Bishop:
        return abs(df)==abs(dr) && IsPathClear(state, move.from, move.to, (df>0?1:-1) + (dr>0?8:-8));
    case PieceType::Rook:
        if (df==0 && dr!=0)
            return IsPathClear(state, move.from, move.to, dr>0?8:-8);
        if (dr==0 && df!=0)
            return IsPathClear(state, move.from, move.to, df>0?1:-1);
        return false;
    case PieceType::Queen:
        if (abs(df)==abs(dr))
            return IsPathClear(state, move.from, move.to, (df>0?1:-1)+(dr>0?8:-8));
        if (df==0 && dr!=0)
            return IsPathClear(state, move.from, move.to, dr>0?8:-8);
        if (dr==0 && df!=0)
            return IsPathClear(state, move.from, move.to, df>0?1:-1);
        return false;
    case PieceType::King:
        return std::max(abs(df),abs(dr))==1; // castling handled elsewhere
    default:
        return false;
    }
}

} // namespace

GameState MakeInitialState() {
    GameState state;
    // Initialize pawns
    for (int i = 0; i < 8; ++i) {
        state.board[Index(i, 1)] = {PieceType::Pawn, Color::White};
        state.board[Index(i, 6)] = {PieceType::Pawn, Color::Black};
    }
    // Rooks
    state.board[Index(0,0)] = {PieceType::Rook, Color::White};
    state.board[Index(7,0)] = {PieceType::Rook, Color::White};
    state.board[Index(0,7)] = {PieceType::Rook, Color::Black};
    state.board[Index(7,7)] = {PieceType::Rook, Color::Black};
    // Knights
    state.board[Index(1,0)] = {PieceType::Knight, Color::White};
    state.board[Index(6,0)] = {PieceType::Knight, Color::White};
    state.board[Index(1,7)] = {PieceType::Knight, Color::Black};
    state.board[Index(6,7)] = {PieceType::Knight, Color::Black};
    // Bishops
    state.board[Index(2,0)] = {PieceType::Bishop, Color::White};
    state.board[Index(5,0)] = {PieceType::Bishop, Color::White};
    state.board[Index(2,7)] = {PieceType::Bishop, Color::Black};
    state.board[Index(5,7)] = {PieceType::Bishop, Color::Black};
    // Queens
    state.board[Index(3,0)] = {PieceType::Queen, Color::White};
    state.board[Index(3,7)] = {PieceType::Queen, Color::Black};
    // Kings
    state.board[Index(4,0)] = {PieceType::King, Color::White};
    state.board[Index(4,7)] = {PieceType::King, Color::Black};
    return state;
}

static std::optional<GameState> HandleCastling(const GameState& state, const Move& move) {
    GameState next = state;
    const Piece& king = state.board[move.from];
    if (king.type != PieceType::King)
        return std::nullopt;

    int fileFrom = move.from % 8;
    int fileTo   = move.to % 8;
    int rank = move.from / 8;
    if (IsInCheck(state, king.color))
        return std::nullopt;

    if (king.color == Color::White && rank == 0 && fileFrom == 4) {
        if (fileTo == 6 && state.castling.whiteKingSide) {
            if (state.board[Index(5,0)].type==PieceType::None && state.board[Index(6,0)].type==PieceType::None &&
                !IsSquareAttacked(state, Index(5,0), Color::Black) &&
                !IsSquareAttacked(state, Index(6,0), Color::Black)) {
                next.board[move.from] = {};
                next.board[move.to] = king;
                next.board[Index(5,0)] = {PieceType::Rook, Color::White};
                next.board[Index(7,0)] = {};
                next.castling.whiteKingSide = next.castling.whiteQueenSide = false;
                next.toMove = Color::Black;
                if (!IsInCheck(next, Color::White))
                    return next;
            }
        }
        if (fileTo == 2 && state.castling.whiteQueenSide) {
            if (state.board[Index(1,0)].type==PieceType::None && state.board[Index(2,0)].type==PieceType::None && state.board[Index(3,0)].type==PieceType::None &&
                !IsSquareAttacked(state, Index(3,0), Color::Black) &&
                !IsSquareAttacked(state, Index(2,0), Color::Black)) {
                next.board[move.from] = {};
                next.board[move.to] = king;
                next.board[Index(3,0)] = {PieceType::Rook, Color::White};
                next.board[Index(0,0)] = {};
                next.castling.whiteKingSide = next.castling.whiteQueenSide = false;
                next.toMove = Color::Black;
                if (!IsInCheck(next, Color::White))
                    return next;
            }
        }
    }
    if (king.color == Color::Black && rank == 7 && fileFrom == 4) {
        if (fileTo == 6 && state.castling.blackKingSide) {
            if (state.board[Index(5,7)].type==PieceType::None && state.board[Index(6,7)].type==PieceType::None &&
                !IsSquareAttacked(state, Index(5,7), Color::White) &&
                !IsSquareAttacked(state, Index(6,7), Color::White)) {
                next.board[move.from] = {};
                next.board[move.to] = king;
                next.board[Index(5,7)] = {PieceType::Rook, Color::Black};
                next.board[Index(7,7)] = {};
                next.castling.blackKingSide = next.castling.blackQueenSide = false;
                next.toMove = Color::White;
                if (!IsInCheck(next, Color::Black))
                    return next;
            }
        }
        if (fileTo == 2 && state.castling.blackQueenSide) {
            if (state.board[Index(1,7)].type==PieceType::None && state.board[Index(2,7)].type==PieceType::None && state.board[Index(3,7)].type==PieceType::None &&
                !IsSquareAttacked(state, Index(3,7), Color::White) &&
                !IsSquareAttacked(state, Index(2,7), Color::White)) {
                next.board[move.from] = {};
                next.board[move.to] = king;
                next.board[Index(3,7)] = {PieceType::Rook, Color::Black};
                next.board[Index(0,7)] = {};
                next.castling.blackKingSide = next.castling.blackQueenSide = false;
                next.toMove = Color::White;
                if (!IsInCheck(next, Color::Black))
                    return next;
            }
        }
    }
    return std::nullopt;
}

static std::optional<GameState> HandleEnPassant(const GameState& state, const Move& move) {
    GameState next = state;
    const Piece& piece = state.board[move.from];
    if (piece.type != PieceType::Pawn || !state.enPassantTarget)
        return std::nullopt;
    if (move.to != *state.enPassantTarget)
        return std::nullopt;

    int dir = (piece.color == Color::White) ? 1 : -1;
    int captured = move.to - dir*8;

    if (state.board[captured].type != PieceType::Pawn || !IsOpponent(piece.color, state.board[captured].color))
        return std::nullopt;

    next.board[move.from] = {};
    next.board[captured] = {};
    next.board[move.to] = piece;
    next.enPassantTarget.reset();
    next.toMove = (state.toMove == Color::White) ? Color::Black : Color::White;
    if (IsInCheck(next, state.toMove))
        return std::nullopt;
    return next;
}

static GameState HandlePawnPromotion(const GameState& state, const Move& move, const Piece& pawn) {
    GameState next = state;
    next.board[move.from] = {};
    next.board[move.to] = {move.promotion.value_or(PieceType::Queen), pawn.color};
    next.enPassantTarget.reset();
    next.toMove = (state.toMove == Color::White) ? Color::Black : Color::White;
    return next;
}

std::optional<GameState> ApplyMove(const GameState& state, const Move& move) {
    if (move.from < 0 || move.from >= 64 || move.to < 0 || move.to >= 64)
        return std::nullopt;

    const Piece& piece = state.board[move.from];
    if (piece.color != state.toMove)
        return std::nullopt;

    // Castling
    if (piece.type == PieceType::King) {
        if (auto castled = HandleCastling(state, move))
            return castled;
    }

    // En passant
    if (auto ep = HandleEnPassant(state, move))
        return ep;

    if (!BasicMoveLegal(state, move))
        return std::nullopt;

    GameState next = state;
    next.board[move.from] = {};
    Piece captured = state.board[move.to];
    next.board[move.to] = piece;
    next.enPassantTarget.reset();

    // Pawn double move to set en passant target
    if (piece.type == PieceType::Pawn) {
        int fromRank = move.from / 8;
        int toRank = move.to / 8;
        if (piece.color == Color::White && fromRank == 1 && toRank == 3)
            next.enPassantTarget = move.from + 16;
        else if (piece.color == Color::Black && fromRank == 6 && toRank == 4)
            next.enPassantTarget = move.from - 16;
        // Promotion
        if ((piece.color == Color::White && toRank == 7) || (piece.color == Color::Black && toRank == 0))
            return HandlePawnPromotion(next, move, piece);
    }

    // Update castling rights if rooks or king moved
    if (piece.type == PieceType::King) {
        if (piece.color == Color::White) {
            next.castling.whiteKingSide = next.castling.whiteQueenSide = false;
        } else {
            next.castling.blackKingSide = next.castling.blackQueenSide = false;
        }
    }
    if (piece.type == PieceType::Rook) {
        if (move.from == 0)
            next.castling.whiteQueenSide = false;
        if (move.from == 7)
            next.castling.whiteKingSide = false;
        if (move.from == 56)
            next.castling.blackQueenSide = false;
        if (move.from == 63)
            next.castling.blackKingSide = false;
    }

    // Opponent rook captured affects castling rights
    if (captured.type == PieceType::Rook) {
        if (move.to == 0)
            next.castling.whiteQueenSide = false;
        if (move.to == 7)
            next.castling.whiteKingSide = false;
        if (move.to == 56)
            next.castling.blackQueenSide = false;
        if (move.to == 63)
            next.castling.blackKingSide = false;
    }

    // Switch side to move
    next.toMove = (state.toMove == Color::White) ? Color::Black : Color::White;
    if (IsInCheck(next, state.toMove))
        return std::nullopt; // absolute pin
    return next;
}

bool IsInCheck(const GameState& state, Color color) {
    int kingSq = -1;
    for (int i=0;i<64;++i) {
        const Piece& p = state.board[i];
        if (p.type==PieceType::King && p.color==color) {
            kingSq = i;
            break;
        }
    }
    if (kingSq == -1) return false;
    return IsSquareAttacked(state, kingSq, Opposite(color));
}

bool IsCheckmate(const GameState& state, Color color) {
    if (!IsInCheck(state, color))
        return false;
    for (int from=0; from<64; ++from) {
        if (state.board[from].color != color) continue;
        for (int to=0; to<64; ++to) {
            Move m{from,to};
            if (ApplyMove(state,m)) return false;
            if (state.board[from].type==PieceType::Pawn && ((color==Color::White && to/8==7) || (color==Color::Black && to/8==0))) {
                for (PieceType pt : {PieceType::Queen,PieceType::Rook,PieceType::Bishop,PieceType::Knight}) {
                    Move pm{from,to,pt};
                    if (ApplyMove(state,pm)) return false;
                }
            }
        }
    }
    return true;
}

} // namespace Chess
