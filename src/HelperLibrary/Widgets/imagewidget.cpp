#include "imagewidget.h"

#include <QPainter>

ImageWidget::ImageWidget(QWidget *parent) :
    QWidget             (parent),
    m_imageOpacity      (1),
    m_padding           (QSize(0,0))
{

}

void ImageWidget::setBackgroundPixmap(const QPixmap &_pixmap)
{
    m_backgroundImage = _pixmap;
    update();
}

QPixmap ImageWidget::getBackgorundPixmap() const
{
    return m_backgroundImage;
}

void ImageWidget::setImageOpacity(double _opacity)
{
    m_imageOpacity = _opacity;
    update();
}

double ImageWidget::getImageOpacity() const
{
    return m_imageOpacity;
}

void ImageWidget::setImagePadding(const QSize &_size)
{
    m_padding = _size;
    update();
}

QSize ImageWidget::getImagePadding() const
{
    return m_padding;
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if(m_backgroundImage.isNull()) {return;}

    QPainter painter(this);
    painter.setOpacity(m_imageOpacity);

    QImage img = m_backgroundImage.scaled(this->size() - QSize(m_padding.width() * 2, m_padding.height() * 2), Qt::KeepAspectRatio).toImage();
    painter.drawImage(m_padding.width(), this->height() - img.height() - m_padding.height(), img);
}
