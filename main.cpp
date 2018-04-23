#include "dbmanager.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  DbManager dbManager("database/bazodanowa.db");
  MainWindow w(dbManager);
  w.show();

  return a.exec();
}
