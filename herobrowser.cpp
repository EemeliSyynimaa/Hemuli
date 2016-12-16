#include "herobrowser.h"
#include "ui_herobrowser.h"
#include <QSqlQuery>
#include "mainwindow.h"

HeroBrowser::HeroBrowser(QSqlDatabase& db, MainWindow* window) :
    QWidget(window),
    db(db),
    window(window),
    ui(new Ui::HeroBrowser)
{
    ui->setupUi(this);
}

HeroBrowser::~HeroBrowser()
{
    delete ui;
}

void HeroBrowser::refresh()
{
    ui->listWidget->clear();

    QSqlQuery query;

    query.prepare("SELECT * FROM heroes");

    if (query.exec())
    {
        while (query.next())
        {
            QListWidgetItem* item = new QListWidgetItem(query.value(1).toString());
            item->setData(1, query.value(0).toInt());
            ui->listWidget->insertItem(ui->listWidget->count(), item);
        }
    }
}

void HeroBrowser::on_editButton_clicked()
{
    if (!ui->listWidget->currentItem())
        return;

    window->createHero.hero.id = ui->listWidget->currentItem()->data(1).toInt();
    window->createHero.hero.update = true;

    window->openCreateHero();
    window->createHero.updateSummary();
}

void HeroBrowser::on_deleteButton_clicked()
{
    QSqlQuery query;

    query.prepare("DELETE FROM Heroes WHERE ID = ?");
    query.addBindValue(ui->listWidget->currentItem()->data(1));
    query.exec();

    refresh();
}

void HeroBrowser::on_backButton_clicked()
{
    window->openMainMenu();
}
