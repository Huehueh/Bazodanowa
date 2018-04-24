#include "addcompanydialog.h"
#include "ui_addcompanydialog.h"

#include <QSqlRecord>

AddCompanyDialog::AddCompanyDialog(QSqlTableModel* model, QWidget* parent)
    : QDialog(parent),
      ui(new Ui::AddCompanyDialog),
      m_pModel(model),
      m_pMapper(nullptr) {
  ui->setupUi(this);

  m_pMapper = new QDataWidgetMapper();
  m_pMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
  m_pMapper->setModel(model);

  m_pMapper->addMapping(ui->nameLineEdit, 1);
  m_pMapper->addMapping(ui->nipLineEdit, 2);
  m_pMapper->addMapping(ui->addressLineEdit, 3);
  m_pMapper->addMapping(ui->emailLineEdit, 4);

  connect(ui->okButton, &QPushButton::clicked, this,
          &AddCompanyDialog::OnAccept);
  connect(ui->cancelButton, &QPushButton::clicked, this,
          &AddCompanyDialog::OnCancel);
}

void AddCompanyDialog::OnAccept() {
  int row = m_pMapper->currentIndex();
  m_pMapper->submit();
  m_pModel->insertRow(row);
  m_pMapper->setCurrentIndex(row);
  accept();
}

void AddCompanyDialog::OnCancel() { reject(); }

AddCompanyDialog::~AddCompanyDialog() { delete ui; }
