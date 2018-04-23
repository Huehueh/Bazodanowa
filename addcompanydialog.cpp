#include "addcompanydialog.h"
#include "ui_addcompanydialog.h"

AddCompanyDialog::AddCompanyDialog(QSqlTableModel* model, QWidget* parent)
    : QWidget(parent), ui(new Ui::AddCompanyDialog), m_pMapper(nullptr) {
  ui->setupUi(this);

  m_pMapper = new QDataWidgetMapper();
  m_pMapper->setModel(model);

  m_pMapper->addMapping(ui->nameLineEdit, 1);
  m_pMapper->addMapping(ui->nipLineEdit, 2);
  m_pMapper->addMapping(ui->addressLineEdit, 3);
  m_pMapper->addMapping(ui->emailLineEdit, 4);
  m_pMapper->toFirst();
}

AddCompanyDialog::~AddCompanyDialog() { delete ui; }
