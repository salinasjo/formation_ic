#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <math.h>
#include <QString>

#include <QPoint>
#include "ISerializable.h"



class Point : ISerializable
{
    public:
        Point();
        Point(double latitude, double longitude , double alt=0.0);
        Point(const Point & other);
        Point& operator=(const Point & other);
        virtual ~Point();

        double GetAltitude() const { return _altitude; }
        void SetAltitude(double val) { _altitude = val; }
        double GetLongitude()  const { return _longitude; }
        void SetLongitude(double val) { _longitude = val; }
        double GetLatitude()  const { return _latitude; }
        void SetLatitude(double val) { _latitude = val; }
        void Set(double latitude, double longitude, double alt) { SetLatitude(latitude); SetLongitude(longitude); SetAltitude(alt);}
        void Set(Point other) { SetLatitude(other.GetLatitude()); SetLongitude(other.GetLongitude()); SetAltitude(other.GetAltitude());}

        //Compute geographical distance between points
        static double toRad(double degree) {return degree * (M_PI / 180.0); }
        static double toDegree(double rad) {return rad * (180.0 / M_PI); }
        static double computeDistance(const Point &, const Point &);

        //double GetDistance(const Point & other) const {return sqrt( pow(GetAltitude - other.GetAltitude,2) + pow(GetLongitude - other.GetLongitude,2) + pow(x() - other.x(),2) );}
        double DistanceWithAltitude(const Point & other) const;
        double Magnitude() const {return sqrt( pow(GetAltitude(),2) + pow(GetLongitude(),2) + pow(GetLatitude(),2) );}

        static double AngleABC(const Point& A,const Point& B,const Point& C);

        Point Destination(double bearing, double distance) const;

        void Normalize()
        {
            double dist =Magnitude();
            if(dist != 0.0)
                this->operator*=(1.0/dist);
        }
        Point& operator+=(const Point& other)
        {
            _longitude += other.GetLongitude();
            _latitude += other.GetLatitude();
            _altitude += other.GetAltitude();

            return *this;
        }
        Point& operator-=(const Point& other)
        {
            _longitude -= other.GetLongitude();
            _latitude -= other.GetLatitude();
            _altitude -= other.GetAltitude();

            return *this;
        }
        Point& operator*=(const double scalar)
        {
            _longitude *= scalar;
            _latitude *= scalar;
            _altitude *= scalar;

            return *this;
        }


        virtual std::string ToString() const;
        virtual QString ToQString() const;



    protected:
        double _latitude;
        double _longitude;
        double _altitude;


    private:
        inline void InitCore(double,double,double);




		// ISerializable interface
public:
		void readObject(const QJsonObject &json) override;
		void writeObject(QJsonObject &json) const override;
		int getid() const override;
};

inline Point operator+(const Point& lhs, const Point& rhs)
{
    return Point(lhs.GetLatitude()+rhs.GetLatitude(), lhs.GetLongitude()+rhs.GetLongitude(), lhs.GetAltitude()+rhs.GetAltitude());
}

inline Point operator-(const Point& lhs, const Point& rhs)
{
    return Point(lhs.GetLatitude()-rhs.GetLatitude(), lhs.GetLongitude()-rhs.GetLongitude(), lhs.GetAltitude()-rhs.GetAltitude());
}

inline Point operator*(const double lhs, const Point& rhs)
{
    return Point(lhs*rhs.GetLatitude(), lhs*rhs.GetLongitude(), lhs*rhs.GetAltitude());
}


#endif // POINT_H
