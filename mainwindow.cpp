#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "addcompanydialog.h"
#include <QDebug>
#include <QHeaderView>
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

  SetupTableView();
  CreateMapper();
  MakeConnections();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::SetupTableView() {
  auto view = ui->companiesTableView;
  view->setModel(m_tableModel);
  view->hideColumn(0); // id
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  view->setSelectionMode(QAbstractItemView::SingleSelection);
  view->selectRow(0);
  view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void MainWindow::CreateMapper() {
  // form
  auto mapper = new QDataWidgetMapper();
  mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
  mapper->setModel(m_tableModel);
  mapper->addMapping(ui->shortNameLineEdit, MojaFirma::Skrot);
  mapper->addMapping(ui->nameLineEdit, MojaFirma::Nazwa);
  mapper->addMapping(ui->nipLineEdit, MojaFirma::NIP);
  mapper->addMapping(ui->emailLineEdit, MojaFirma::Email);
  mapper->toFirst();

  connect(ui->companiesTableView->selectionModel(),
          &QItemSelectionModel::currentRowChanged,
          [mapper](const QModelIndex &index) {
            mapper->setCurrentIndex(index.row());
          });
}

void MainWindow::MakeConnections() {
  connect(ui->addButton, &QPushButton::clicked, this,
          &MainWindow::OnAddButtonClicked);
  connect(ui->openButton, &QPushButton::clicked, this,
          &MainWindow::OnOpenButtonClicked);
  connect(ui->removeButton, &QPushButton::clicked, this,
          &MainWindow::OnRemoveButtonClicked);
}

void MainWindow::OnOpenButtonClicked() {

  auto selectedRow =
      ui->companiesTableView->selectionModel()->selectedRows().at(0).row() +
      1; // TODO zmienić na wartosc kolumny 0

  auto dialog = new SalePurchaseDialog(selectedRow, this);
  dialog->exec();
}

void MainWindow::OnAddButtonClicked() {
  AddCompanyDialog *dialog = new AddCompanyDialog(m_tableModel, this);
  auto result = dialog->exec();
  auto last = m_tableModel->rowCount() - 1;

  if (result == QDialog::Accepted) {
    ui->companiesTableView->selectRow(last);
    ui->companiesTableView->scrollTo(m_tableModel->index(last, 0));
  }
}

void MainWindow::OnRemoveButtonClicked() {
  auto selection = ui->companiesTableView->selectionModel()->selectedRows();

  int deletedRowIndex = -1;
  for (const auto &index : selection) {
    auto model = index.model();
    auto name =
        model->data(model->index(index.row(), MojaFirma::Nazwa)).toString();

    deletedRowIndex = index.row();
    auto removed = m_tableModel->removeRow(deletedRowIndex);
    if (removed) {
      QMessageBox box(QMessageBox::Information, tr("Info"),
                      name + tr(" firma usunięta"), QMessageBox::Ok, this);
      box.exec();

      m_tableModel->submitAll();
      m_tableModel->database().commit();
      m_tableModel->select();
      if (deletedRowIndex > 1) {
        m_tableModel->selectRow(deletedRowIndex - 1);
      } else if (m_tableModel->rowCount() > 0) {
        ui->companiesTableView->selectRow(deletedRowIndex - 1);
        ui->companiesTableView->scrollTo(
            m_tableModel->index(deletedRowIndex - 1, 0));
      }
      ui->companiesTableView->update();
    }
  }
}
