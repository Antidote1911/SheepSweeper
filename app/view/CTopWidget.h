#ifndef TOPWIDGET_H
#define TOPWIDGET_H

#include <QWidget>
#include <QIcon>

namespace Ui {
class CTopWidget;
}

namespace SSw
{

class CTopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CTopWidget(QWidget *parent = 0);
    ~CTopWidget();
    int32_t        m_time;


signals:
    void buttonClicked();

public slots:
    void setSheepDisplay(int32_t sheepRemained);
    void incrementTimer();
    void resetTimer();
    void onPressed();
    void onReleased();
    void onWon();
    void onLost();
    void setDefault();

private:
    Ui::CTopWidget *ui;
    void init();
    QIcon          m_normalFace;
    QIcon          m_fearFace;
    QIcon          m_happyFace;
    QIcon          m_sadFace;

};

} // namespace SSw

#endif // TOPWIDGET_H
