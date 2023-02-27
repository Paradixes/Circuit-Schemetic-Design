#include "Text.h"
#include <iostream>

Text::Text()
{
    initial();
}

Text::Text(const Text& rhs)
{
    initial();
    setPos(rhs.scenePos());
    setPlainText(rhs.toPlainText());
}

void Text::initial()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    setFont(font);
    setTextInteractionFlags(Qt::TextEditable);
    setTextInteractionFlags(Qt::TextEditorInteraction);

    code = TEXT;
}

void Text::startDraw(QGraphicsSceneMouseEvent *event)
{
    setPos(event->scenePos());
}

void Text::drawing(QGraphicsSceneMouseEvent *event)
{
    return;
}

void Text::writeFile(std::ofstream &fout)
{
    fout << shapeCode() << "\t" << rotation() << "\r\n";
    fout << scenePos().x() << "\t" << scenePos().y() << "\r\n";
    fout << toPlainText().toStdString() << "\r\n";
}

void Text::readFile(std::ifstream &fin)
{
    qreal r, x, y;
    std::string str;
    QString qstr;
    fin >> r >> x >> y;
    fin >> str;
    qstr = QString::fromStdString(str);
    setPos(x, y);
    setPlainText(qstr);
    setRotation(r);
}

void Text::setRectBounding(QRectF rect)
{
    setPos(rect.bottomRight());
}

void Text::setcolor(QString color)
{
    setDefaultTextColor(setColorPen(color));
}
