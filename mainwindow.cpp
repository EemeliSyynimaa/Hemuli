#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");

    if (!db.open())
    {
        qDebug() << "ERROR";
    }
    else
    {
        qDebug() << "OK";

        QSqlQuery query;

        query.prepare("SELECT * FROM races");

        if (query.exec())
        {
            while (query.next())
            {
                ui->listWidget->insertItem(ui->listWidget->count(), new QListWidgetItem(query.value(2).toString()));
            }
        }
    }

    ui->herolist->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->herolist->show();
    ui->menu->hide();
}
