#pragma once

#include <QWhatsThis>

#include "../export.h"

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT WhatiIsThisToolButton : public QToolButton
{
    Q_OBJECT
public:
    WhatiIsThisToolButton(QWidget *_parent = nullptr);
};

}
