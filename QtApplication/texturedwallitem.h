#ifndef TEXTUREDWALLITEM_H
#define TEXTUREDWALLITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QImage>

class TexturedWallItem : public QGraphicsItem
{
public:
    TexturedWallItem(QPointF tl, QPointF tr, QPointF br, QPointF bl, const QPixmap& texture);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;

private:
    QPointF m_tl, m_tr, m_br, m_bl;
    QPixmap m_texture;
    QImage  m_image;
    QRectF  m_bounds;
};

#endif
