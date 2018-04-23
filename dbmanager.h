#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlTableModel>

class DbManager
{
public:
    DbManager(const QString& path);
    QSqlTableModel* GetModel(QObject* parent, const QString& tableName);

private:
    QSqlDatabase m_db;

};

#endif // DBMANAGER_H
