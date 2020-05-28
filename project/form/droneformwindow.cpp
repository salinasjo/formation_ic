#include "droneformwindow.h"
#include "ui_droneformwindow.h"

droneFormWindow::droneFormWindow(SerializableCollection<Drone>* list, Commander* user, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::droneFormWindow)
{
	ui->setupUi(this);
	myDrones = list;
	comm = user;
}

droneFormWindow::~droneFormWindow()
{
	delete ui;
}

void droneFormWindow::on_btn_Save_clicked()
{
	ui->txt_errors->clear();
	QList<QLineEdit *> txtErrors;
	QString name = ui->cBox_wingType->currentText();
	float maxAngle = ui->txt_maxAngle->text().toFloat();
	verifyField(txtErrors, ui->txt_maxAngle, "Max Angle");
	WingType wT(name, maxAngle);

	float payload = ui->txt_Payload->text().toFloat();
	verifyField(txtErrors, ui->txt_Payload, "Payload");
	double maxAlt = ui->txt_maxAltitude->text().toDouble();
	verifyField(txtErrors, ui->txt_maxAltitude, "Max Altitude");
	double maxRange = ui->txt_maxRange->text().toDouble();
	verifyField(txtErrors, ui->txt_maxRange, "Max Range");
	float cruiseSpeed = ui->txt_cruiseSpeed->text().toFloat();
	verifyField(txtErrors, ui->txt_cruiseSpeed, "Cruise Speed");
	float autonomy = ui->txt_Autonomy->text().toFloat();
	verifyField(txtErrors, ui->txt_Autonomy, "Autonomy");
	DroneType dT(payload,maxAlt,maxRange,cruiseSpeed,autonomy,wT);

	double latitude = ui->txt_latitude->text().toDouble();
	double longitude = ui->txt_longitude->text().toDouble();
	Point p(latitude, longitude, 0.0);

	if(txtErrors.isEmpty()) {
		Drone *d = new Drone(p, dT);
		bool executed = comm->addDrone(myDrones->getMap(), d);
		if(executed) {
			FileDump::WriteLine("Added Drone : " + d->toString());
			myDrones->save();
			emit droneAdded();
			this->close();
//			int row = ui->tbl_Drones->rowCount();
//			QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(d->getid()));
//			ui->tbl_Drones->insertRow(row);
//			ui->tbl_Drones->setItem(row, 0, newItem);
		}
	}

}

void droneFormWindow::verifyField(QList<QLineEdit*> &list, QLineEdit *line, QString lbl)  {
	line->setStyleSheet({"border : 0px solid black;"});
	if(line->text().toDouble()<0) {
		list.push_back(line);
		FileDump::WriteLine("Negative Value in Field : " + lbl.toStdString());

		line->setStyleSheet({"border : 2px solid red;"});
		ui->txt_errors->append("Negative Values in field : " + lbl);
	}
}

void droneFormWindow::on_btn_Cancel_clicked()
{
	this->close();
}
