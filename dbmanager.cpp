#include "dbmanager.h"

#include <QDebug>
#include <QSqlQuery>
#include <QTableView>

DbManager::DbManager(const QString& path)
{
   m_db = QSqlDatabase::addDatabase("QSQLITE");
   m_db.setDatabaseName("bazodanowa.db");

   if (!m_db.open())
   {
      qDebug() << "Error: connection with database fail";
   }
   else
   {
      qDebug() << "Database: connection ok " << m_db.isValid();
   }
   if(m_db.isOpen())
   {
       auto list = m_db.tables();
       for(auto l : list)
       {
           qDebug() << l;
       }
   }

}

QSqlTableModel* DbManager::GetModel(QObject* parent, const QString& tableName)
{
    auto model = new QSqlTableModel(parent, m_db);
    model->setTable(tableName);
    return model;
}
