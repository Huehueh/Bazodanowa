#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QString>

class DbManager {
public:
  static DbManager *CreateInstance(const QString &path);
  static DbManager *Instance();
  static QSqlTableModel *CreateMyCompaniesModel();
  static QSqlTableModel *CreateContractorsModel();
  static QSqlRelationalTableModel *CreateSalesModel(int companyId);
  static QSqlRelationalTableModel *CreatePurchaseModel(int companyId);

private:
  DbManager(const QString &path);
  static DbManager *m_pInstance;

  QSqlDatabase m_db;
};

#endif // DBMANAGER_H
