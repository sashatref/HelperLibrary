#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QDialog>

namespace Ui {
class InfoWindow;
}

class InfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InfoWindow(const QString &_text, const QString &_caption = "Info", QWidget *parent = 0);
    ~InfoWindow();

private slots:
    void on_closeButton_clicked();

private:
    Ui::InfoWindow *ui;
};

#endif // INFOWINDOW_H
