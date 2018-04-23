#include "mainwindow.h"
#include <QApplication>
#include "dbmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    DbManager dbManager("bazodanowa");
    MainWindow w;
    auto model = dbManager.GetModel(&w, "my_companies");
    w.setTableModel(model);
    w.show();

    return a.exec();
}
