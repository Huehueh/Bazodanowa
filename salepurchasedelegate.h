#ifndef SALEPURCHASEDELEGATE_H
#define SALEPURCHASEDELEGATE_H

#include <QSqlRelationalDelegate>

class SalePurchaseDelegate : public QSqlRelationalDelegate {
  Q_OBJECT
public:
  SalePurchaseDelegate(QObject *parent = nullptr);
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;

signals:

public slots:

private:
  const QString dateFormat = "yyyy-MM-dd";
};

#endif // SALEPURCHASEDELEGATE_H
