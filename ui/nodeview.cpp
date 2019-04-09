#include "nodeview.h"

#include <QWheelEvent>
#include <QScrollBar>
#include <QDebug>

NodeView::NodeView(QGraphicsScene *scene, QWidget *parent) :
  QGraphicsView(scene, parent),
  hand_moving_(false)
{
  setMouseTracking(true);
  setWindowTitle(tr("Node Editor"));

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void NodeView::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::MidButton) {
    hand_moving_ = true;
    drag_start_ = event->pos();
  } else {
    QGraphicsView::mousePressEvent(event);
  }
}

void NodeView::mouseMoveEvent(QMouseEvent *event)
{
  if (hand_moving_) {
    QPoint delta = event->pos() - drag_start_;

    horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
    verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());

    drag_start_ = event->pos();
  } else {
    QGraphicsView::mouseMoveEvent(event);
  }
}

void NodeView::mouseReleaseEvent(QMouseEvent *event)
{
  if (!hand_moving_) {
    hand_moving_ = false;
    QGraphicsView::mouseReleaseEvent(event);
  }
}

void NodeView::wheelEvent(QWheelEvent *event)
{
  if (event->angleDelta().y() > 0) {
    scale(0.9, 0.9);
  } else {
    scale(1.1, 1.1);
  }
}
