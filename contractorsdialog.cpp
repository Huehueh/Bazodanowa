#include "contractorsdialog.h"
#include "ui_contractorsdialog.h"

#include "dbmanager.h"
#include "enums.h"

#include <QDialogButtonBox>
#include <QPushButton>

ContractorsDialog::ContractorsDialog(std::function<void(int)> onAccept,
                                     QWidget *parent)
    : QDialog(parent), ui(new Ui::ContractorsDialog) {
  ui->setupUi(this);

  auto tableModel = DbManager::CreateContractorsModel();
  ui->contractorsView->setModel(tableModel);

  SetupUi();

  connect(
      ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this,
      [&onAccept, this]() {
        auto selectedRow =
            ui->contractorsView->selectionModel()->selectedRows().at(0).row();
        onAccept(selectedRow);
      });
}

ContractorsDialog::~ContractorsDialog() { delete ui; }

void ContractorsDialog::SetupUi() {
  auto view = ui->contractorsView;
  view->setEditTriggers(QAbstractItemView::NoEditTriggers);
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  view->setSelectionMode(QAbstractItemView::SingleSelection);
  view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  view->hideColumn(Kontrahent::Id);
  view->selectRow(0);

}
