#ifndef GAMEADAPTER_H
#define GAMEADAPTER_H

#include <QObject>
#include "GameLogic.h"

namespace Chess {

class GameAdapter : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString sideToMove READ sideToMove NOTIFY stateChanged)
public:
    explicit GameAdapter(QObject* parent = nullptr);

    QString sideToMove() const;

    Q_INVOKABLE void resign();
    Q_INVOKABLE void timeOut();

signals:
    void stateChanged();
    void gameOver(const QString& reason);

private:
    GameState state_;
};

} // namespace Chess

#endif // GAMEADAPTER_H
