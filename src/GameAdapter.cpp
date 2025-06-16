#include "GameAdapter.h"
#include <QMessageBox>

namespace Chess {

GameAdapter::GameAdapter(QObject* parent) : QObject(parent), state_(MakeInitialState()) {}

QString GameAdapter::sideToMove() const {
    return state_.toMove == Color::White ? "White" : "Black";
}

void GameAdapter::resign() {
    emit gameOver(QString("%1 resigned").arg(sideToMove()));
}

void GameAdapter::timeOut() {
    emit gameOver("Time out");
}

} // namespace Chess
