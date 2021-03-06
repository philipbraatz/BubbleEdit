#include "draglabel.h"
#include "draglabel.h"

#include <QtWidgets>

//! [0]

//! [2]

DragLabel::DragLabel(const QString &text, QWidget *parent)
    : QTextEdit(parent)
{
    QFontMetrics metric(font());
    QSize size = metric.size(Qt::TextSingleLine, text);

    QImage image(size.width() + 12, size.height() + 12, QImage::Format_ARGB32_Premultiplied);
    image.fill(qRgba(0, 0, 0, 0));

    QFont font;
    font.setStyleStrategy(QFont::ForceOutline);
    //! [0]

    //! [1]
    QLinearGradient gradient(0, 0, 0, image.height()-1);
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(0.2, QColor(200, 200, 255));
    gradient.setColorAt(0.8, QColor(200, 200, 255));
    gradient.setColorAt(1.0, QColor(127, 127, 200));

    QPainter painter;
    painter.begin(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(gradient);
    painter.drawRoundedRect(QRectF(0.5, 0.5, image.width()-1, image.height()-1),
                            25, 25, Qt::RelativeSize);

    painter.setFont(font);
    painter.setBrush(Qt::black);
    painter.drawText(QRect(QPoint(6, 6), size), Qt::AlignCenter, text);
    painter.end();
    //! [1]

    //! [2]
    //!

    this->setDocumentTitle(text);
    setDocument(new QTextDocument(text));
    //setPixmap(QPixmap::fromImage(image));
    //m_labelText = text;
}

QString DragLabel::labelText() const
{
    return "temp";//m_labelText;
}
void DragLabel::textChanged()
{
    //m_labelText = this->toPlainText();
}
