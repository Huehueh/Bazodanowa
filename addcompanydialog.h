#ifndef ADDCOMPANYDIALOG_H
#define ADDCOMPANYDIALOG_H

#include <QDataWidgetMapper>
#include <QDialog>
#include <QModelIndex>
#include <QSqlTableModel>

namespace Ui {
class AddCompanyDialog;
}

enum CompanyType { Main, Contactor };

class AddCompanyDialog : public QDialog {
  Q_OBJECT

public:
  explicit AddCompanyDialog(CompanyType company, QWidget *parent = nullptr);
  ~AddCompanyDialog();

private slots:
  void OnAccept();
  void OnCancel();

private:
  void CreateUi();

  Ui::AddCompanyDialog *ui;
  QSqlTableModel *m_pModel;
  QDataWidgetMapper *m_pMapper;
  QModelIndex m_Index;
  CompanyType m_CompanyType;
};

#endif // ADDCOMPANYDIALOG_H
