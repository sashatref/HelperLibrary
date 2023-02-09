#include "imagelistwidget.h"

#include <QScrollBar>
#include <QPainter>

ImageListWidget::ImageListWidget(QWidget *_parent):
    QListWidget         (_parent),
    m_backgroundImage   (),
    m_imageOpacity      (1.0),
    m_padding           (0, 0)
{
    connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &ImageListWidget::onSliderChanged);
    connect(horizontalScrollBar(), &QScrollBar::valueChanged, this, &ImageListWidget::onSliderChanged);
}

void ImageListWidget::setBackgroundPixmap(const QPixmap &_pixmap)
{
    m_backgroundImage = _pixmap;
    repaint();
}

QPixmap ImageListWidget::getBackgorundPixmap() const
{
    return m_backgroundImage;
}

void ImageListWidget::setImageOpacity(double _opacity)
{
    m_imageOpacity = _opacity;
    repaint();
}

double ImageListWidget::getImageOpacity() const
{
    return m_imageOpacity;
}

void ImageListWidget::setImagePadding(const QSize &_size)
{
    m_padding = _size;
    repaint();
}

QSize ImageListWidget::getImagePadding() const
{
    return m_padding;
}

void ImageListWidget::onSliderChanged(int /*_value*/)
{
    viewport()->repaint();
}


void ImageListWidget::paintEvent(QPaintEvent *event)
{
    QListWidget::paintEvent(event);

    QPainter painter(viewport());
    if(m_backgroundImage.isNull()) {return;}

    painter.setOpacity(m_imageOpacity);

    QImage img = m_backgroundImage.scaled(viewport()->size() - QSize(m_padding.width() * 2, m_padding.height() * 2), Qt::KeepAspectRatio).toImage();
    painter.drawImage(m_padding.width(), viewport()->height() - img.height() - m_padding.height(), img);
}
