#include "../Styles/iconsenum.h"
#include "../functions.h"
#include "showiconsform.h"
#include "ui_showiconsform.h"

void ShowIconsForm::initElements()
{
    ui->listWidget->clear();

    const QSize size = QSize(ui->sizeSpinBox->value(), ui->sizeSpinBox->value());


    for(uint i = QStyle::SP_TitleBarMenuButton ; i <= QStyle::SP_LineEditClearButton; i++)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        const QString text = Text::enumToString(i, &QStyle::staticMetaObject, "StandardPixmap");
        item->setText(text);
        item->setIcon(IconsEnum::getIcon(i));
        item->setSizeHint(size);
    }


    for(uint i = IconsEnum::BaseIcon ; i < IconsEnum::SP_Max_Value; i++)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        const QString text = Text::enumToString(i, &IconsEnum::staticMetaObject, "Icons");
        item->setText(text);
        item->setIcon(IconsEnum::getIcon(i));
        item->setSizeHint(size);
    }
}

ShowIconsForm::ShowIconsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowIconsForm)
{
    ui->setupUi(this);

    initElements();
}

ShowIconsForm::~ShowIconsForm()
{
    delete ui;
}


void ShowIconsForm::changeEvent(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::StyleChange:
        initElements();
        break;
    default:
        break;
    }
}

void ShowIconsForm::on_sizeSpinBox_valueChanged(int)
{
    initElements();
}
