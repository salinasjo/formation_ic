#include "dronewindow.h"
#include "ui_dronewindow.h"
#include "droneformwindow.h"

#include <QMessageBox>

DroneWindow::DroneWindow(SerializableCollection<Drone> *list, User *u, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::DroneWindow)
{
	ui->setupUi(this);
	_user = u;
	myDrones = list;
	int row = 0;
	for(int ID : myDrones->getMap()->keys()) {
		Drone *d = myDrones->getMap()->value(ID);
		if(!d->getDeleted()) {
			QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(ID));
			ui->tbl_Drones->insertRow(row);
			ui->tbl_Drones->setItem(row, 0, newItem);
			row++;
		}
	}

}

DroneWindow::~DroneWindow()
{

    FileDump::WriteLine("DroneWindow destruction !");
    delete ui;

}


void DroneWindow::clearFields() {

//	for(int i=0;i<layout()->count();i++) {
//		QLayoutItem *layoutItem = layout()->itemAt(i);
//		QWidget * widget = layoutItem->widget();
//		QLineEdit * txtEdit = dynamic_cast<QLineEdit *>(widget);
//		if(txtEdit!=nullptr)
//			txtEdit->text().clear();
//	}

}

void DroneWindow::on_tbl_Drones_itemDoubleClicked(QTableWidgetItem *item)
{
	Drone *d = myDrones->getMap()->value(item->text().toInt());
	ui->txt_ID->setText(QString::number(d->getid()));

	ui->cBox_wingType->setCurrentText(d->getDroneType().getWingType().getName());
	ui->txt_maxAngle->setText(QString::number(d->getDroneType().getWingType().getMaxAngle()));

	ui->txt_Payload->setText(QString::number(d->getDroneType().getWeightCapacity()));
	ui->txt_maxAltitude->setText(QString::number(d->getDroneType().getMaxAltitude()));
	ui->txt_maxRange->setText(QString::number(d->getDroneType().getMaxRange()));
	ui->txt_cruiseSpeed->setText(QString::number(d->getDroneType().getCruiseSpeed()));
	ui->txt_Autonomy->setText(QString::number(d->getDroneType().getAutonomy()));

    ui->txt_latitude->setText(QString::number(d->getGroundPosition().GetLatitude()));
    ui->txt_longitude->setText(QString::number(d->getGroundPosition().GetLongitude()));

}

void DroneWindow::on_btn_addDrone_clicked()
{
	Commander *comm = dynamic_cast<Commander*>(_user);
	if(comm != nullptr) {
		droneFormWindow *dfW = new droneFormWindow(myDrones,comm);
		dfW->show();
		connect(dfW, SIGNAL(droneAdded()), this, SLOT(on_droneAdded()));
	}
	else {
		qDebug() << "Non Commander User cannot add Drone!" << endl;
		FileDump::WriteLine("Error addDrone unavailable for User : " + _user->getLogin().toStdString());

		QMessageBox msgBox(QMessageBox::Warning,
						   "User Error!",
						   "Non Commander User cannot add Drone!",
						   QMessageBox::Ok);
		msgBox.exec();
	}
}

void DroneWindow::on_btn_deleteDrone_clicked()
{
	Commander *comm = dynamic_cast<Commander*>(_user);
	if(comm != nullptr) {
		QTableWidgetItem *item = ui->tbl_Drones->currentItem();
		if(item != nullptr) {
			int row = ui->tbl_Drones->currentRow();
			Drone *d = myDrones->getMap()->value(item->text().toInt());
			bool executed = comm->deleteDrone(myDrones->getMap(),d);
			if(executed) {
				FileDump::WriteLine("Deleted Drone : " + d->toString());
				ui->tbl_Drones->removeRow(row);
			}
			d = nullptr;
		}
		clearFields();
		comm = nullptr;
	}
	else {
		qDebug() << "Non Commander User cannot delete Drone!" << endl;
		FileDump::WriteLine("Error deleteDrone unavailable for User : " + _user->getLogin().toStdString());

		QMessageBox msgBox(QMessageBox::Warning,
						   "User Error!",
						   "Non Commander User cannot delete Drone!",
						   QMessageBox::Ok);
		msgBox.exec();
	}
}

void DroneWindow::on_droneAdded()
{
	int row = ui->tbl_Drones->rowCount();
	Drone *d = myDrones->getMap()->last();
	QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(d->getid()));
	ui->tbl_Drones->insertRow(row);
	ui->tbl_Drones->setItem(row, 0, newItem);
}

void DroneWindow::on_btn_Clear_clicked()
{
	clearFields();
}

void DroneWindow::closeEvent( QCloseEvent* event )
{
	bool saved = myDrones->save();
    if(!saved) {
        FileDump::WriteLine("Error while saving Drones to file!");
    }
}

//void DroneWindow::verifyField(QList<QLineEdit*> &list, QLineEdit *line, QString lbl)  {
//	line->setStyleSheet({"border : 0px solid black;"});
//	if(line->text().toDouble()<0) {
//		list.push_back(line);
//		FileDump::WriteLine("Negative Value in Field : " + lbl.toStdString());

//		line->setStyleSheet({"border : 2px solid red;"});
//		ui->txt_errors->append("Negative Values in field : " + lbl);
//	}
//}
