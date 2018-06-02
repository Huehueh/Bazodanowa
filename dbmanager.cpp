#include "dbmanager.h"

#include <QDebug>
#include <QSqlQuery>
#include <QTableView>

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
  model->setTable(Names::mojeFirmy);
  model->select();

  //  model->setHeaderData(MojaFirma::Skrot, Qt::Horizontal,
  //                       "Skrócona nazwa firmy");
  //  model->setHeaderData(MojaFirma::eData::Nazwa, Qt::Horizontal, "Nazwa
  //  firmy"); model->setHeaderData(MojaFirma::NIP, Qt::Horizontal, "NIP");
  //  model->setHeaderData(MojaFirma::Adres, Qt::Horizontal, "Adres");
  //  model->setHeaderData(MojaFirma::Email, Qt::Horizontal, "Email");

  return model;
}

QSqlRelationalTableModel *DbManager::CreateSalesModel(int companyId) {
  auto db = QSqlDatabase::database();
  auto *model = new QSqlRelationalTableModel(nullptr, db);
  model->setTable(Names::sprzedaz);
  model->setFilter("FirmaId=" + QString::number(companyId));

  model->setRelation(Sprzedaz::KontrahentId,
                     QSqlRelation(Names::konrahenci, "KontrahentId", "Nazwa"));
  model->select();

  //  model->setHeaderData(Sprzedaz::Id, Qt::Horizontal, "Id");
  //  // model->setHeaderData(Sprzedaz::KontrahentId, Qt::Horizontal,
  //  "Kontrahent");

  //  model->setHeaderData(Sprzedaz::DowodSprzedazy, Qt::Horizontal,
  //                       "Dowód sprzedaży");
  //  model->setHeaderData(Sprzedaz::DataSprzedazy, Qt::Horizontal,
  //                       "Data sprzedaży");
  //  model->setHeaderData(Sprzedaz::DataWystawienia, Qt::Horizontal,
  //                       "Data wystawienia");

  return model;
}
