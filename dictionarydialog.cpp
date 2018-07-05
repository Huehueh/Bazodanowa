#include "dictionarydialog.h"

#include <QXmlStreamReader>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QGridLayout>

DictionaryDialog::DictionaryDialog(QWidget *parent) : QDialog(parent)
{
    LoadDictionary();
    FillLayout();
}

void DictionaryDialog::FillLayout()
{
    auto layout = new QGridLayout(this);
    int i=0;
    auto f = font();
    f.setBold(true);
    for(const auto&key : map.keys())
    {
        auto label = new QLabel(key);
        label->setFont(f);
        layout->addWidget(label, i, 0);
        ++i;
    }
    int j=0;
    for(const auto&val : map.values())
    {
        layout->addWidget(new QLabel(val), j, 1);
        ++j;
    }
    layout->setSpacing(10);
    layout->setMargin(10);
    setLayout(layout);
}

void DictionaryDialog::ParseEntry(QXmlStreamReader& reader)
{
   QString key, value;
   if(reader.name().toString() == "K" && reader.attributes().hasAttribute("name"))
   {
       key = reader.attributes().value("name").toString();
       while(reader.readNextStartElement())
       {
            if(reader.name() == "Description")
            {
                value = reader.readElementText();
                map[key] = value;
            }
            else
            {
                reader.skipCurrentElement();
            }
       }
   }
   else
   {
       reader.skipCurrentElement();
   }
}

void DictionaryDialog::LoadDictionary()
{
    auto xmlFile = new QFile("k.xml");
            if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
                    QMessageBox::critical(this,"Load XML File Problem",
                    "Couldn't open k.xml to load settings for download",
                    QMessageBox::Ok);
                    return;
            }
    QXmlStreamReader reader(xmlFile);
    while(reader.readNextStartElement() && reader.name().toString() == "NeededValues")
    {
        while(reader.readNextStartElement())
        {
            ParseEntry(reader);
        }
    }
    xmlFile->close();
}
