#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDragMoveEvent;
class QFrame;
namespace Ui {
class DragLabel;
}
QT_END_NAMESPACE

//! [0]
class DragLabel : public QTextEdit
{
public:
    DragLabel(const QString &text, QWidget *parent);
    QString labelText() const;

    void textChanged();
private:
    Ui::DragLabel *ui;
};
//! [0]

#endif // DRAGLABEL_H
