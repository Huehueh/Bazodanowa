#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <dbmanager.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void OnAddButtonClicked();
  void OnRemoveButtonClicked();
  void OnOpenButtonClicked();

private:
  void MakeConnections();
  void CreateMapper();
  void SetupTableView();

  Ui::MainWindow *ui;
  QSqlTableModel *m_tableModel;
};

#endif // MAINWINDOW_H
