#pragma once

#include <QDialog>

#include "../export.h"

namespace Ui {
class InfoWindow;
}

namespace HelperLibrary
{
    namespace UserExceptions
    {
        class BaseException;
    }
}

class HELPERLIBRARY_EXPORT InfoWindow : public QDialog
{
    Q_OBJECT
public:
    explicit InfoWindow(const QString &_text, const QString &_caption = "Info", const QSize &_formSize = QSize(600,300), QWidget *parent = 0);
    explicit InfoWindow(QWidget *_parent, const QString &_text);
    explicit InfoWindow(const HelperLibrary::UserExceptions::BaseException &e, QWidget *_parent);
    ~InfoWindow();

private slots:
    void on_closeButton_clicked();

private:
    Ui::InfoWindow *ui;
};
