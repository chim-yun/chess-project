#include "StockfishAI.h"
#include <cstdio>
#include <regex>
#include <cctype>
#include <sstream>

namespace Chess {
namespace {

static std::string UrlEncode(const std::string& in) {
    std::ostringstream oss;
    for (unsigned char c : in) {
        if (std::isalnum(c) || c=='/' || c=='-') {
            oss << c;
        } else if (c == ' ') {
            oss << "%20";
        } else {
            char buf[4];
            std::snprintf(buf, sizeof(buf), "%%%02X", c);
            oss << buf;
        }
    }
    return oss.str();
}

} // namespace

std::string ToFEN(const GameState& state) {
    std::string fen;
    for (int r = 7; r >= 0; --r) {
        int empty = 0;
        for (int f = 0; f < 8; ++f) {
            const Piece& p = state.board[r * 8 + f];
            if (p.type == PieceType::None) {
                ++empty;
            } else {
                if (empty) { fen += std::to_string(empty); empty = 0; }
                char c = ' ';
                switch (p.type) {
                    case PieceType::Pawn:   c = 'P'; break;
                    case PieceType::Knight: c = 'N'; break;
                    case PieceType::Bishop: c = 'B'; break;
                    case PieceType::Rook:   c = 'R'; break;
                    case PieceType::Queen:  c = 'Q'; break;
                    case PieceType::King:   c = 'K'; break;
                    default: break;
                }
                if (p.color == Color::Black) c = std::tolower(c);
                fen += c;
            }
        }
        if (empty) fen += std::to_string(empty);
        if (r > 0) fen += '/';
    }
    fen += ' ';
    fen += (state.toMove == Color::White ? 'w' : 'b');
    fen += ' ';
    std::string cast;
    if (state.castling.whiteKingSide) cast += 'K';
    if (state.castling.whiteQueenSide) cast += 'Q';
    if (state.castling.blackKingSide) cast += 'k';
    if (state.castling.blackQueenSide) cast += 'q';
    if (cast.empty()) cast = "-";
    fen += cast + ' ';
    if (state.enPassantTarget) {
        int idx = *state.enPassantTarget;
        char file = 'a' + idx % 8;
        char rank = '1' + idx / 8;
        fen += file;
        fen += rank;
    } else {
        fen += '-';
    }
    fen += ' ';
    fen += std::to_string(state.halfmoveClock);
    fen += ' ';
    fen += std::to_string(state.fullmoveNumber);
    return fen;
}

std::optional<Move> MoveFromUCI(const std::string& uci) {
    if (uci.size() < 4) return std::nullopt;
    int ff = uci[0] - 'a';
    int fr = uci[1] - '1';
    int tf = uci[2] - 'a';
    int tr = uci[3] - '1';
    if (ff < 0 || ff > 7 || tf < 0 || tf > 7 || fr < 0 || fr > 7 || tr < 0 || tr > 7)
        return std::nullopt;
    Move m;
    m.from = fr * 8 + ff;
    m.to   = tr * 8 + tf;
    if (uci.size() >= 5) {
        char p = std::tolower(uci[4]);
        switch (p) {
            case 'q': m.promotion = PieceType::Queen; break;
            case 'r': m.promotion = PieceType::Rook; break;
            case 'b': m.promotion = PieceType::Bishop; break;
            case 'n': m.promotion = PieceType::Knight; break;
        }
    }
    return m;
}

std::optional<Move> QueryStockfish(const GameState& state) {
    std::string fen = ToFEN(state);
    std::string url = "https://stockfish.online/api/s/v2.php?fen=" + UrlEncode(fen);
    std::string cmd = "curl -s \"" + url + "\"";
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return std::nullopt;
    std::string output;
    char buf[256];
    while (fgets(buf, sizeof(buf), pipe)) output += buf;
    pclose(pipe);
    std::smatch m;
    std::regex re("\"bestmove\":\"([^\"]+)\"");
    if (std::regex_search(output, m, re)) {
        std::string token = m[1];
        size_t space = token.find(' ');
        std::string moveStr = (space == std::string::npos) ? token : token.substr(space + 1, 4);
        return MoveFromUCI(moveStr);
    }
    return std::nullopt;
}

} // namespace Chess
