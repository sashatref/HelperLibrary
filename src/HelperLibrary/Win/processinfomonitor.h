#pragma once

#include <QWidget>

#include "../Widgets/extendedwidget.h"

namespace Ui {
class ProcessInfoMonitor;
}

class HELPERLIBRARY_EXPORT ProcessInfoMonitor : public ExtendedWidget
{
    Q_OBJECT
public:
    explicit ProcessInfoMonitor(QWidget *parent = nullptr);
    ~ProcessInfoMonitor();

private slots:
    void timedoutSlot();
    void on_updateIntervalSpinbox_valueChanged(int arg1);

private:
    void updateView();

    QTimer *m_timer = nullptr;
    Ui::ProcessInfoMonitor *ui;

public:
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;
    virtual void updateLanguage() override;
    virtual void updateStyle() override;
    virtual void initUiComponets() override;
    virtual void initConnections() override;
};
