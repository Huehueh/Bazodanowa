#include "addcompanydialog.h"
#include "ui_addcompanydialog.h"

#include <QLineEdit>
#include <QModelIndex>
#include <QRegExpValidator>
#include <QSqlRecord>
#include <QSqlTableModel>

#include "enums.h"

AddCompanyDialog::AddCompanyDialog(QSqlTableModel *model, QWidget *parent)
    : QDialog(parent), ui(new Ui::AddCompanyDialog), m_pModel(model),
      m_pMapper(nullptr) {
  ui->setupUi(this);

  m_pMapper = new QDataWidgetMapper();
  m_pMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
  m_pMapper->setModel(model);
  model->insertRow(model->rowCount(QModelIndex()));
  m_pMapper->toLast();

  // name
  m_pMapper->addMapping(ui->nameLineEdit, MojaFirma::Nazwa);

  // nip
  m_pMapper->addMapping(ui->nipLineEdit, MojaFirma::NIP);
  QRegExp rx("[0-9]\\d{0,9}");
  auto validator = new QRegExpValidator(rx, this);
  ui->nipLineEdit->setValidator(validator);

  // address
  m_pMapper->addMapping(ui->addressLineEdit, MojaFirma::Adres);

  // email
  m_pMapper->addMapping(ui->emailLineEdit, MojaFirma::Email);

  connect(ui->okButton, &QPushButton::clicked, this,
          &AddCompanyDialog::OnAccept);
  connect(ui->cancelButton, &QPushButton::clicked, this,
          &AddCompanyDialog::OnCancel);
}

void AddCompanyDialog::OnAccept() {
  m_pMapper->submit();
  m_pModel->submitAll();
  close();
}

void AddCompanyDialog::OnCancel() {
  m_pModel->removeRow(-1, m_Index);
  close();
}

AddCompanyDialog::~AddCompanyDialog() { delete ui; }
