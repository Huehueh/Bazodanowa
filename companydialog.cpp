#include "companydialog.h"
#include "ui_companydialog.h"

#include "dbmanager.h"
#include "salepurchasedelegate.h"

CompanyDialog::CompanyDialog(int companyId, QWidget *parent)
    : QDialog(parent), ui(new Ui::CompanyDialog), mCompanyId(companyId) {
  ui->setupUi(this);
  SetupSaleTab();
}

CompanyDialog::~CompanyDialog() { delete ui; }

void CompanyDialog::SetupSaleTab() {
  auto saleTableView = ui->saleTableView;
  saleTableView->setItemDelegate(new SalePurchaseDelegate());
  auto model = DbManager::CreateSalesModel(mCompanyId);
  saleTableView->setModel(model);
}

void CompanyDialog::SetupPurchaseTab() {}
