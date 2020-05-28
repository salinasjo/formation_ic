#include "form/mainwindow.h"
#include "form/loginwindow.h"
#include "form/trajectoryWindow.h"
#include <QApplication>
#include <iostream>
#include "include/test.h"
#include "include/FileDump.h"

#include <QDir>
#include <QMap>

#include <vector>
#include "include/User.h"
#include "include/Admin.h"
#include "include/Operator.h"
#include "include/Commander.h"
#include "include/WingType.h"
#include "include/DroneType.h"

#include "include/MissionProcess.h"
#include "include/Point.h"
#include "include/ControlPoint.h"
#include "include/Trajectory.h"

#include "include/DiscreteMap.h"
#include <include/mapinfo.h>
#include <QDebug>
#include <QPoint>
#include "form/dronewindow.h"
#include "form/missionwindow.h"

using namespace std;



int main(int argc, char *argv[])
{
    FileDump::ClearFile();
    FileDump::WriteLine("Start");
    qDebug() << "Start " << endl;

    QDir directory = QDir();
    QStringList images = directory.entryList(QStringList() << "*.png",QDir::Files);
    QString fileNameImg = "";
    foreach(QString filename, images) {
        QFile(filename).remove();
    }

    QApplication a(argc, argv);
	//MainWindow w;
	//w.show();
	LoginWindow lW;
	lW.show();
    //TrajectoryWindow tw;
    //tw.show();

    //missionWindow mw;
    //mw.show();

    //MapInfo map;
    //TODO from mission process


    //romain
    {
        //test translation
        Point lyon(45.75, 4.91 , 000);
        Point trs = lyon.Destination(0,200000);
        qDebug() << "200 km nord de Lyon " << trs.ToQString() << " distance=" << Point::computeDistance(lyon,trs);
        //test projection mercator
        MissionProcess mp;
        MapInfo map;
        mp.setEndPoint(Point(2.46, 48.8566, 500)); //Paris for default map
        mp.setStartPoint(Point(4.91, 45.75, 000));
        mp.setAltitude(1000);
        Drone toto(Point(),DroneType(125,200,200,321,352,WingType("heli",90)));
        mp.setActiveDrone(&toto);
        //DiscreteMap & dm = *mp.getMap(); //move to UI
        //TrajectoryWindow tw(dm);
        //tw.show();  // <-----------------------TRAJECTORY

//        qDebug() << dm.getMap()->ToQString();
//        qDebug() << dm.getMap()->GetScreenPos(Point(2.3522, 48.8566, 500));
//        qDebug() << dm.getMap()->GetScreenPos(Point(4.8357, 45.7640, 000));

//        QPoint ori(50,50);
//        Point proj = dm.getMap()->GetWorldPos(ori);
//        qDebug() << dm.getMap()->ToQString();
//        qDebug() << proj.ToQString() << " at " << ori;
//        QPoint ret = dm.getMap()->GetScreenPos(proj);
//        qDebug() << ret << " ret of " << proj.ToQString();


        //test point
        qDebug() << "------------------------------------" ;
        Point p0;
        qDebug() << p0.ToQString();
        Point p1(-5.57,10.36,20.15);
        qDebug() << p1.ToQString() ;
        Point p2 = Point(2,0,0);
        qDebug() << p2.ToQString() ;
        p1 = p2;
        qDebug() << p1.ToQString() ;
        p0.SetLatitude(4);
        p0.SetLongitude(5);
        p0.SetAltitude(0);
        p2.Set(5,4,0);
        double distance = p0.DistanceWithAltitude(p2);
        qDebug() << "Distance " << p0.ToQString() << " and " << p2.ToQString() << " = " << distance ;
        //operator point
        qDebug() << "Operations " ;
        Point A = Point(1,0,1);
        qDebug() << "A=" << A.ToQString() ;
        Point B = Point(0,1,0);
        qDebug() << "B=" <<  B.ToQString() ;
        qDebug() << "A+B " << (A+B).ToQString() ;
        qDebug() << "A-B " << (A-B).ToQString() ;
        qDebug() << "5A " << (5.0*A).ToQString() ;
        qDebug() ;
        qDebug() << "export trajectory in fileDump " ;

        //Control point
        //ControlPoint cp0;  ->ERROR NO TYPE
        ControlPoint cp0(ControlPointType::AUTOMATIC, 5.0, 48.2, -6479.0);
        ControlPoint cp1(ControlPointType::MANUAL);
        ControlPoint cp2(ControlPointType::ORIGIN, p1);
        cp1.UpdateInfos(125,65.0);
        cp1.SetLatitude(666.666);

        qDebug() << cp0.ToQString() ;
        qDebug() << cp1.ToQString() ;
        qDebug() << cp2.ToQString() ;

        //Trajectory
        //Trajectory t;  ->Error no origin and destination
        Trajectory t(p0,p2);
        t.ModifyPoint(1).Set(52,32,-900.254);
        t.AddNextPoint(Point(5,23,22),ControlPointType::MANUAL);
        t.AddNextPoint(Point(65.2,-33.254,987),ControlPointType::AUTOMATIC);
        t.AddPointAt(Point(0.01,0.01,0.01),ControlPointType::AUTOMATIC,2);
        t.SwitchPoint(1,2);
        t.DeletePoint(1);

        qDebug() << t.ToQString() ;

        qDebug() << "export trajectory in fileDump " ;
        Trajectory t2(Point(-10,-10,-100),Point(15,30,1000));
        t2.AddNextPoint(Point(0,0,200),ControlPointType::MANUAL);
        t2.AddNextPoint(Point(6,6,600),ControlPointType::MANUAL);
        qDebug() << t2.ToQString() ;
        //t2.Export(50);

        //mapinfo //moved to UI
//        MapInfo defaultMap;
//        MapInfo customMap(p0,p2);
//        qDebug() << "default map " << defaultMap.ToQString() ;
//        qDebug() << "custom map " << customMap.ToQString() ;
//        qDebug() << "is in default map (-250,-250) " << defaultMap.IsInMap(Point(-250,-250,0)) ;
//        qDebug() << "is in default map (10,10) " << defaultMap.IsInMap(Point(10,10,0)) ;
//        QPoint qp(10,10);
//        qDebug() << "world pos of (10,10) custom map " << customMap.GetWorldPos(qp).ToQString() ;
//        ControlPoint pc(ControlPointType::MANUAL, Point(51,13,0));
//        QPoint pp = customMap.GetScreenPos(pc);
//        qDebug() << "screen pos of (51,13,0) custom map (" << pp.x() << "/" << pp.y() << ")" ;


        qDebug() << "------------------------------------" ;
    }




    
    //joseph
    {
		SerializableCollection<Drone> *myDrones = new SerializableCollection<Drone>("drones.json", "drones");
		QMap<QString, User*> *myUsers = new QMap<QString, User*>();

		try {
			myDrones->load();
		}
		catch(const char *) {

		}

		Commander comm("DEVITO", "Danny", "DD", "1234");
		myUsers->insert(comm.getLogin(), &comm);
        WingType fixed("voilure fixe", 45.5);
        DroneType hale(500, 15000, 500, 430.25, 30.5, fixed);
        Point p(2,0,0);
		Drone d(p, hale);

		qDebug().noquote() << d.toQString();

		comm.addDrone(myDrones->getMap(), &d);

        qDebug() << "Array of Drones [" ;
		for(auto k : myDrones->getMap()->keys()) {
            qDebug() << "\tDrone ID : " << k ;
		}
		qDebug() << "]";


		Operator op("BOND", "James", "JB", "007");
		myUsers->insert(op.getLogin(), &op);

		Admin a("MASTER CHIEF", "John-117", "Halo", "Bungie");
		myUsers->insert(a.getLogin(), &a);
		User::saveUsers(myUsers);

    }



    //valentin
    {
		qDebug() << endl << "/////// DISCRETE MAP ////////" << endl;
        Trajectory t2(Point(-10,-10,-10),Point(15,30,10));
        MissionType mT("Recon", "Analyze area", 20, 15000);

        MissionProcess mP;
        mP.setMissionType(mT);

        //DiscreteMap dm(mP.getStartPoint(),mP.getEndPoint(),*mP.getActiveDrone(),1000.0); //should error
        //qDebug() << dm.toQString() ;
    }



    //lucas

    {
        SerializableCollection<Drone> *myDrones = new SerializableCollection<Drone>("drones.json", "drones");
        QMap<int, Drone *>::const_iterator dromap;

        try {
            myDrones->load();
        }
        catch(const char *) {


        }

//        bob.infos();
//        babe.infos();
//        shepard.infos();
        WingType fixed("voilure fixe", 45.5);
        WingType rotor("voilure mobile", 0);

        // Creation of drone types
        DroneType hale(700, 15000, 500, 430.25, 30.5, fixed);
        DroneType male(500, 10000, 550, 400, 28, rotor);
        DroneType nale(0, 2000, 200, 180, 5, rotor);
        DroneType bale(300, 13000, 350, 350, 40, fixed);
        DroneType kale(600, 17000, 450, 300, 20, rotor);
        DroneType sale(650, 18000, 400, 320, 25, fixed);

        Point p(2,46,0);
        Point p2(3, 49, 0);
//        // Creation of drone types
//        DroneType hale(700, 15000, 500, 430.25, 30.5, fixed);
//        DroneType male(500, 10000, 550, 400, 28, rotor);
//        DroneType nale(0, 2000, 200, 180, 5, rotor);
//        DroneType bale(300, 13000, 350, 350, 40, fixed);
//        DroneType kale(600, 17000, 450, 300, 20, rotor);
//        DroneType sale(650, 18000, 400, 320, 25, fixed);

        //Paris' coordinates
        Point start(2.3522, 48.8566, 500);
        //Lyon's coordinates
        Point finish(4.8357, 45.7640, 000);
        //Resulting distance = 367km or 391.499
        qDebug() << "Distance geo Lyon/paris = " << Point::computeDistance(start, finish);
        qDebug() << "Distance geo+Z Lyon/paris = " << start.DistanceWithAltitude(finish);

        //Creation of drones
        Drone d( p, hale);
        Drone d2( p, male);
        Drone d3(p, nale);
        Drone d4( p, bale);
        Drone d5( p, kale);
        Drone d6( p2, sale);

//        //Creation of drones
//        Drone d( p, hale);
//        Drone d2( p, male);
//        Drone d3(p, nale);
//        Drone d4( p, bale);
//        Drone d5( p, kale);
//        Drone d6( p2, sale);
        Commander comm("DEVITO", "Danny", "DD", "1234");

        //Adding drones to map
        comm.addDrone(myDrones->getMap(), &d);
        comm.addDrone(myDrones->getMap(), &d2);
        comm.addDrone(myDrones->getMap(), &d3);
        comm.addDrone(myDrones->getMap(), &d4);
        comm.addDrone(myDrones->getMap(), &d5);
        comm.addDrone(myDrones->getMap(), &d6);

        try {
            myDrones->save();
        } catch (const char *) {

        }

        // Creation of a mission type
        MissionType drop("Drop", "Drop payload at objective area", 200, 11000);

        // Instanciation of a new mission process
        MissionProcess *mp = new MissionProcess();

        // Attribution of the mission type to the process
        mp->setMissionType(drop);

        // Setting the start&finish points
        mp->setStartPoint(start);
        mp->setEndPoint(finish);

//        // Setting the start&finish points
//        mp->setStartPoint(start);
//        mp->setEndPoint(finish);

        // Creation of another mission process in order to attribute a drone to it
        MissionProcess *mp2 = new MissionProcess();
        mp2->setStartDate(QDate(2020, 05, 18));
        mp2->setActiveDrone(&d);

//        // Creation of another mission process in order to attribute a drone to it
//        MissionProcess *mp2 = new MissionProcess();
//        mp2->setStartDate(QDate(2020, 05, 18));
//        mp2->setActiveDrone(&d);

        // Checking for each drone in the map if it is compatible with the mission caracteristics
        for(dromap = myDrones->getMap()->constBegin(); dromap != myDrones->getMap()->constEnd(); dromap++)
        {
            if(dromap.value()->hasRange(mp)) //temp fixe
            {
                // If caracteristics match, check if it has the range
                //qDebug() << dromap.value()->ToQString().toStdString() << endl;
                if(dromap.value()->hasRange(mp))
                {
                    // If the drone matches the caracteristics and has the range, check if it is available at desired date
                    //qDebug() << dromap.value()->ToQString().toStdString() << endl;
                    if(dromap.value()->isAvailableAt(QDate(2020, 05, 18)))
                    {
                       qDebug() << dromap.value()->toQString();
                       // Compute the distance between drone's ground position and start point
                       qDebug() << "Distance drone/point de depart :" << dromap.value()->distanceFromStart(mp);
                    }
                }
            }
        }

        // Setting the start date
        mp-> setStartDate(QDate(2020, 05, 16));
        mp->setStartDate(QDate(2020, 05, 18));

//        // Setting the start date
//        mp-> setStartDate(QDate(2020, 05, 16));
//        mp->setStartDate(QDate(2020, 05, 18));

        // Setting the active drone
        mp->setActiveDrone(&d5);

    }

	qDebug() << endl << "END" << endl;

    FileDump::WriteLine("End");
    return a.exec();
}
