#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <array>
#include <vector>
#include <QPushButton>
#include <QGridLayout>
#include <QTimer>
#include "GameLogic.h"

namespace Chess {

class GameWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit GameWindow(QWidget* parent = nullptr);

private slots:
    void HandleSquare(int idx);
    void UpdateTimers();

private:
    GameState state_;
    std::array<QPushButton*,64> squares_{};
    QGridLayout* boardLayout_{};
    int selected_{-1};
    QTimer* timer_{};
    int whiteTime_{600};
    int blackTime_{600};

    void RenderBoard();
    void ClearHighlights();
    void HighlightMoves(const std::vector<Move>& moves);
    void MakeAIMove();
};

} // namespace Chess

#endif // GAMEWINDOW_H
