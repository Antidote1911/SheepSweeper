#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <model/CTableModel.h>
#include <view/CTableView.h>
#include <SPreferences.h>

namespace Ui {
class MainWindow;
}

namespace SSw
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);

public slots:
    void newGame();
    void onGameLost();
    void onGameWon();
    void showAboutBox();
    void showPreferences();
    void showBestScores();
    void updateView();

private:
    void initTable();
    void initMenubar();
    void initConnections();
    void initTimer();
    void loadSettings();
    void saveSettings();
    QString convertIntLevelToQString();

    Ui::MainWindow*     ui;
    CTableModel         m_model;
    QTimer              m_timer;
    SPreferences        m_prefs;
    //WinDialog *mMyNewWindow;
};

} // namespace SSw

#endif // MAINWINDOW_H
