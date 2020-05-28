#ifndef DRONEFORMWINDOW_H
#define DRONEFORMWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include "../include/SerializableCollection.h"
#include "../include/Commander.h"
#include "../include/Drone.h"

namespace Ui {
class droneFormWindow;
}

class droneFormWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit droneFormWindow(SerializableCollection<Drone>*, Commander*, QWidget *parent = nullptr);
	~droneFormWindow();

	void verifyField(QList<QLineEdit*> &list, QLineEdit *line, QString lbl);

signals:
	void droneAdded();
private slots:
	void on_btn_Save_clicked();

	void on_btn_Cancel_clicked();

private:
	Ui::droneFormWindow *ui;
	SerializableCollection<Drone> *myDrones;
	Commander *comm;
};

#endif // DRONEFORMWINDOW_H
