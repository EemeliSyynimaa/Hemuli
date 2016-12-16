#include "createhero.h"
#include "ui_createhero.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "mainwindow.h"

CreateHero::CreateHero(QSqlDatabase& db, MainWindow* window) :
    QWidget(window),
    db(db),
    window(window),
    ui(new Ui::CreateHero),
    perk_index(1)
{
    ui->setupUi(this);
}

CreateHero::~CreateHero()
{
    delete ui;
}

void CreateHero::init()
{
    ui->raceWidget->clear();
    ui->classWidget->clear();
    ui->perksWidget->clear();

    QSqlQuery query;

    query.prepare("SELECT * FROM races");

    if (query.exec())
    {
        while (query.next())
        {
            ui->raceWidget->insertItem(ui->raceWidget->count(), new QListWidgetItem(query.value(1).toString()));
        }
    }

    query.prepare("SELECT * FROM classes");

    if (query.exec())
    {
        while (query.next())
        {
            ui->classWidget->insertItem(ui->classWidget->count(), new QListWidgetItem(query.value(1).toString()));
        }
    }

    query.prepare("SELECT * FROM perks");

    if (query.exec())
    {
        while (query.next())
        {
            ui->perksWidget->insertItem(ui->perksWidget->count(), new QListWidgetItem(query.value(1).toString()));
        }
    }
}

void CreateHero::on_raceWidget_itemDoubleClicked(QListWidgetItem*)
{
    hero.race_id = ui->raceWidget->currentIndex().row() + 1;
    ui->raceLabel->setText("Race: " + ui->raceWidget->currentItem()->text());
}

void CreateHero::on_classWidget_itemDoubleClicked(QListWidgetItem*)
{
    hero.class_id = ui->classWidget->currentIndex().row() + 1;
    ui->classLabel->setText("Class: " + ui->classWidget->currentItem()->text());

    QSqlQuery query;
    query.prepare("SELECT \"Skill ID 1\", \"Skill ID 2\", \"Skill ID 3\" FROM Classes WHERE ID = ?");
    query.bindValue(0, hero.class_id);

    query.exec();
    query.next();

    QSqlQuery query2;
    query2.prepare("SELECT Name FROM Skills WHERE ID IN (?, ?, ?)");
    query2.bindValue(0, query.value(0).toInt());
    query2.bindValue(1, query.value(1).toInt());
    query2.bindValue(2, query.value(2).toInt());

    query2.exec();

    query2.next();
    ui->skillLabel1->setText("Skill 1: " + query2.value(0).toString());

    query2.next();
    ui->skillLabel2->setText("Skill 2: " + query2.value(0).toString());

    query2.next();
    ui->skillLabel3->setText("Skill 3: " + query2.value(0).toString());
}

void CreateHero::on_perksWidget_itemDoubleClicked(QListWidgetItem*)
{
    if (perk_index == 1)
    {
        hero.perk1_id = ui->perksWidget->currentIndex().row() + 1;
        ui->perkLabel1->setText("Perk 1: " + ui->perksWidget->currentItem()->text());
    }
    else if (perk_index == 2)
    {
        hero.perk2_id = ui->perksWidget->currentIndex().row() + 1;
        ui->perkLabel2->setText("Perk 2: " + ui->perksWidget->currentItem()->text());
    }
    else if (perk_index == 3)
    {
        hero.perk3_id = ui->perksWidget->currentIndex().row() + 1;
        ui->perkLabel3->setText("Perk 3: " + ui->perksWidget->currentItem()->text());
    }

    if(++perk_index > 3)
        perk_index = 1;

}

void CreateHero::on_nameWidget_textChanged(const QString &arg1)
{
    hero.name = arg1;
    ui->nameLabel->setText("Name: " + arg1);
}

void CreateHero::on_strBox_valueChanged(QString arg1)
{
    hero.strength = arg1.toInt();
    ui->strLabel->setText("Strength: " + arg1);
}

void CreateHero::on_agiBox_valueChanged(QString arg1)
{
    hero.agility = arg1.toInt();
    ui->agiLabel->setText("Agility: " + arg1);
}

void CreateHero::on_dexBox_valueChanged(QString arg1)
{
    hero.dexterity = arg1.toInt();
    ui->dexLabel->setText("Dexterity: " + arg1);
}

void CreateHero::on_intBox_valueChanged(QString arg1)
{
    hero.intelligence = arg1.toInt();
    ui->intLabel->setText("Intelligence: " + arg1);
}

void CreateHero::on_SaveButton_clicked()
{
    QSqlQuery query;

    if (!hero.update)
    {
         query.prepare("INSERT INTO Heroes (Name, Age, 'Race ID', 'Class ID', 'Perk ID 1', 'Perk ID 2', 'Perk ID 3', Strength, Agility, Dexterity, Intelligence) "
                       "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    }
    else
    {
        query.prepare("UPDATE Heroes SET Name = ?, Age = ?, 'Race ID' = ?, 'Class ID' = ?, "
                      "'Perk ID 1' = ?, 'Perk ID 2' = ?, 'Perk ID 3' = ?, "
                      "Strength = ?, Agility = ?, Dexterity = ?, Intelligence = ? WHERE ID  = ?");
        query.bindValue(11, hero.id);
    }

    query.bindValue(0, hero.name);
    query.bindValue(1, hero.age);
    query.bindValue(2, hero.race_id);
    query.bindValue(3, hero.class_id);
    query.bindValue(4, hero.perk1_id);
    query.bindValue(5, hero.perk2_id);
    query.bindValue(6, hero.perk3_id);
    query.bindValue(7, hero.strength);
    query.bindValue(8, hero.agility);
    query.bindValue(9, hero.dexterity);
    query.bindValue(10, hero.intelligence);

    query.exec();
}

void CreateHero::on_ageBox_valueChanged(const QString &arg1)
{
    hero.age = arg1.toInt();
    ui->ageLabel->setText("Age: " + arg1 + " years old.");
}

void CreateHero::on_backButton_clicked()
{
    window->openMainMenu();
}

void CreateHero::updateSummary()
{
    QSqlQuery query;
    QSqlQuery query2;

    changeTab(5);

    query.prepare("SELECT * FROM Heroes WHERE ID = ?");
    query.addBindValue(hero.id);
    query.exec();
    query.next();

    hero.name = query.value(1).toString();
    hero.age = query.value(2).toInt();
    hero.race_id = query.value(3).toInt();
    hero.class_id = query.value(4).toInt();
    hero.perk1_id = query.value(5).toInt();
    hero.perk2_id = query.value(6).toInt();
    hero.perk3_id = query.value(7).toInt();
    hero.strength = query.value(8).toInt();
    hero.agility = query.value(9).toInt();
    hero.dexterity = query.value(10).toInt();
    hero.intelligence = query.value(11).toInt();

    ui->nameLabel->setText("Name: " +  hero.name);
    ui->ageLabel->setText("Age: " + query.value(2).toString() + " years old.");
    ui->raceLabel->setText("Race: " + ui->raceWidget->item(hero.race_id - 1)->text());

    ui->strLabel->setText("Strength: " + query.value(8).toString());
    ui->agiLabel->setText("Agility: " + query.value(9).toString());
    ui->dexLabel->setText("Dexterity: " + query.value(10).toString());
    ui->intLabel->setText("Intelligence: " + query.value(11).toString());

    ui->perkLabel1->setText("Perk 1: " + ui->perksWidget->item(hero.perk1_id - 1)->text());
    ui->perkLabel2->setText("Perk 2: " + ui->perksWidget->item(hero.perk2_id - 1)->text());
    ui->perkLabel3->setText("Perk 3: " + ui->perksWidget->item(hero.perk3_id - 1)->text());

    query.prepare("SELECT * FROM Classes WHERE ID = ?");
    query.bindValue(0, hero.class_id);

    query.exec();
    query.next();

    ui->classLabel->setText("Class: " + query.value(1).toString());

    query2.prepare("SELECT Name FROM Skills WHERE ID IN (?, ?, ?)");
    query2.bindValue(0, query.value(3).toInt());
    query2.bindValue(1, query.value(4).toInt());
    query2.bindValue(2, query.value(5).toInt());

    query2.exec();
    query2.next();
    ui->skillLabel1->setText("Skill 1: " + query2.value(0).toString());
    query2.next();
    ui->skillLabel2->setText("Skill 2: " + query2.value(0).toString());
    query2.next();
    ui->skillLabel3->setText("Skill 3: " + query2.value(0).toString());
}

void CreateHero::changeTab(int i)
{
    ui->tabWidget->setCurrentIndex(i);
}
