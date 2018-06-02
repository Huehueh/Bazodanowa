#ifndef ADDCOMPANYDIALOG_H
#define ADDCOMPANYDIALOG_H

#include <QDataWidgetMapper>
#include <QDialog>
#include <QModelIndex>
#include <QSqlTableModel>

namespace Ui {
class AddCompanyDialog;
}

class AddCompanyDialog : public QDialog {
  Q_OBJECT

 public:
  explicit AddCompanyDialog(QSqlTableModel *model, QWidget *parent = nullptr);
  ~AddCompanyDialog();

 private slots:
  void OnAccept();
  void OnCancel();

 private:
  void createUi();

  Ui::AddCompanyDialog *ui;
  QSqlTableModel *m_pModel;
  QDataWidgetMapper *m_pMapper;
  QModelIndex m_Index;
};

#endif  // ADDCOMPANYDIALOG_H
