#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    heroBrowser(db, this),
    createHero(db, this)
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
    }

    openMainMenu();
    createHero.init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openMainMenu()
{
    hideAll();
    ui->mainMenu->show();
}

void MainWindow::openHeroBrowser()
{
    hideAll();
    heroBrowser.refresh();
    heroBrowser.show();
}

void MainWindow::openCreateHero()
{
    hideAll();
    createHero.show();
}

void MainWindow::hideAll()
{
    ui->mainMenu->hide();
    heroBrowser.hide();
    createHero.hide();
}

void MainWindow::on_browseButton_clicked()
{
    openHeroBrowser();
}

void MainWindow::on_exitButton_clicked()
{
    close();
}

void MainWindow::on_newButton_clicked()
{
    openCreateHero();
    createHero.hero.update = false;
    createHero.changeTab(0);
}
