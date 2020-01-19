#include <qtextstream.h>
#include "draglabel.h"
#include "Editor.h"

#include <QtWidgets>//QDrag Events

static inline QString fridgetMagnetsMimeType() { return QStringLiteral("application/x-fridgemagnet"); }

Editor::Editor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionExit, SIGNAL(clicked()), this, SLOT(exit()));
	connect(ui.btnTest, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
}

void Editor::onButtonClicked()
{
	ui.btnTest->setText(tr("Hello World"));
	QTextStream stream(stdout);
	stream << "Button clicked" << endl;
}

void Editor::dragEnterEvent(QDragEnterEvent* event)
{
    //! [4] //! [5]
    if (event->mimeData()->hasFormat(fridgetMagnetsMimeType())) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else {
            event->acceptProposedAction();
            //! [5] //! [6]
        }
        //! [6] //! [7]
    }
    else if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
    else {
        event->ignore();
    }
}
//! [7]

//! [8]
void Editor::dragMoveEvent(QDragMoveEvent* event)
{
    if (event->mimeData()->hasFormat(fridgetMagnetsMimeType())) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else {
            event->acceptProposedAction();
        }
    }
    else if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
    else {
        event->ignore();
    }
}
//! [8]

//! [9]
void Editor::dropEvent(QDropEvent* event)
{
    if (event->mimeData()->hasFormat(fridgetMagnetsMimeType())) {
        const QMimeData* mime = event->mimeData();
        //! [9] //! [10]
        QByteArray itemData = mime->data(fridgetMagnetsMimeType());
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPoint offset;
        //! [10]
        //! [11]
        DragLabel* newLabel = new DragLabel("old text would go here", this);
        newLabel->move(event->pos() - offset);
        newLabel->show();
        newLabel->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else {
            event->acceptProposedAction();
        }
        //! [11] //! [12]
    }
    else if (event->mimeData()->hasText()) {
        QStringList pieces = event->mimeData()->text().split(QRegularExpression(QStringLiteral("\\s+")),
            QString::SkipEmptyParts);
        QPoint position = event->pos();

        foreach(const QString & piece, pieces) {
            DragLabel* newLabel = new DragLabel(piece, this);
            newLabel->move(position);
            newLabel->show();
            newLabel->setAttribute(Qt::WA_DeleteOnClose);

            position += QPoint(newLabel->width(), 0);
        }

        event->acceptProposedAction();
    }
    else {
        event->ignore();
    }
}
//! [12]

//! [13]
void Editor::mousePressEvent(QMouseEvent* event)
{
    //! [13]
    //! [14]
    //DragLabel* child = static_cast<DragLabel*>(childAt(event->pos()));
    //if (!child)
    //    return;
    //
    //QPoint hotSpot = event->pos() - child->pos();
    //
    //QByteArray itemData;
    //QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    //dataStream << child->labelText() << QPoint(hotSpot);
    ////! [14]
    //
    ////! [15]
    //QMimeData* mimeData = new QMimeData;
    //mimeData->setData(fridgetMagnetsMimeType(), itemData);
    //mimeData->setText(child->labelText());
    ////! [15]
    //
    ////! [16]
    //QDrag* drag = new QDrag(this);
    //drag->setMimeData(mimeData);
    ////drag->setPixmap(*child->pixmap());
    //drag->setHotSpot(hotSpot);
    //
    //child->hide();
    ////! [16]
    //
    ////! [17]
    //if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
    //    child->close();
    //else
    //    child->show();
}
//! [17]