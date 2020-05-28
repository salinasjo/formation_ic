#ifndef DRONEWINDOW_H
#define DRONEWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QWidget>
#include <QDebug>

#include <QMap>

#include "../include/SerializableCollection.h"
#include "../include/Drone.h"
#include "../include/Commander.h"
#include "../include/Point.h"
#include <QCloseEvent>

namespace Ui {
class DroneWindow;
}

class DroneWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit DroneWindow(SerializableCollection<Drone>*, User*,QWidget *parent = nullptr);
	~DroneWindow();

	void clearFields();

private slots:
	void on_tbl_Drones_itemDoubleClicked(QTableWidgetItem *item);

	void on_btn_addDrone_clicked();
	void on_btn_deleteDrone_clicked();

	void on_droneAdded();

	void on_btn_Clear_clicked();


    void closeEvent( QCloseEvent* event ) override;

private:
	Ui::DroneWindow *ui;
	SerializableCollection<Drone> *myDrones;
	User *_user;
};

#endif // DRONEWINDOW_H
