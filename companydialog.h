#ifndef COMPANYDIALOG_H
#define COMPANYDIALOG_H

#include <QCalendarWidget>
#include <QDateEdit>
#include <QDialog>
#include <QSqlTableModel>
#include <memory>

namespace Ui {
class CompanyDialog;
}

class SalePurchaseDialog : public QDialog {
  Q_OBJECT

public:
  SalePurchaseDialog(int companyId, QWidget *parent = nullptr);
  ~SalePurchaseDialog();

protected:
  bool eventFilter(QObject *object, QEvent *event) override;

private:
  void SetupSaleTab();
  void SetupPurchaseTab();
  void CreateSalesMapper();

  void SetupDateEdit(QDateEdit *dateEdit);

  Ui::CompanyDialog *ui = nullptr;
  int mCompanyId;
  QSqlTableModel *m_pSalesModel = nullptr;
  QSqlTableModel *m_pPurchaseModel = nullptr;
};

#endif // COMPANYDIALOG_H
