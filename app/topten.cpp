/**
 * TopTen
 * Displays information about the top ten players
 * @author Stephen Liang
 * @author Aisha Halim
 * Created for CS 340 Fall 2010 - Professor Troy
 */
#include "topten.h"
#include "ui_topten.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

/**
  * Constructor
  * Sets up database connection and connects the reset button to clear all the information
  */
TopTen::TopTen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TopTen)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);

    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetScores()));

    //Database info
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE", "connection");

    db.setDatabaseName("scores.sqlite");

    if ( !db.open() )
    {
        qFatal("Failed to connect to database");
    }

    getTopTenScores();
}

/**
  * resetScores()
  * Erases the score table
  */
void TopTen::resetScores()
{
    QSqlDatabase db = QSqlDatabase::database("connection");

    QSqlQuery sql(db);

    //Clear the table
    sql.prepare("DELETE FROM scores");

    if ( !sql.exec() )
    {
        qFatal("Unable to truncate table from database");
    }

    getTopTenScores(); //Refresh view
}

/**
  * getTopTenScores()
  * Gets the top ten scores from the database and ensures that the scores table already exists
  */
void TopTen::getTopTenScores()
{
    QString topScores0 = "<ol>";
    QString topScores1 = "<ol>";
    QString topScores2 = "<ol>";
    QString topScores3 = "<ol>";
    QString topScores4 = "<ol>";
    QString topScores5 = "<ol>";

    QSqlDatabase db = QSqlDatabase::database("connection");

    QSqlQuery sql(db);

    //Ensure that the table exists!
    sql.prepare("CREATE  TABLE  IF NOT EXISTS \"scores\" (\"id\" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , \"score\" INTEGER, \"name\" TEXT, \"level\" INTEGER)");

    if ( !sql.exec())
    {
        QString error = sql.lastError().text();
    }

    //Grab the top ten players
    sql.prepare("SELECT name, score, level FROM scores WHERE level = '0' ORDER BY score ASC LIMIT 10");

    if ( !sql.exec() )
    {
        qFatal("Unable to select from database");
    }

    QSqlRecord record = sql.record();

    //Create a list of those top ten players
    for( int r=0; sql.next(); r++ )
              topScores0 += "<li>" + sql.value(0).toString() + " - " + sql.value(1).toString() +"  secondes  "+"</li>";

    topScores0 += "</ol>";

    //Set the list for the user to see
    ui->topTenList->setText(topScores0);

    // Remplissage table level 1
    sql.prepare("SELECT name, score, level FROM scores WHERE level = '1' ORDER BY score ASC LIMIT 10");
    if ( !sql.exec() )
    {
        qFatal("Unable to select from database");
    }

    for( int r=0; sql.next(); r++ )
              topScores1 += "<li>" + sql.value(0).toString() + " - " + sql.value(1).toString() +"  secondes  "+"</li>";
    topScores1 += "</ol>";
    ui->topTenList_1->setText(topScores1);

    // Remplissage table level 2
    sql.prepare("SELECT name, score, level FROM scores WHERE level = '2' ORDER BY score ASC LIMIT 10");
    if ( !sql.exec() )
    {
        qFatal("Unable to select from database");
    }

    for( int r=0; sql.next(); r++ )
              topScores2 += "<li>" + sql.value(0).toString() + " - " + sql.value(1).toString() +"  secondes  "+"</li>";

    topScores2 += "</ol>";

    //Set the list for the user to see
    ui->topTenList_2->setText(topScores2);

    // Remplissage table level 3
    sql.prepare("SELECT name, score, level FROM scores WHERE level = '3' ORDER BY score ASC LIMIT 10");
    if ( !sql.exec() )
    {
        qFatal("Unable to select from database");
    }

    for( int r=0; sql.next(); r++ )
              topScores3 += "<li>" + sql.value(0).toString() + " - " + sql.value(1).toString() +"  secondes  "+"</li>";

    topScores3 += "</ol>";

    //Set the list for the user to see
    ui->topTenList_3->setText(topScores3);

    // Remplissage table level 4
    sql.prepare("SELECT name, score, level FROM scores WHERE level = '4' ORDER BY score ASC LIMIT 10");
    if ( !sql.exec() )
    {
        qFatal("Unable to select from database");
    }

    for( int r=0; sql.next(); r++ )
              topScores4 += "<li>" + sql.value(0).toString() + " - " + sql.value(1).toString() +"  secondes  "+"</li>";

    topScores4 += "</ol>";

    //Set the list for the user to see
    ui->topTenList_4->setText(topScores4);

    // Remplissage table level 5
    sql.prepare("SELECT name, score, level FROM scores WHERE level = '5' ORDER BY score ASC LIMIT 10");
    if ( !sql.exec() )
    {
        qFatal("Unable to select from database");
    }

    for( int r=0; sql.next(); r++ )
              topScores5 += "<li>" + sql.value(0).toString() + " - " + sql.value(1).toString() +"  secondes  "+"</li>";

    topScores5 += "</ol>";

    //Set the list for the user to see
    ui->topTenList_5->setText(topScores5);

}

/**
  * Destructor
  */
TopTen::~TopTen()
{
    QSqlDatabase::database("connection").close();
    QSqlDatabase::removeDatabase("connection");
    delete ui;
}

void TopTen::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
