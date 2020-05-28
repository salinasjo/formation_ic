#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include "include/User.h"
#include "include/SerializableCollection.h"
#include "include/Drone.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

	void setUser(User *u);

private slots:

	void on_btnDroneWindow_clicked();

	void on_btn_TrajectoryWindow_clicked();

    void on_btnMissionWindow_clicked();



    void on_pushButton_clicked();

    void on_pushButton_traj_clicked();

private:
    Ui::MainWindow *ui;
	User *_user;

	SerializableCollection<Drone> *myDrones;

};

#endif // MAINWINDOW_H
