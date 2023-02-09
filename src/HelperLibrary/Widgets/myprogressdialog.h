#pragma once
#include <QProgressDialog>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>

#include "widgethelper.h"
#include "../export.h"

class HELPERLIBRARY_EXPORT MyProgressDialog : public QProgressDialog
{
public:
    MyProgressDialog(QWidget *parent = 0,
                     const QString &_label = tr("Загрузка данных"),
                     const QString &_title = tr("Загрузка данных"),
                     const QString &_cancelText = tr("Отмена"),
                     int minimumDuration = 1000);

    static MyProgressDialog *createContinuousDialog(
            QWidget *parent = 0,
            const QString &_label = tr("Загрузка данных"),
            const QString &_title = tr("Загрузка данных"),
            const QString &_cancelText = tr("Отмена"),
            int minimumDuration = 3000);

public slots:
    void onUpdateStarted();
    void onUpdateProgress(int _current, int _total);
    void onUpdateFinished();
};

