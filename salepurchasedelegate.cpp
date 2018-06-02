#include "salepurchasedelegate.h"

#include <QDateEdit>
#include <QLineEdit>

#include "enums.h"

SalePurchaseDelegate::SalePurchaseDelegate(QObject *parent)
    : QSqlRelationalDelegate(parent) {}

QWidget *SalePurchaseDelegate::createEditor(QWidget *parent,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const {
  auto role = static_cast<Sprzedaz::eData>(index.column());
  switch (role) {
  case Sprzedaz::DataSprzedazy:
  case Sprzedaz::DataWystawienia: {
    return new QDateEdit(parent);
  }
  default: {
    return QSqlRelationalDelegate::createEditor(parent, option, index);
  }
  }
}

void SalePurchaseDelegate::setEditorData(QWidget *editor,
                                         const QModelIndex &index) const {
  auto role = static_cast<Sprzedaz::eData>(index.column());
  switch (role) {
  case Sprzedaz::DataSprzedazy:
  case Sprzedaz::DataWystawienia: {
    auto value = index.model()->data(index, Qt::EditRole).toString();
    QDateEdit *dateEdit = static_cast<QDateEdit *>(editor);
    QDate date = QDate::fromString(value, dateFormat);
    dateEdit->setDate(date);
    break;
  }

  default: { break; }
  }
}

void SalePurchaseDelegate::setModelData(QWidget *editor,
                                        QAbstractItemModel *model,
                                        const QModelIndex &index) const {
  auto role = static_cast<Sprzedaz::eData>(index.column());
  switch (role) {
  case Sprzedaz::DataSprzedazy:
  case Sprzedaz::DataWystawienia: {
    QDateEdit *dateEdit = static_cast<QDateEdit *>(editor);
    QDate date = dateEdit->date();
    auto value = date.toString(dateFormat);
    model->setData(index, value, Qt::EditRole);
    break;
  }

  default: { break; }
  }
}
