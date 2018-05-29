#include "widget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(500,500);
    setMaximumSize(500, 500);
    initBoard();
    isMoveable = false;
    createConnections();
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    for( int h = 0 ; h < BoardWidth ; ++h )
    {
        drawBoardRow(&painter, h);
    }
    drawColumnRank(&painter);
    drawCorners(&painter);
    drawPieceHightlight(&painter);
    drawPieces(&painter);
}

QSize Widget::sizeHint()
{
    return QSize(500, 500);
}

QSize Widget::minimumSize()
{
    return QSize(500, 500);
}

void Widget::drawBoardRow(QPainter *painter, int y)
{
    QColor color;
    QColor rowRankColor;
    rowRankColor.setRgb(211,211,211);
    painter->setBrush(rowRankColor);
    painter->drawRect(0, columnRankHeight() + y*squareHeight(), rowRankWidth() , squareHeight());
    painter->drawText(QRect(0, columnRankHeight() + y*squareHeight(), rowRankWidth() , squareHeight()), Qt::AlignCenter, QString::number(8-y) );

    if(y%2)
    {
        for(int i = 0; i < BoardWidth; ++i)
        {
            if(i%2)
            {
                color.setRgb(238, 221, 187);
            }
            else
            {
                color.setRgb(204,136, 68);
            }
            painter->setBrush(color);
            painter->drawRect( i * squareWidth() + rowRankWidth(),
                             y * squareHeight() + columnRankHeight(),
                             squareWidth(),
                             squareHeight());

        }
    }
    else
    {
        for(int i = 0; i < BoardWidth; ++i)
        {
            if(!(i%2))
            {
                color.setRgb(238, 221, 187);
            }
            else
            {
                color.setRgb(204,136, 68);
            }
            painter->setBrush(color);
            painter->drawRect( i * squareWidth() + rowRankWidth(),
                             y * squareHeight() + columnRankHeight(),
                             squareWidth(),
                             squareHeight());


        }
    }
    painter->setBrush(rowRankColor);
    painter->drawRect(rowRankWidth() + BoardWidth*squareWidth(), columnRankHeight() + y*squareHeight(), rowRankWidth() , squareHeight());
    painter->drawText(QRect(rowRankWidth() + BoardWidth*squareWidth(), columnRankHeight() + y*squareHeight(), rowRankWidth() , squareHeight()), Qt::AlignCenter, QString::number(8-y) );
}

void Widget::drawPieceHightlight(QPainter *painter)
{
    QColor color;
    color.setRgb(230, 0, 0, 128);
    painter->setBrush(color);
    if( data(curPieceX, curPieceY) == PieceB)
    {
        int x = curPieceX * squareWidth() + rowRankWidth() ;
        int y = curPieceY * squareHeight() + columnRankHeight();
        int width = squareWidth();
        int height = squareHeight();
        painter->drawRect(QRect(x, y, width, height));

        if( (curPieceX-1) >= 0 && (curPieceY+1 < BoardHeight) /* && (data(curPieceX-1, curPieceY + 1) == Empty)*/ )
        {
             color.setRgb(200, 0, 0, 128);
             painter->setBrush(color);
             int x = (curPieceX-1) * squareWidth() + rowRankWidth();
             int y = (curPieceY+1) * squareHeight() + columnRankHeight();
             int width = squareWidth();
             int height = squareHeight();
             painter->drawRect( QRect(x, y, width, height) );
        }
        if( (curPieceX+1) < BoardWidth && (curPieceY + 1 < BoardHeight) /*&& (data(curPieceX+1, curPieceY + 1) == Empty)*/ )
        {
            color.setRgb(200, 0, 0, 128);
            painter->setBrush(color);
            int x = (curPieceX+1) * squareWidth() + rowRankWidth();
            int y =  (curPieceY+1) * squareHeight() + columnRankHeight();
            int width = squareWidth();
            int height = squareHeight();
            painter->drawRect( QRect(x, y, width, height) );
        }


    }
    if( data(curPieceX, curPieceY) == PieceW)
    {
        int x = curPieceX * squareWidth() + rowRankWidth();
        int y =  curPieceY * squareWidth() + columnRankHeight();
        int width = squareWidth();
        int height = squareHeight();
        painter->drawRect(x, y, width, height);

        if( (curPieceX-1) >= 0 && (curPieceY-1 >= 0) && (data(curPieceX-1, curPieceY - 1) == Empty) )
        {
             color.setRgb(200, 0, 0, 128);
             painter->setBrush(color);
             int x = (curPieceX-1) * squareWidth() + rowRankWidth();
             int y = (curPieceY-1) * squareHeight() + columnRankHeight();
             int width = squareWidth();
             int height = squareHeight();
             painter->drawRect( QRect(x, y, width, height) );
        }
        if( (curPieceX+1) < BoardWidth && (curPieceY - 1 >= 0) && (data(curPieceX+1, curPieceY - 1) == Empty) )
        {
            color.setRgb(200, 0, 0, 128);
            painter->setBrush(color);
            int x = (curPieceX+1) * squareWidth() + rowRankWidth();
            int y =  (curPieceY-1) * squareHeight() + columnRankHeight();
            int width = squareWidth();
            int height = squareHeight();
            painter->drawRect( QRect(x, y, width, height));
        }

    }
}

void Widget::mousePressEvent(QMouseEvent* event)
{
    if(!isMoveable)
    {
        emit setHighlights( event->pos() );
    }
    else
    {
        emit setMove(event->pos() );
    }
}

void Widget::initBoard()
{
    for(int x = 0; x < BoardWidth; x++)
        for(int y = 0; y < BoardHeight; ++y)
            board[x][y] = Empty;

    board[1][0] = PieceB;
    board[3][0] = PieceB;
    board[5][0] = PieceB;
    board[7][0] = PieceB;

    board[0][1] = PieceB;
    board[2][1] = PieceB;
    board[4][1] = PieceB;
    board[6][1] = PieceB;

    board[1][6] = PieceW;
    board[3][6] = PieceW;
    board[5][6] = PieceW;
    board[7][6] = PieceW;

    board[0][7] = PieceW;
    board[2][7] = PieceW;
    board[4][7] = PieceW;
    board[6][7] = PieceW;

    curPieceX = 0;
    curPieceY = 0;
}

Piece Widget::data(int x, int y)
{
    return board[x][y];
}

void Widget::setData(int x, int y, Piece data)
{
    board[x][y] = data;
}

void Widget::drawPieces(QPainter *painter)
{
    QPixmap pixmap;
    for(int r = 0 ; r < BoardWidth; r++)
    {
        for(int c = 0; c < BoardWidth; ++c)
        {
            if( board[r][c] == PieceB)
            {
                pixmap.load(":/img/black.svg");
                painter->drawPixmap(r*squareWidth()+rowRankWidth(), c*squareHeight() + columnRankHeight(), squareWidth(), squareHeight(), pixmap);
            }
            else if( board[r][c] == PieceW)
            {
                pixmap.load(":/img/white.svg");
                painter->drawPixmap(r*squareWidth() + rowRankWidth(), c*squareHeight() + columnRankHeight(), squareWidth(), squareHeight(), pixmap);
            }

        }
    }
}

void Widget::move(int fromX,int fromY,int toX,int  toY )
{
    Piece p = board[fromX][fromY];

    setData(fromX, fromY, Empty);
    setData(toX, toY, p);
}

void Widget::drawColumnRank(QPainter* painter)
{
    QColor color;
    color.setRgb(211, 211, 211);
    painter->setBrush(color);
    for(int i = 0; i < BoardWidth; ++i)
    {
        painter->drawRect(rowRankWidth() + i*squareWidth(), 0, squareWidth(), columnRankHeight());
        painter->drawText(QRect(rowRankWidth() + i*squareWidth(), 0, squareWidth(), columnRankHeight()), Qt::AlignCenter,  QString(QChar('a'+i)));
    }

    for(int i = 0; i < BoardWidth; ++i)
    {
        painter->drawRect(rowRankWidth() + i*squareWidth(), columnRankHeight() + BoardHeight*squareHeight(), squareWidth(), columnRankHeight());
        painter->drawText(QRect(rowRankWidth() + i*squareWidth(), columnRankHeight() + BoardHeight*squareHeight(), squareWidth(), columnRankHeight()), Qt::AlignCenter, QString(QChar('a' + i)));
    }
}

void Widget::drawCorners(QPainter* painter)
{
    QColor color;
    color.setRgb(0,0,0);
    painter->setBrush(color);
    painter->drawRect(0, 0, rowRankWidth(), columnRankHeight() );
    painter->drawRect(rowRankWidth() + BoardWidth*squareWidth(), 0, rowRankWidth(), columnRankHeight() );

    painter->drawRect(0, columnRankHeight() + BoardHeight*squareHeight(), rowRankWidth(), columnRankHeight());
    painter->drawRect(rowRankWidth() + BoardHeight*squareHeight(), columnRankHeight() + BoardHeight*squareHeight(), rowRankWidth(), columnRankHeight());
}

void Widget::setHighlights(QPoint clickedPoint)
{
    //check position clicked point. If pos is out of board's square then return
    if( (clickedPoint.x() < rowRankWidth()) || (clickedPoint.y() < columnRankHeight()) )
    {
        return;
    }

    //curPieceX/Y are number of square from left to right and top to bottom
    curPieceX = ( clickedPoint.x()-rowRankWidth() ) / squareWidth()  ;
    curPieceY = ( clickedPoint.y() - columnRankHeight() )/ (squareHeight());

    //check position clicked point. If pos is out of board's square then return
    if(curPieceX >= BoardWidth || curPieceY >= BoardHeight)
    {
        return;
    }
    curPiece = data(curPieceX, curPieceY);

    //flag to move
    isMoveable = false;
    if( data(curPieceX, curPieceY) == PieceB)
    {
        isMoveable = true;
        //check range
        if( ( (curPieceX-1) >= 0 && (curPieceY+1 < BoardHeight) && (data(curPieceX-1, curPieceY + 1) == Empty) )
                ||
          ( (data(curPieceX-1, curPieceY + 1) == PieceW) && (data(curPieceX-1, curPieceY + 1) != PieceB)  ))
        {
             int x = (curPieceX-1) ;
             int y = (curPieceY+1) ;

             if(board[x][y] == PieceW){

             }

             setMoveType(x,y, validMove);
        }
        if( (curPieceX+1) < BoardWidth && (curPieceY + 1 < BoardHeight) && (data(curPieceX+1, curPieceY + 1) == Empty) )
        {
            int x = (curPieceX+1);
            int y =  (curPieceY+1);
            if(board[x][y] == PieceW){

            }
            setMoveType(x, y, validMove);
        }
    }

    if( data(curPieceX, curPieceY) == PieceW)
    {
        isMoveable = true;
        if( (curPieceX-1) >= 0 && (curPieceY-1 >= 0) && (data(curPieceX-1, curPieceY - 1) == Empty) )
        {
             int x = (curPieceX-1);
             int y = (curPieceY-1);
             if(board[x][y] == PieceB){

             }
             setMoveType(x, y, validMove);
        }
        if( (curPieceX+1) < BoardWidth && (curPieceY - 1 >= 0) && (data(curPieceX+1, curPieceY - 1) == Empty) )
        {
            int x = (curPieceX+1);
            int y =  (curPieceY-1) ;
            if(board[x][y] == PieceB){

            }
            setMoveType(x, y, validMove);
        }

    }

    debugMovePiece();
    update();
}

void Widget::createConnections()
{
    connect(this, SIGNAL(pieceClicked(QPoint)), this, SLOT(setHighlights(QPoint)));
}

PossibleMove Widget::getMoveType(int x, int y)
{
    return moveType[x][y];
}

void Widget::setMoveType(int x, int y, PossibleMove p)
{
    moveType[x][y] = p;
}

void Widget::resetMoveType()
{
    for(int r = 0 ; r < BoardWidth; r++)
        for(int c = 0; c < BoardHeight; c++)
        {
            moveType[r][c] = invalidMove;
        }
}

void Widget::setMove(QPoint clickedPoint)
{
    if( (clickedPoint.x() < rowRankWidth()) || (clickedPoint.y() < columnRankHeight()) )
    {
        return;
    }
    int X = ( clickedPoint.x()-rowRankWidth() ) / squareWidth()  ;
    int Y = ( clickedPoint.y() - columnRankHeight() )/ (squareHeight());
    if(X >= BoardWidth || X >= BoardHeight)
    {
        return;
    }

    if( /*data(X, Y) == PieceW || data(X, Y) == PieceB ||*/ (data(X, Y) == Empty &&  getMoveType(X,Y) == invalidMove))
    {
        curPieceX = X;
        curPieceY = Y;
        curPiece = data(curPieceX, curPieceY);
        isMoveable = false;
        update();
        return;
    }

    if( data(X, Y) == Empty &&  getMoveType(X,Y) == validMove )
    {
        move(curPieceX, curPieceY, X, Y);
        curPieceX = -1;
        curPieceY = -1;
        curPiece = data(curPieceX, curPieceY);
        resetMoveType();
        isMoveable = false;
    }



    update();
}

void Widget::debugMovePiece()
{
    for(int i = 0; i < BoardWidth; i++)
        for(int j = 0; j < BoardHeight; j++)
        {
            qDebug() << "x " << i << " y " << j;
            if(getMoveType(i,j) == invalidMove)
            {
                qDebug() << "invalidMove";
            }
            else if(getMoveType(i,j) == validMove)
            {
                qDebug() << "validMove";
            }


        }
}
