#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}

void MainWindow::setTableModel(QSqlTableModel* model)
{
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(1, Qt::Horizontal, tr("Nazwa firmy"));
    model->setHeaderData(2, Qt::Horizontal, tr("NIP"));
    model->setHeaderData(3, Qt::Horizontal, tr("Adres"));
    model->setHeaderData(4, Qt::Horizontal, tr("Email"));

    auto view = ui->companiesTableView;
    view->setModel(model);
    view->hideColumn(0); //id
}

MainWindow::~MainWindow()
{
    delete ui;
}
