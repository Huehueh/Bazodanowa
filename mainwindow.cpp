#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include "addcompanydialog.h"

MainWindow::MainWindow(DbManager &manager, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), pDbManager(&manager) {
  ui->setupUi(this);
  m_tableModel = CreateTableModel();

  auto view = ui->companiesTableView;
  view->setModel(m_tableModel);
  view->hideColumn(0);  // id

  connect(ui->addButton, &QPushButton::clicked, this,
          &MainWindow::OnAddButtonClicked);
}

MainWindow::~MainWindow() { delete ui; }

QSqlTableModel *MainWindow::CreateTableModel() {
  QSqlDatabase db = QSqlDatabase::database();
  QSqlTableModel *model = new QSqlTableModel(this, db);
  model->setTable("my_companies");
  model->setEditStrategy(QSqlTableModel::OnManualSubmit);
  model->select();

  model->setHeaderData(1, Qt::Horizontal, tr("Nazwa firmy"));
  model->setHeaderData(2, Qt::Horizontal, tr("NIP"));
  model->setHeaderData(3, Qt::Horizontal, tr("Adres"));
  model->setHeaderData(4, Qt::Horizontal, tr("Email"));

  return model;
}

void MainWindow::OnAddButtonClicked() {
  AddCompanyDialog *dialog = new AddCompanyDialog(m_tableModel, this);
  dialog->show();
}
