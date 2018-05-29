#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>


enum Piece{Empty, PieceW, PieceB };
enum PossibleMove{invalidMove, validMove, possibleEnemy};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    QSize sizeHint();
    QSize minimumSize();
private:
    int squareWidth() { return contentsRect().width() / BoardWidth - (2*rowRankWidth()/BoardWidth); }
    int squareHeight() { return contentsRect().height() / BoardHeight - (2*columnRankHeight()/BoardHeight); }

    int rowRankWidth()
    {
        return (contentsRect().width()/BoardWidth)/2 ;
    }
    int columnRankHeight()
    {
        return (contentsRect().height()/BoardHeight)/2;
    }

    void drawBoardRow(QPainter* painter, int y);
    void drawColumnRank(QPainter* painter);
    void drawCorners(QPainter* painter);
    enum {BoardWidth = 8, BoardHeight = 8};
    Piece board[BoardWidth][BoardHeight];
    PossibleMove moveType[BoardWidth][BoardHeight];

    int curPieceX;
    int curPieceY;
    void drawPieceHightlight(QPainter* painter);
    Piece curPiece;

    Piece data(int x, int y);
    void setData(int x, int y, Piece data);

    PossibleMove getMoveType(int x, int y);
    void setMoveType(int x, int y, PossibleMove p);
    void resetMoveType();

    void initBoard();
    void drawPieces(QPainter *painter);
    void move(int fromX,int fromY, int toX, int toY);

    bool isMoveable;

    void createConnections();

    /***to delete ***/
    void debugMovePiece();
signals:
    void pieceClicked(QPoint);

private slots:
    void setHighlights(QPoint);
    void setMove(QPoint);
};

#endif // WIDGET_H
