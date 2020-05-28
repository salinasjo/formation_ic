#ifndef TRAJECTORYWINDOW_H
#define TRAJECTORYWINDOW_H

#include <QMainWindow>
#include <include/DiscreteMap.h>
#include <QLineEdit>
#include <QLabel>
#include "drawer.h"

namespace Ui {
class TrajectoryWindow;
}

class TrajectoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrajectoryWindow(DiscreteMap & dm,QWidget *parent = nullptr);
    ~TrajectoryWindow();

public slots:
    void OnSelectPoint(double x, double y, double z, double fuel, double time, double angle);
    void SendSignalZChanged();
signals:
    void signalZChanged(double z);

private slots:
    void closeEvent(QCloseEvent *event);
private:
    void CreateLabel(QString text, QPoint pos, int width);


    Ui::TrajectoryWindow *ui;
    drawer * _drawer;
    QLabel * _posX;
    QLabel * _posY;
    QLineEdit * _posZ;
    QLabel * _fuelUse;
    QLabel * _time;
    QLabel * _angle;
};

#endif // TRAJECTORYWINDOW_H
