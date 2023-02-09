#pragma once

#include <QWidget>

#include "../export.h"

class HELPERLIBRARY_EXPORT ImageWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPixmap backgroundImage READ getBackgorundPixmap WRITE setBackgroundPixmap)
    Q_PROPERTY(double imageOpacity READ getImageOpacity WRITE setImageOpacity)
    Q_PROPERTY(QSize imagePadding READ getImagePadding WRITE setImagePadding)
public:
    explicit ImageWidget(QWidget *parent = 0);

    void setBackgroundPixmap(const QPixmap &_pixmap);
    QPixmap getBackgorundPixmap() const;

    void setImageOpacity(double _opacity);
    double getImageOpacity() const;

    void setImagePadding(const QSize &_size);
    QSize getImagePadding() const;

    virtual void paintEvent(QPaintEvent *event) override;

private:
    QPixmap m_backgroundImage;
    double m_imageOpacity;
    QSize m_padding;
};

