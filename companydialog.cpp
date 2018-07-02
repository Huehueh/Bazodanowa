#include "companydialog.h"
#include "ui_companydialog.h"

#include "dbmanager.h"
#include "salepurchasedelegate.h"
#include <QDataWidgetMapper>
#include <QSqlRecord>

#include "enums.h"

#include "contractorsdialog.h"
#include "salepurchasedelegate.h"

SalePurchaseDialog::SalePurchaseDialog(int companyId, QWidget *parent)
    : QDialog(parent), ui(new Ui::CompanyDialog), mCompanyId(companyId), m_SelectedIndex(0) {
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

void SalePurchaseDialog::SetupDateEdit(QDateEdit *dateEdit)
{
  dateEdit->setCalendarPopup(true);
  auto calendar = dateEdit->calendarWidget();
  calendar->setWindowFlags(Qt::Popup);

  dateEdit->installEventFilter(this);
  dateEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
  connect(calendar, &QCalendarWidget::clicked, this,
          [dateEdit, calendar](QDate date) {
            dateEdit->setDate(date);
            calendar->hide();
          });
}

void SalePurchaseDialog::SetupSaleTab()
{
  auto view = ui->saleTableView;
  view->setModel(m_pSalesModel);
  view->setEditTriggers(QAbstractItemView::NoEditTriggers);
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  view->setSelectionMode(QAbstractItemView::SingleSelection);
  view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  view->selectRow(m_SelectedIndex);
  view->hideColumn(Sprzedaz::FirmaId);
  view->hideColumn(Sprzedaz::Id);
  // view->setItemDelegate(new SalePurchaseDelegate(view));
  CreateSalesMapper();

  connect(ui->addContractorButton, &QPushButton::clicked, this,
          &SalePurchaseDialog::OpenContractorDialog);
  connect(ui->saleTableView->selectionModel(),
          &QItemSelectionModel::currentRowChanged,this, [this](const QModelIndex& current){
      m_SelectedIndex = current.row();
  });





}

void SalePurchaseDialog::OpenContractorDialog() {
  int id = 0;
  auto onAccept = [&id](int value) {
    id = value;
  };
  ContractorsDialog *dialog = new ContractorsDialog(onAccept, this);
  dialog->exec();

  SelectContractor(id);
}

void SalePurchaseDialog::SelectContractor(int /*id*/)
{
    //auto model = DbManager::CreateContractorsModel();
    //auto contractor

    //ui->saleTableView->
}

void SalePurchaseDialog::SetupPurchaseTab() {
  auto view = ui->purchaseTableView;
  view->setModel(m_pPurchaseModel);
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  view->setSelectionMode(QAbstractItemView::SingleSelection);
  view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  view->selectRow(m_SelectedIndex);
  view->hideColumn(Zakup::FirmaId);
  view->hideColumn(Zakup::Id);
  // view->setItemDelegate(new SalePurchaseDelegate(view));
}

void SalePurchaseDialog::LoadKValues(QSqlTableModel* model, int minCol, int maxCol, QGridLayout* layout, QDataWidgetMapper* mapper)
{
    const int maxRowCount = 5;
    int columnNumber = 0;
    int rowNumber = 0;
    for(int i = minCol; i<maxCol; i++)
    {
        rowNumber = i-minCol - maxRowCount * qRound(0.5f * columnNumber);
        if(rowNumber >= maxRowCount)
        {
            columnNumber+=2;
            rowNumber = i-minCol - maxRowCount * qRound(0.5f * columnNumber);
        }
        auto header = m_pSalesModel->headerData(i, Qt::Horizontal).toString();
        layout->addWidget(new QLabel(header), rowNumber, columnNumber, Qt::AlignLeft);
        auto label = new QLineEdit();
        layout->addWidget(label, rowNumber, columnNumber+1, Qt::AlignLeft);
        mapper->addMapping(label, i);

    }
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

  LoadKValues(m_pSalesModel, 6, m_pSalesModel->columnCount(), ui->kGridLayout, mapper);

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
