#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <dbmanager.h>
#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(DbManager &manager, QWidget *parent = 0);
  ~MainWindow();
  QSqlTableModel *CreateTableModel();

 private slots:
  void OnAddButtonClicked();

 private:
  Ui::MainWindow *ui;
  DbManager *pDbManager;
  QSqlTableModel *m_tableModel;
};

#endif  // MAINWINDOW_H
