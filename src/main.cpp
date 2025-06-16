#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "GameAdapter.h"
#include "UserSystem.h"

using namespace Chess;

int main(int argc, char** argv){
    QApplication app(argc, argv);

    UserDatabase db = LoadDatabase("users.txt");
    bool ok = false;
    QString user = QInputDialog::getText(nullptr,"Login","Username:",QLineEdit::Normal,"",&ok);
    if(!ok) return 0;
    QString pass = QInputDialog::getText(nullptr,"Login","Password:",QLineEdit::Password,"",&ok);
    if(!ok) return 0;
    if(!LoginUser(db,user.toStdString(),pass.toStdString())){
        QMessageBox::information(nullptr,"Register","Registering new user.");
        db = RegisterUser(db,user.toStdString(),pass.toStdString());
        SaveDatabase(db,"users.txt");
    }

    if(QMessageBox::question(nullptr,"Start","Start game?")==QMessageBox::No)
        return 0;

    GameAdapter adapter;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("game", &adapter);
    engine.load(QUrl::fromLocalFile("qml/ChessGame.qml"));
    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
