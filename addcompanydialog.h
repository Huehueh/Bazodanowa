#ifndef ADDCOMPANYDIALOG_H
#define ADDCOMPANYDIALOG_H

#include <QDataWidgetMapper>
#include <QSqlTableModel>
#include <QWidget>

namespace Ui {
class AddCompanyDialog;
}

class AddCompanyDialog : public QWidget {
  Q_OBJECT

 public:
  explicit AddCompanyDialog(QSqlTableModel *model, QWidget *parent = nullptr);
  ~AddCompanyDialog();

 private:
  Ui::AddCompanyDialog *ui;
  QDataWidgetMapper *m_pMapper;
};

#endif  // ADDCOMPANYDIALOG_H
