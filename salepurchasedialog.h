#ifndef SALEPURCHASEDIALOG_H
#define SALEPURCHASEDIALOG_H

#include <QCalendarWidget>
#include <QDateEdit>
#include <QDialog>
#include <QSqlTableModel>
#include <memory>
#include <QGridLayout>
#include <QDataWidgetMapper>

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

private slots:
  void OpenContractorDialog();

private:
  void SetupSaleTab();
  void SetupPurchaseTab();
  void CreateSalesMapper();
  void CreatePurchaseMapper();
  void SetupDateEdit(QDateEdit *dateEdit);
  void SelectContractor(int id);
  void LoadKValues(QSqlTableModel* model, int minCol, int maxCol, QGridLayout* layout, QDataWidgetMapper* mapper);

  Ui::CompanyDialog *ui = nullptr;
  int mCompanyId;
  QSqlTableModel *m_pSalesModel = nullptr;
  QSqlTableModel *m_pPurchaseModel = nullptr;
  int m_SelectedIndex;
};

#endif // SALEPURCHASEDIALOG_H
