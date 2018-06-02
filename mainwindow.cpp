#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "addcompanydialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QTableView>

#include "companydialog.h"
#include "enums.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  m_tableModel = DbManager::CreateMyCompaniesModel();
  m_tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

  auto view = ui->companiesTableView;
  view->setModel(m_tableModel);
  view->hideColumn(0); // id
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  view->setSelectionMode(QAbstractItemView::SingleSelection);
  view->selectRow(0);

  // form
  auto mapper = new QDataWidgetMapper();
  mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
  mapper->setModel(m_tableModel);
  mapper->toFirst();

  connect(view, &QTableView::pressed, [&, mapper](const QModelIndex &index) {
    mapper->setCurrentIndex(index.row());
  });

  mapper->addMapping(ui->shortNameLineEdit, MojaFirma::Skrot);
  mapper->addMapping(ui->nameLineEdit, MojaFirma::Nazwa);
  mapper->addMapping(ui->nipLineEdit, MojaFirma::NIP);
  mapper->addMapping(ui->emailLineEdit, MojaFirma::Email);

  connect(ui->addButton, &QPushButton::clicked, this,
          &MainWindow::OnAddButtonClicked);

  connect(ui->openButton, &QPushButton::clicked, this,
          &MainWindow::OnOpenButtonClicked);

  connect(ui->removeButton, &QPushButton::clicked, this,
          &MainWindow::OnRemoveButtonClicked);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::OnOpenButtonClicked() {
  auto view = ui->companiesTableView;
  auto selection = view->selectionModel()->selectedRows().at(0);
  int selectedRow = selection.row();

  auto dialog = new CompanyDialog(selectedRow, this);
  dialog->exec();
}

void MainWindow::OnAddButtonClicked() {
  AddCompanyDialog *dialog = new AddCompanyDialog(m_tableModel, this);
  dialog->exec();
}

void MainWindow::OnRemoveButtonClicked() {
  auto view = ui->companiesTableView;
  auto selection = view->selectionModel()->selectedRows();
  for (const auto &index : selection) {
    auto model = index.model();
    auto name =
        model->data(model->index(index.row(), MojaFirma::Nazwa)).toString();

    auto removed = m_tableModel->removeRow(index.row());
    if (removed) {
      QMessageBox box(QMessageBox::Information, tr("Info"),
                      name + tr(" firma usunięta"), QMessageBox::Ok, this);
      box.exec();
    }
  }
  m_tableModel->submitAll();
  m_tableModel->database().commit();
  m_tableModel->select();
  view->update();
}
