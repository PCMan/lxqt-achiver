#include <QHeaderView>
#include <QMouseEvent>
#include <QApplication>

#include "filetreeView.h"

FileTreeView::FileTreeView(QWidget* parent) : QTreeView(parent) {
    dragStarted_ = false;
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setIconSize(QSize(24, 24));
    setRootIsDecorated(false);
    setDragDropMode(QAbstractItemView::DragOnly);
    header()->setSortIndicatorShown(true);
    header()->setStretchLastSection(false);
    header()->setSortIndicatorShown(true);
    header()->setSortIndicator(0, Qt::AscendingOrder);
}

void FileTreeView::mousePressEvent(QMouseEvent* event) {
    QTreeView::mousePressEvent(event);
    if (event->button() == Qt::LeftButton && indexAt(event->pos()).isValid()) {
        dragStartPosition_ = event->pos();
    }
    else {
        dragStartPosition_ = QPoint();
    }
    dragStarted_ = false;
}

void FileTreeView::mouseMoveEvent(QMouseEvent* event) {
    if(dragStartPosition_.isNull()) {
        QTreeView::mouseMoveEvent(event);
        return;
    }
    if((event->pos() - dragStartPosition_).manhattanLength() >= qMax(16, QApplication::startDragDistance())) {
        dragStarted_ = true;
    }

    if((event->buttons() & Qt::LeftButton) && dragStarted_) {
        if(selectionModel() && !selectionModel()->selectedRows().isEmpty()) {
            Q_EMIT dragStarted();
        }
        event->accept();
    }
}
