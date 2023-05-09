#include "infowidgit.h"

InfoWidgit::InfoWidgit(QWidget *parent)
    : QWidget{parent}
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    info = "";

    this->form.setTitle("Информация");

    connect(this, &InfoWidgit::customContextMenuRequested, [=](){
        QMenu contextMenu(tr("Меню"), this);
        QAction action1("Больше информации...", this);

        connect( &action1, &QAction::triggered, [&](){
            form.setText(info);
            form.show();
        });

        contextMenu.addAction(&action1);
        contextMenu.exec(mapToGlobal(this->mapFromGlobal(this->cursor().pos())));
    });
}

void InfoWidgit::setTextInfo(QString info)
{
    this->info = info;
}

InfoWidgit::~InfoWidgit()
{

}
