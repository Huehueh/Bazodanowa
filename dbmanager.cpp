#include "dbmanager.h"

#include <QDebug>
#include <QSqlQuery>
#include <QTableView>

#include "columnnames.h"
#include "enums.h"
#include "names.h"

DbManager *DbManager::m_pInstance = nullptr;

DbManager *DbManager::CreateInstance(const QString &path) {
  if (m_pInstance == nullptr) {
    m_pInstance = new DbManager(path);
  }
  return m_pInstance;
}

DbManager *DbManager::Instance() { return m_pInstance; }

DbManager::DbManager(const QString &path) {
  m_db = QSqlDatabase::addDatabase("QSQLITE");
  m_db.setDatabaseName(path);

  if (!m_db.open()) {
    qDebug() << "Error: connection with database fail";
  } else {
    qDebug() << "Database: connection ok " << m_db.isValid();
  }
  if (m_db.isOpen()) {
    auto list = m_db.tables();
    for (auto l : list) {
      qDebug() << l;
    }
  }
}

QSqlTableModel *DbManager::CreateMyCompaniesModel() {
  QSqlDatabase db = QSqlDatabase::database();
  QSqlTableModel *model = new QSqlTableModel(nullptr, db);
  model->setTable(TableNames::mojeFirmy);
  model->select();

  for (const auto &it : ColumnNames::my_companies) {
    model->setHeaderData(it.first, Qt::Horizontal, it.second);
  }
  return model;
}

QSqlTableModel *DbManager::CreateContractorsModel() {
  QSqlDatabase db = QSqlDatabase::database();
  QSqlTableModel *model = new QSqlTableModel(nullptr, db);
  model->setTable(TableNames::konrahenci);
  model->select();

  for (const auto &it : ColumnNames::contractors) {
    model->setHeaderData(it.first, Qt::Horizontal, it.second);
  }
  return model;
}

QSqlRelationalTableModel *DbManager::CreateSalesModel(int companyId) {
  auto db = QSqlDatabase::database();
  auto *model = new QSqlRelationalTableModel(nullptr, db);
  model->setTable(TableNames::sprzedaz);
  model->setFilter("FirmaId='" + QString::number(companyId) + "'");

  model->setRelation(Sprzedaz::KontrahentId,
                     QSqlRelation(TableNames::konrahenci, "Id", "Nazwa"));
  model->select();

  for (const auto &it : ColumnNames::sale) {
    model->setHeaderData(it.first, Qt::Horizontal, it.second);
  }

  return model;
}

QSqlRelationalTableModel *DbManager::CreatePurchaseModel(int companyId) {
  auto db = QSqlDatabase::database();
  auto *model = new QSqlRelationalTableModel(nullptr, db);
  model->setTable(TableNames::zakup);
  model->setFilter("FirmaId='" + QString::number(companyId) + "'");

  model->setRelation(Sprzedaz::KontrahentId,
                     QSqlRelation(TableNames::konrahenci, "Id", "Nazwa"));
  model->select();

  for (const auto &it : ColumnNames::purchase) {
    model->setHeaderData(it.first, Qt::Horizontal, it.second);
  }

  return model;
}
