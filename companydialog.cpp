#include "companydialog.h"
#include "ui_companydialog.h"

#include "dbmanager.h"
#include "salepurchasedelegate.h"
#include <QDataWidgetMapper>
#include <QSqlRecord>

#include "enums.h"

#include "salepurchasedelegate.h"

SalePurchaseDialog::SalePurchaseDialog(int companyId, QWidget *parent)
    : QDialog(parent), ui(new Ui::CompanyDialog), mCompanyId(companyId) {
  ui->setupUi(this);

  m_pSalesModel = DbManager::CreateSalesModel(mCompanyId);
  //  m_pSalesModel->setEditStrategy(QSqlTableModel::OnFieldChange);
  m_pPurchaseModel = DbManager::CreatePurchaseModel(mCompanyId);

  SetupSaleTab();
  SetupPurchaseTab();
}

SalePurchaseDialog::~SalePurchaseDialog() {
  delete ui;
  delete m_pSalesModel;
  delete m_pPurchaseModel;
}

void SalePurchaseDialog::SetupDateEdit(QDateEdit *dateEdit) {
  dateEdit->setCalendarPopup(true);
  auto calendar = dateEdit->calendarWidget();
  calendar->setWindowFlags(Qt::Popup);
  dateEdit->installEventFilter(this);
  dateEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
  connect(calendar, &QCalendarWidget::clicked,
          [dateEdit, calendar](QDate date) {
            dateEdit->setDate(date);
            calendar->hide();
          });
}

void SalePurchaseDialog::SetupSaleTab() {
  auto view = ui->saleTableView;
  view->setModel(m_pSalesModel);
  view->setEditTriggers(QAbstractItemView::NoEditTriggers);
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  view->setSelectionMode(QAbstractItemView::SingleSelection);
  view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  view->selectRow(0);
  view->hideColumn(Sprzedaz::FirmaId);
  view->hideColumn(Sprzedaz::Id);
  // view->setItemDelegate(new SalePurchaseDelegate(view));
  CreateSalesMapper();
}

void SalePurchaseDialog::SetupPurchaseTab() {
  auto view = ui->purchaseTableView;
  view->setModel(m_pPurchaseModel);
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  view->setSelectionMode(QAbstractItemView::SingleSelection);
  view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  view->selectRow(0);
  view->hideColumn(Zakup::FirmaId);
  view->hideColumn(Zakup::Id);
  // view->setItemDelegate(new SalePurchaseDelegate(view));
}

void SalePurchaseDialog::CreateSalesMapper() {
  // form
  auto mapper = new QDataWidgetMapper(this);
  mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
  mapper->setModel(m_pSalesModel);
  mapper->addMapping(ui->saleDateEdit, Sprzedaz::DataSprzedazy);
  SetupDateEdit(ui->saleDateEdit);
  mapper->addMapping(ui->issueDateEdit, Sprzedaz::DataWystawienia);
  SetupDateEdit(ui->issueDateEdit);
  mapper->addMapping(ui->invoiceEdit, Sprzedaz::DowodSprzedazy);
  mapper->addMapping(ui->contractorBox, Sprzedaz::KontrahentId);

  auto contractorModel = DbManager::CreateContractorsModel();
  QStringList contractorNames;
  for (int i = 0; i < contractorModel->rowCount(); ++i) {
    contractorNames.append(
        contractorModel->record(i).value(Kontrahent::Nazwa).toString());
  }
  contractorModel->deleteLater();
  ui->contractorBox->addItems(contractorNames);

  mapper->setItemDelegate(new SalePurchaseDelegate(mapper));
  mapper->toFirst();

  connect(ui->saleTableView->selectionModel(),
          &QItemSelectionModel::currentRowChanged,
          [mapper](const QModelIndex &index) {
            mapper->setCurrentIndex(index.row());
          });
}
bool SalePurchaseDialog::eventFilter(QObject *object, QEvent *event) {
  if (event->type() == QEvent::InputMethodQuery) {
    auto dateEdit = qobject_cast<QDateEdit *>(object);
    if (dateEdit && !dateEdit->calendarWidget()->isVisible()) {
      dateEdit->calendarWidget()->move(
          dateEdit->mapToGlobal(QPoint(0, dateEdit->height())));
      dateEdit->calendarWidget()->show();
      return true;
    }
  }
  return false;
}
