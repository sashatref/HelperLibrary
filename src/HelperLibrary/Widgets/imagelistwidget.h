#pragma once

#include <QListWidget>

#include "../export.h"

class HELPERLIBRARY_EXPORT ImageListWidget : public QListWidget
{
    Q_OBJECT
    Q_PROPERTY(QPixmap backgroundImage READ getBackgorundPixmap WRITE setBackgroundPixmap)
    Q_PROPERTY(double imageOpacity READ getImageOpacity WRITE setImageOpacity)
    Q_PROPERTY(QSize imagePadding READ getImagePadding WRITE setImagePadding)
public:
    ImageListWidget(QWidget *_parent);

    void setBackgroundPixmap(const QPixmap &_pixmap);
    QPixmap getBackgorundPixmap() const;

    void setImageOpacity(double _opacity);
    double getImageOpacity() const;

    void setImagePadding(const QSize &_size);
    QSize getImagePadding() const;

public slots:
    void onSliderChanged(int _value);

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QPixmap m_backgroundImage;
    double m_imageOpacity;
    QSize m_padding;
};

