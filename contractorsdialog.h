#ifndef CONTRACTORSDIALOG_H
#define CONTRACTORSDIALOG_H

#include <QDialog>
#include <functional>

namespace Ui {
class ContractorsDialog;
}

class ContractorsDialog : public QDialog {
  Q_OBJECT

public:
  ContractorsDialog(std::function<void(int)> onAccept,
                    QWidget *parent = nullptr);
  ~ContractorsDialog();

private:
  Ui::ContractorsDialog *ui;

  void SetupUi();
};

#endif // CONTRACTORSDIALOG_H
