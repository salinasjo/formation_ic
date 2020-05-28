#include "missionwindow.h"
#include "ui_missionwindow.h"

#include <QJsonDocument>
#include <qfile.h>
#include <QtDebug>

#include <QFormLayout>
#include <QMessageBox>

missionWindow::missionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::missionWindow)
{
    ui->setupUi(this);

    //Creation of a new instance of MissionProcess at the opening of the window
    MissionProcess *mp = new MissionProcess();

    missionList =  new SerializableCollection<MissionProcess>("missions.json","missions"); //new QMap<int, MissionProcess *>();
    bool loaded = missionList->load();//MissionProcess::loadMissions(missionList);
    if(loaded) {
        int row =0;
        for(int ID : missionList->getMap()->keys()) {
            QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(ID));
            ui->missionListWidget->insertRow(row);
            ui->missionListWidget->setItem(row, 0, newItem);
            row++;
        }
        FileDump::WriteLine("Successfully loaded Missions from file!");
    }else{
        FileDump::WriteLine("Error while loading Missions from file!");
    }


    //Loading all existing drones in the table and display some caracteristics
    myDrones = new SerializableCollection<Drone>("drones.json", "drones");
    bool droneLoaded = myDrones->load();
    if(droneLoaded) {
        QMap<int, Drone*>::iterator it;
        int row = 0;
        for (it = myDrones->getMap()->begin(); it != myDrones->getMap()->end(); it++)
        {
            ui->compatibleDronesTable->insertRow(row);
            addDroneToTableWidget(ui->compatibleDronesTable, row, it, mp);
            row++;
        }
        FileDump::WriteLine("Successfully loaded Drones from file!");
    }
    else {
        FileDump::WriteLine("Error while loading Drones from file!");

    }
}


missionWindow::~missionWindow()
{

    delete ui;
    delete missionList;
}

void missionWindow::on_pushButton_clicked()
{

    MissionProcess * newMission = new MissionProcess();

    MissionType * mt = new MissionType();
    mt->setName(ui->nameTxt->text());
    mt->setPayload(ui->chargeTxt->text().toFloat());
    mt->setAltitude(ui->altitudeTxt->text().toDouble());
    newMission->setMissionType(*mt);

    //newMission->setId(ui->idTxt->text().toInt());
    Point startPoint = Point(ui->departX->text().toDouble(),ui->departY->text().toDouble(),ui->departZ->text().toDouble());
    Point endPoint = Point(ui->arriveeX->text().toDouble(),ui->arriveeY->text().toDouble(),ui->arriveeZ->text().toDouble());
    newMission->setStartPoint(startPoint);
    newMission->setEndPoint(endPoint);

    newMission->setStartDate(ui->dateEdit->date());


     if (missionList->getMap()->contains(newMission->getid()) == false){
        missionList->getMap()->insert(newMission->getid(), newMission);

        int row = ui->missionListWidget->rowCount();
        QTableWidgetItem *newItem = new QTableWidgetItem(ui->nameTxt->text());
        ui->missionListWidget->insertRow(row);
        ui->missionListWidget->setItem(row, 0, newItem);

       qDebug() << newMission->toQString();

       }else{
            qDebug() << "Mission déjà existante";
       }

}

void missionWindow::closeEvent( QCloseEvent* event )
{
    missionList->save();//MissionProcess::saveMissions(missionList);

    for(int index : missionList->getMap()->keys()) {
        MissionProcess *mp = missionList->getMap()->take(index);
        delete mp;
    }
}


 

//From a QMAP<int, Drone> iterator, creates the QTableWidgetItems that are inserted in the table
void missionWindow::addDroneToTableWidget(QTableWidget* table, int row, QMap<int, Drone*>::iterator it, MissionProcess* mp)
{
    QTableWidgetItem *id = new QTableWidgetItem(QString::number(it.key()));
    table->setItem(row, 0, id);
    QTableWidgetItem *alt = new QTableWidgetItem(QString::number(it.value()->getDroneType().getMaxAltitude()));
    table->setItem(row, 1, alt);
    QTableWidgetItem *wc = new QTableWidgetItem(QString::number(it.value()->getDroneType().getWeightCapacity()));
    table->setItem(row, 2, wc);
    QTableWidgetItem *range = new QTableWidgetItem(QString::number(it.value()->getDroneType().getMaxRange()));
    table->setItem(row, 3, range);
    QTableWidgetItem *distance = new QTableWidgetItem(QString::number(it.value()->distanceFromStart(mp)));
    table->setItem(row, 4, distance);
}

bool missionWindow::droneCheck(QTableWidget* table)
{
    if(table->item(0, 0) == NULL)
    {
        QMessageBox erreur;
        erreur.setText("Aucun drone disponible pour cette combinaison de parametres !");
        erreur.setWindowTitle("Alerte");
        erreur.exec();

        return false;
    }
}

//Clears and deactivates indicated field
void missionWindow::resetField(QLineEdit *field)
{
    field->clear();
    field->setEnabled(false);
}



void missionWindow::on_altitudeTxt_editingFinished()
{
    mp->setAltitude(ui->altitudeTxt->text().toDouble());
    ui->compatibleDronesTable->clearContents();
    QMap<int, Drone*>::iterator it;
    int row = 0;
    for(it = myDrones->getMap()->begin(); it != myDrones->getMap()->end(); it++)
    {
        if(it.value()->hasAltitude(mp))
        {
            addDroneToTableWidget(ui->compatibleDronesTable, row, it, mp);
            row++;
            ui->chargeTxt->setEnabled(true);
        }
    }
    droneCheck(ui->compatibleDronesTable);
}

void missionWindow::on_chargeTxt_editingFinished()
{
    mp->setWeightCarge(ui->chargeTxt->text().toFloat());
    mp->setAltitude(ui->altitudeTxt->text().toDouble());
    ui->compatibleDronesTable->clearContents();
    QMap<int, Drone*>::iterator it;
    int row = 0;
    for(it = myDrones->getMap()->begin(); it != myDrones->getMap()->end(); it++)
    {
        if(it.value()->hasAltitude(mp))
        {
            if(it.value()->hasWeightCapacity(mp))
            {
                addDroneToTableWidget(ui->compatibleDronesTable, row, it, mp);
                row++;
                ui->departX->setEnabled(true);
                ui->departY->setEnabled(true);
                ui->departZ->setEnabled(true);
                ui->arriveeX->setEnabled(true);
                ui->arriveeY->setEnabled(true);
                ui->arriveeZ->setEnabled(true);
            }
        }
    }
    droneCheck(ui->compatibleDronesTable);

    //Disconnects the signal from the altitude field then connects it to the following field
    disconnect(ui->altitudeTxt, SIGNAL(editingFinished()), nullptr, nullptr);
    connect(ui->altitudeTxt, SIGNAL(editingFinished()), this, SLOT(on_chargeTxt_editingFinished()));

    //If LineEdit is empty after edition, deactivates the following fields
    if(ui->chargeTxt->text() == "")
    {
        resetField(ui->departX);
        resetField(ui->departY);
        resetField(ui->departZ);
        resetField(ui->arriveeX);
        resetField(ui->arriveeY);
        resetField(ui->arriveeZ);
    }

    //If previous field has null value, return to first step
    if(ui->altitudeTxt->text() == "")
    {
        //Reconnects the signal to the field slot
        disconnect(ui->altitudeTxt, SIGNAL(editingFinished()), nullptr, nullptr);
        connect(ui->altitudeTxt, SIGNAL(editingFinished()), this, SLOT(on_altitudeTxt_editingFinished()));
        //Clears and deactivates the following slots
        resetField(ui->chargeTxt);
        resetField(ui->departX);
        resetField(ui->departY);
        resetField(ui->departZ);
        resetField(ui->arriveeX);
        resetField(ui->arriveeY);
        resetField(ui->arriveeZ);

        //Reload full drone list
        QMap<int, Drone*>::iterator it;
        int row = 0;
        for (it = myDrones->getMap()->begin(); it != myDrones->getMap()->end(); it++)
        {
            addDroneToTableWidget(ui->compatibleDronesTable, row, it, mp);
            row++;
        }
    }
}

void missionWindow::on_departX_editingFinished()
{
    //Creation of a new point from the values inserted in the starting point fields
    Point spoint;
    spoint.SetLatitude(ui->departX->text().toDouble());
    spoint.SetLongitude(ui->departY->text().toDouble());
    spoint.SetAltitude(ui->departZ->text().toDouble());

    //Creation of a new point from the values inserted in the ending point fields
    Point epoint;
    epoint.SetLatitude(ui->arriveeX->text().toDouble());
    epoint.SetLongitude(ui->arriveeY->text().toDouble());
    epoint.SetAltitude(ui->arriveeZ->text().toDouble());

    //Assignation of both points to the mission
    mp->setStartPoint(spoint);
    mp->setEndPoint(epoint);

    ui->compatibleDronesTable->clearContents();
    QMap<int, Drone*>::iterator it;
    int row = 0;
    for(it = myDrones->getMap()->begin(); it != myDrones->getMap()->end(); it++)
    {
        if(it.value()->hasAltitude(mp))
        {
            if(it.value()->hasWeightCapacity(mp))
            {
                if(it.value()->hasRange(mp))
                {
                    addDroneToTableWidget(ui->compatibleDronesTable, row, it, mp);
                    row++;
                    ui->dateEdit->setEnabled(true);
                }
            }
        }
    }



}
