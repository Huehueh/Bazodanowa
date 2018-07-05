#ifndef DICTIONARYDIALOG_H
#define DICTIONARYDIALOG_H

#include <QDialog>
#include <QXmlStreamReader>
#include <QMap>

class DictionaryDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DictionaryDialog(QWidget *parent = nullptr);


signals:

public slots:

private:
    void LoadDictionary();
    void FillLayout();
    void ParseEntry(QXmlStreamReader& reader);
    QMap<QString, QString> map;

};

#endif // DICTIONARYDIALOG_H
