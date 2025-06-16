#include "GameWindow.h"
#include <QWidget>
#include <QMessageBox>
#include <QProcess>

namespace Chess {

GameWindow::GameWindow(QWidget* parent) : QMainWindow(parent), state_(MakeInitialState()) {
    auto* central = new QWidget;    
    boardLayout_ = new QGridLayout; 
    for (int r=0;r<8;++r) {
        for (int f=0;f<8;++f) {
            int idx = r*8+f;
            auto* btn = new QPushButton;
            btn->setFixedSize(60,60);
            squares_[idx]=btn;
            boardLayout_->addWidget(btn,7-r,f);
            connect(btn,&QPushButton::clicked,this,[this,idx]{HandleSquare(idx);});
        }
    }
    central->setLayout(boardLayout_);
    setCentralWidget(central);
    RenderBoard();
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &GameWindow::UpdateTimers);
    timer_->start(1000);
}

void GameWindow::RenderBoard(){
    for(int i=0;i<64;++i){
        const Piece& p = state_.board[i];
        QString text;
        switch(p.type){
        case PieceType::Pawn: text="P"; break;
        case PieceType::Knight: text="N"; break;
        case PieceType::Bishop: text="B"; break;
        case PieceType::Rook: text="R"; break;
        case PieceType::Queen: text="Q"; break;
        case PieceType::King: text="K"; break;
        default: text=""; break;
        }
        if(p.color==Color::Black) text=text.toLower();
        squares_[i]->setText(text);
        squares_[i]->setStyleSheet("");
    }
}

void GameWindow::ClearHighlights(){
    for(auto* b : squares_) b->setStyleSheet("");
}

void GameWindow::HighlightMoves(const std::vector<Move>& moves){
    for(const auto& m : moves){
        squares_[m.to]->setStyleSheet("background: yellow");
    }
}

void GameWindow::HandleSquare(int idx){
    if(selected_==-1){
        if(state_.board[idx].color!=state_.toMove) return;
        selected_=idx;
        std::vector<Move> legal;
        for(int to=0;to<64;++to){
            Move m{idx,to};
            if(ApplyMove(state_,m)) legal.push_back(m);
            if(state_.board[idx].type==PieceType::Pawn && ((state_.board[idx].color==Color::White&&to/8==7)||(state_.board[idx].color==Color::Black&&to/8==0))){
                for(auto pt:{PieceType::Queen,PieceType::Rook,PieceType::Bishop,PieceType::Knight}){
                    Move pm{idx,to,pt};
                    if(ApplyMove(state_,pm)) legal.push_back(pm);
                }
            }
        }
        HighlightMoves(legal);
    }else{
        Move m{selected_,idx};
        if(auto next=ApplyMove(state_,m)){
            state_=*next;
        }
        selected_=-1;
        ClearHighlights();
        RenderBoard();
    }
}

void GameWindow::UpdateTimers(){
    if(state_.toMove==Color::White) --whiteTime_; else --blackTime_;
    if(whiteTime_<=0||blackTime_<=0){
        QMessageBox::information(this,"Game Over","Time out");
        timer_->stop();
    }
}

void GameWindow::MakeAIMove(){
    // Example stockfish integration using QProcess; not fully implemented
    QProcess sf;
    sf.start("stockfish");
    if(!sf.waitForStarted(1000)) return;
    sf.write("uci\n");
    sf.waitForReadyRead(1000);
    sf.write("ucinewgame\n");
    sf.write("isready\n");
    sf.waitForReadyRead(1000);
    // FEN not implemented; placeholder
}

} // namespace Chess
