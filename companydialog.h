#ifndef COMPANYDIALOG_H
#define COMPANYDIALOG_H

#include <QDialog>

namespace Ui {
class CompanyDialog;
}

class CompanyDialog : public QDialog {
  Q_OBJECT

public:
  explicit CompanyDialog(int companyId, QWidget *parent = nullptr);
  ~CompanyDialog();

private:
  Ui::CompanyDialog *ui;
  int mCompanyId;
  void SetupSaleTab();
  void SetupPurchaseTab();
};

#endif // COMPANYDIALOG_H
