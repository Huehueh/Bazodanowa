#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QString>

class DbManager {
public:
  DbManager(const QString &path);

private:
  QSqlDatabase m_db;
};

#endif // DBMANAGER_H
