#include "dbmanager.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  DbManager::CreateInstance("db/bazodanowa.db");
  MainWindow w;
  w.show();

  return a.exec();
}
