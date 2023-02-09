#pragma once

#include "../export.h"

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT IndependentWidgetHolder : public QObject
{
    Q_OBJECT
public:
    IndependentWidgetHolder(QObject *_parent = nullptr);

    void registerIndependentWindow(QWidget *_independentWidnow);

    void closeIndependentWindows();

private:
    QWidgetList m_independentWidgets;
};

}
