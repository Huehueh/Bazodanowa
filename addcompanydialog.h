#ifndef ADDCOMPANYDIALOG_H
#define ADDCOMPANYDIALOG_H

#include <QDataWidgetMapper>
#include <QDialog>
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
  Ui::AddCompanyDialog *ui;
  QSqlTableModel *m_pModel;
  QDataWidgetMapper *m_pMapper;
};

#endif  // ADDCOMPANYDIALOG_H
