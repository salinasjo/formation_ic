#ifndef MISSIONWINDOW_H
#define MISSIONWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QWidget>
#include "include/SerializableCollection.h"
#include <include/MissionProcess.h>
#include "../include/Drone.h"

namespace Ui {
class missionWindow;
}

class missionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit missionWindow(QWidget *parent = nullptr);
    ~missionWindow();

    void addDroneToTableWidget(QTableWidget*, int, QMap<int, Drone*>::iterator , MissionProcess*);
    bool droneCheck(QTableWidget*);
    void resetField(QLineEdit*);

private slots:
    void on_pushButton_clicked();
    void closeEvent(QCloseEvent *event);
    void on_altitudeTxt_editingFinished();

    void on_chargeTxt_editingFinished();

    void on_departX_editingFinished();


private:
    Ui::missionWindow *ui;
    SerializableCollection<MissionProcess> *missionList;
    SerializableCollection<Drone> * myDrones;
    MissionProcess *mp;
};

#endif // MISSIONWINDOW_H
