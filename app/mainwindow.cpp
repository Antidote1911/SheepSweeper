#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QSettings>
#include <view/CTopWidget.h>
#include <Constants.h>
#include <view/CSettingsDialog.h>
#include <QDebug>
#include "topten.h"
#include "savescore.h"


namespace SSw
{

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),

    m_model(),
    m_timer(),
    m_prefs()
{

    ui->setupUi(this);

    loadSettings();

    initTable();
    initMenubar();
    initTimer();
    initConnections();

    setWindowIcon(QIcon(QPixmap(BIG_SHEEP_PATH)));
    setWindowTitle(APP);
    newGame();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    event->accept();
}

void MainWindow::initTable()
{
    ui->m_view->setModel(&m_model);
    ui->m_view->activate();
}

void MainWindow::initMenubar()
{
    QMenu *fileMenu = new QMenu(tr("&Fichier"), this);

    QAction *newGameAction = fileMenu->addAction(tr("&Nouvelle Partie"));
    newGameAction->setShortcut(QKeySequence::New);

    QAction *bestScoresAction = fileMenu->addAction(tr("&Meilleurs Scores"));
    bestScoresAction->setShortcut(QKeySequence::UnknownKey);

    QAction *preferencesAction = fileMenu->addAction(tr("&Preferences"));
    preferencesAction->setShortcut(QKeySequence::Preferences);
    //TODO: set another shortkut

    QAction *quitAction = fileMenu->addAction(tr("&Quitter"));
    quitAction->setShortcut(QKeySequence::Quit);

    QMenu *helpMenu = new QMenu(tr("&Infos"), this);
    QAction *aboutAction = helpMenu->addAction(tr("&A Propos"));

    menuBar()->addMenu(fileMenu);
    menuBar()->addSeparator();
    menuBar()->addMenu(helpMenu);

    connect(quitAction,         &QAction::triggered, qApp, &QApplication::quit);
    connect(newGameAction,      &QAction::triggered, this, &MainWindow::newGame);
    connect(preferencesAction,  &QAction::triggered, this, &MainWindow::showPreferences);
    connect(bestScoresAction,  &QAction::triggered, this, &MainWindow::showBestScores);
    connect(aboutAction,        &QAction::triggered, this, &MainWindow::showAboutBox);
}

void MainWindow::initTimer()
{
    m_timer.setInterval(1000);
}

void MainWindow::initConnections()
{
    // CTopWidget connections
    connect(ui->m_view, &CTableView::pressed,       ui->topWidget, &CTopWidget::onPressed);
    connect(ui->m_view, &CTableView::clicked,       ui->topWidget, &CTopWidget::onReleased);
    connect(ui->m_view, &CTableView::bothClicked,   ui->topWidget, &CTopWidget::onReleased);
    connect(&m_timer,   &QTimer::timeout,           ui->topWidget, &CTopWidget::incrementTimer);
    connect(&m_model,   &CTableModel::sheepDisplay, ui->topWidget, &CTopWidget::setSheepDisplay);
    connect(&m_model,   &CTableModel::gameLost,     ui->topWidget, &CTopWidget::onLost);
    connect(&m_model,   &CTableModel::gameWon,      ui->topWidget, &CTopWidget::onWon);

    // CTableModel connections
    connect(ui->m_view, &CTableView::clicked,       &m_model, &CTableModel::onTableClicked);
    connect(ui->m_view, &CTableView::rightClicked,  &m_model, &CTableModel::onRightClicked);
    connect(ui->m_view, &CTableView::bothClicked,   &m_model, &CTableModel::onBothClicked);

    // MainWindow connections
    connect(&m_model,        &CTableModel::gameLost,         this, &MainWindow::onGameLost);
    connect(&m_model,        &CTableModel::gameWon,          this, &MainWindow::onGameWon);
    connect(ui->topWidget,   &CTopWidget::buttonClicked,     this, &MainWindow::newGame);
    connect(&m_model,        SIGNAL(gameStarted()),          &m_timer, SLOT(start()));
}

QString MainWindow::convertIntLevelToQString()
{
    if (m_prefs.perso)
    {
        return("Niveau Personnalisé.");
    }
    else {
        if (m_prefs.level==0){
            return("Ultra Débutant");
        }
        if (m_prefs.level==1){
            return("Débutant");
        }
        if (m_prefs.level==2){
            return("Normal");
        }
        if (m_prefs.level==3){
            return("Difficile");
        }
        if (m_prefs.level==4){
            return("Ultra Difficile");
        }
        if (m_prefs.level==5){
            return("Chuck Norris");
        }
    }
}

void MainWindow::newGame()
{
    m_timer.stop();
    ui->label->setText("Level: "+convertIntLevelToQString());
    m_model.resetModel(m_prefs.height, m_prefs.width, m_prefs.sheep);
    ui->m_view->setModel(&m_model);
    ui->m_view->activate();
    ui->topWidget->resetTimer();
    ui->topWidget->setDefault();

    statusBar()->showMessage(tr("Good luck!"), MSG_TIMEOUT);
    updateView();
}

void MainWindow::onGameLost()
{
    m_timer.stop();
    ui->m_view->deactivate();
    statusBar()->showMessage(tr("Malheureusement, tu as perdu."), MSG_TIMEOUT);

}

void MainWindow::onGameWon()
{

    m_timer.stop();
    ui->m_view->deactivate();
    statusBar()->showMessage(tr("Tu as gagné !"), MSG_TIMEOUT);

    // Si il n'a pas gagné en mode personnalisé on demande à l'utilisateur de rentrer son nom.
    if (m_prefs.perso!=true)
    {
        int time = ui->topWidget->m_time;
        SaveScore* scoreScreen = new SaveScore(time,m_prefs.level);
        scoreScreen->show();
    }
}



void MainWindow::showPreferences()
{
    bool accepted = CSettingsDialog::getPreferences(m_prefs, this);

    if (accepted)
    {
        saveSettings();
        newGame();
    }
}

void MainWindow::showAboutBox()
{
    QMessageBox::about(this, APP, tr("Try to avoid the furious sheep.<br>\
                    <div>Icon made by <a href='http://www.freepik.com' title='Freepik'>Freepik</a>\
                    from <a href='http://www.flaticon.com' title='Flaticon'>www.flaticon.com</a>\
                    is licensed under <a href='http://creativecommons.org/licenses/by/3.0/' \
                    title='Creative Commons BY 3.0'>CC BY 3.0</a></div>"));
}

void MainWindow::updateView()
{
    ui->m_view->adjustSizeToContents();
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void MainWindow::loadSettings()
{
    QSettings settings;
    m_prefs.width   = settings.value("width", DEFAULT_WIDTH).toInt();
    m_prefs.height  = settings.value("height", DEFAULT_HEIGHT).toInt();
    m_prefs.sheep   = settings.value("sheep", DEFAULT_SHEEP).toInt();
    m_prefs.level   = settings.value("level", DEFAULT_LEVEL).toInt();
    m_prefs.perso   = settings.value("perso", DEFAULT_CHECK_BOX_PERSO).toBool();
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("width", m_prefs.width);
    settings.setValue("height", m_prefs.height);
    settings.setValue("sheep", m_prefs.sheep);
    settings.setValue("level", m_prefs.level);
    settings.setValue("perso", m_prefs.perso);
}

void MainWindow::showBestScores()
{
    TopTen* scores = new TopTen();
    scores->show();
}

} // namespace SSw

