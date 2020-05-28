#include "include/Point.h"

#include <QLineF>
#include <sstream>
//#include <math.h>

Point::Point():_latitude(0.0),_longitude(0.0),_altitude(0.0)
{
    //ctor
}

Point::Point(double latitude, double longitude , double alt)
{
    //ctor
    InitCore(latitude,longitude,alt);
}

Point::Point(const Point & other)
{
    InitCore(other.GetLatitude(),other.GetLongitude(),other.GetAltitude());
}


Point& Point::operator=(const Point & other)
{
    if(this != &other)
    {
        InitCore(other.GetLatitude(),other.GetLongitude(),other.GetAltitude());
    }
    return *this;
}

void Point::InitCore(double latitude, double longitude , double alt)
{
    _altitude = alt;
    _latitude = latitude;
    _longitude = longitude;
}

double Point::computeDistance(const Point &p1, const Point &p2)
{
    double dist = 0;
    // Conversion from degrees to radian
    double lat1 = toRad(p1.GetLatitude());
    double long1 = toRad(p1.GetLongitude());
    double lat2 = toRad(p2.GetLatitude());
    double long2 = toRad(p2.GetLongitude());

    // Earth radius in km
    double radius = 6378000;

    //Haversine Formula
    double dlong = long1 - long2;

    dist = sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(dlong);
    dist = acos(dist);
    dist = dist * radius;

    return dist;
    //from https://www.movable-type.co.uk/scripts/latlong.html
    //alternative
    /*double lat1 = toRad(p1.GetLatitude());
    double lat2 = toRad(p2.GetLatitude());
    double deltaLat = toRad(p2.GetLatitude()-p1.GetLatitude());
    double deltaLong = toRad(p2.GetLongitude()-p1.GetLongitude());

    double a = sin(deltaLat/2.0) * sin(deltaLat/2.0) +
            cos(lat1) * cos(lat2) *
            sin(deltaLong/2.0) * sin(deltaLong/2.0);

    double c = 2.0 * atan2(sqrt(a),sqrt(1.0-a));

    double R = 6371000;

    return R*c;*///1000.0;
    //in m
}

double Point::DistanceWithAltitude(const Point &other) const
{
    //return computeDistance(*this,other)+std::abs(this->z()-other.z());
    double geoDistanceXY = computeDistance(*this,other);
    double distanceZ = std::abs(this->GetAltitude()-other.GetAltitude());
    //pythagore
    /*
                                              |
                                              |
                                           distance Z
                                              |
                                              |
      --------------------geoDistanceXY-------
     */
    return  sqrt(geoDistanceXY*geoDistanceXY+distanceZ*distanceZ);
}

double Point::AngleABC(const Point &A, const Point &B, const Point &C)
{
    QPointF qA(A.GetLongitude(),A.GetLatitude());
    QPointF qB(B.GetLongitude(),B.GetLatitude());
    QPointF qC(C.GetLongitude(),C.GetLatitude());
    QLineF u(qA,qB);
    QLineF v(qC,qB);
    return u.angle(v);
}

Point Point::Destination(double bearing, double distance) const
{
    double R = 6371000;

    bearing=Point::toRad(bearing);
    double lat = toRad(GetLatitude());
    double longi = toRad(GetLongitude());
    double angularDist = distance/R;
    double lat2 = asin( sin(lat)*cos(angularDist) + cos(lat)*sin(angularDist)*cos(bearing) );
    double longi2 = longi + atan2( sin(bearing)*sin(angularDist)*cos(lat),cos(angularDist)-sin(lat)*sin(lat2) );
    return Point(toDegree(lat2),toDegree(longi2),GetAltitude());
}


std::string Point::ToString() const
{
    std::stringstream ss;
    ss << "Point " << this << " latitude=" << GetLatitude() << " longitude=" << GetLongitude() << " altitude=" << GetAltitude() << ")";
    return ss.str();
}

QString Point::ToQString() const
{
    return  QString::fromStdString(ToString());
}

//dtor
Point::~Point()
{
    //std::cout << "Destruction Point" << std::endl;
}




void Point::readObject(const QJsonObject &json)
{
	if (json.contains("latitude"))
	{
		SetLatitude(json["latitude"].toDouble());
	}
	if (json.contains("longitude"))
	{
		SetLongitude(json["longitude"].toDouble());
	}
	if (json.contains("altitude"))
	{
		SetAltitude(json["altitude"].toDouble());
	}
}

void Point::writeObject(QJsonObject &json) const
{
	json["latitude"] = _latitude;
	json["longitude"] = _longitude;
	json["altitude"] = _altitude;
}

//Unused
int Point::getid() const
{
	return 0;
}
