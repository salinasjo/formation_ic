#include "include/mapinfo.h"

#include <include/FileDump.h>
#include <QDebug>
#include <QDir>
#include <sstream>
#include <windows.h>

MapInfo::MapInfo()
{
    //use with paris coord (2,48) and (4,45) -> start and end point
    _mapLngLeft = -4.797;
    _mapLngRight = 16.2743;
    _mapLatBottom = 43.05;
    _defaultAltitude = 500.0;
    _pixmap.load(":/new/image/image/franceGmapsmall.png");//_pixmap.load(":/new/image/satImage.jpg");
}


MapInfo::MapInfo(const Point & start, const Point & end)
{
    Load(start,end);
    _pixmap.load(":/new/image/image/pleaseWait.jpg");
}


//MapInfo::MapInfo(double mapLngLeft, double mapLngRight, double mapLatBottom, double defaultAltitude)
//{
//    _mapLngLeft = mapLngLeft;
//    _mapLngRight = mapLngRight;
//    _mapLatBottom = mapLatBottom;
//    _defaultAltitude = defaultAltitude;
//    _pixmap.load(":/new/image/image/franceGmapsmall.png");//_pixmap.load(":/new/image/satImage.jpg"); //TODO : not default
//}

//MapInfo::MapInfo(double mapLngLeft, double mapLngRight, double mapLatBottom, double defaultAltitude, QString fileName)
//{
//    _mapLngLeft = mapLngLeft;
//    _mapLngRight = mapLngRight;
//    _mapLatBottom = mapLatBottom;
//    _defaultAltitude = defaultAltitude;
//    _pixmap.load(fileName);
//}

double MapInfo::longitudeLeft() const
{
    return _mapLngLeft;
}

double MapInfo::longitudeRight() const
{
    return _mapLngRight;
}

double MapInfo::latitudeBottom() const
{
    return _mapLatBottom;
}

double MapInfo::defaultAltitude() const
{
    return _defaultAltitude;
}

void MapInfo::setDefaultAltitude(double defaultAltitude)
{
    _defaultAltitude = defaultAltitude;
}



void MapInfo::Draw(QPainter &painter, QPen &pen) const
{
    painter.drawPixmap(0, 0, _pixmap);
}

bool MapInfo::IsInMap(const Point &p) const
{
    QPoint qp = GetScreenPos(p);
    if(qp.x() < 0 || qp.x() > _pixmap.width())
        return false;
    if(qp.y() < 0 || qp.y() > _pixmap.height())
        return false;
    return true;
}

//QPoint MapInfo::GetScreenPosFromCartesian(QPointF pf) const
//{
//    QPoint qp;
//    if(_pixelScaleInMeter<=0.0)
//    {
//        FileDump::WriteLine("pixelscale is 0 in mapinfo");
//        return qp;
//    }
//    double originX = _originTopLeftMapCartesian.x();
//    double originY = _originTopLeftMapCartesian.y();
//    int screenX = round((pf.x() - originX)/_pixelScaleInMeter);
//    int screenY = round((pf.y() - originY)/_pixelScaleInMeter);
//    qp.setX(screenX);
//    qp.setY(screenY);
//    return qp;
//}

//QPointF MapInfo::GetCartesianFromScreen(QPoint &p) const
//{
//    QPointF pw;
//    double originX = _originTopLeftMapCartesian.x();
//    double originY = _originTopLeftMapCartesian.y();
//    pw.setX(originX + (double)p.x() * _pixelScaleInMeter);
//    pw.setY(originY + (double)p.y() * _pixelScaleInMeter);
//    return pw;
//}

//https://fr.wikipedia.org/wiki/Projection_de_Mercator
//https://stackoverflow.com/questions/14329691/convert-latitude-longitude-point-to-a-pixels-x-y-on-mercator-projection
//https://github.com/mfeldheim/hermap/blob/master/src/Geo/Projection.php
//https://stackoverflow.com/questions/2103924/mercator-longitude-and-latitude-calculations-to-x-and-y-on-a-cropped-map-of-the/10401734#10401734
QPoint MapInfo::GetScreenPos(Point p) const
{
    double latitude = p.GetLatitude();
    double longitude = p.GetLongitude();
    double mapWidth = _pixmap.width();
    double mapHeight = _pixmap.height();
    double  mapLatBottomRad = _mapLatBottom * M_PI / 180.0;
    double  latitudeRad = latitude * M_PI / 180.0;
    double  mapLngDelta = (_mapLngRight - _mapLngLeft);

    double  worldMapWidth = ((mapWidth / mapLngDelta) * 360.0) / (2.0 * M_PI);
    double  mapOffsetY = (worldMapWidth / 2.0 * log((1.0 + sin(mapLatBottomRad)) / (1.0 - sin(mapLatBottomRad))));

    double  x = (longitude - _mapLngLeft) * (mapWidth / mapLngDelta);
    double  y = mapHeight - ((worldMapWidth / 2.0 * log((1.0 + sin(latitudeRad)) / (1.0 - sin(latitudeRad)))) - mapOffsetY);

    return QPoint(x, y);
}




Point MapInfo::GetWorldPos(QPoint qp) const
{
    double ty = qp.y();
    double tx = qp.x();
    double mapLatBottomRadian = Point::toRad(_mapLatBottom);
    double mapLonDelta = _mapLngRight - _mapLngLeft;
    double mapWidth = _pixmap.width();
    double mapHeight = _pixmap.height();
    /* called worldMapWidth in Raphael's Code, but I think that's the radius since it's the map width or circumference divided by 2*PI  */
    double worldMapRadius = mapWidth / mapLonDelta * 360/(2 *   M_PI);
    double mapOffsetY = ( worldMapRadius / 2 * log( (1 + sin(mapLatBottomRadian) ) / (1 - sin(mapLatBottomRadian))  ));
    double equatorY = mapHeight + mapOffsetY;
    double a = (equatorY-ty)/worldMapRadius;

    double lat = 180/  M_PI * (2 * atan(exp(a)) -   M_PI/2);
    double longi = _mapLngLeft+tx/mapWidth*mapLonDelta;
    Point ret;
    ret.SetLatitude(lat);
    ret.SetLongitude(longi);
    return ret;
}

int MapInfo::GetScreenLength(Point a, Point b) const
{
    QPoint qa = GetScreenPos(a);
    QPoint qb = GetScreenPos(b);
    QLineF ab = QLineF(qa,qb);

    return round(ab.length());
}

QString MapInfo::ToQString() const
{
    return  QString::fromStdString(ToString());
}

std::string MapInfo::ToString() const
{
    std::stringstream ss;
    ss << "Mapinfo " << this << " latitude bottom=" << _mapLatBottom << " longitude left=" << _mapLngLeft << " longitude right=" << _mapLngRight;
    ss << " defaultAltitude=" << _defaultAltitude << " pixmap=" << _pixmap.width() << "x" << _pixmap.height();
    return ss.str();
}

void MapInfo::GetZoomsLevel(QVector<double> &zooms)
{
    zooms.push_back(38);
    zooms.push_back(76);
    zooms.push_back(152);
    zooms.push_back(303);
    zooms.push_back(606);
    zooms.push_back(1213);
    zooms.push_back(2426);
    zooms.push_back(4851);
    zooms.push_back(9703);
    zooms.push_back(19405);
    zooms.push_back(38810);
    zooms.push_back(77621);
    zooms.push_back(155241);
    zooms.push_back(310483);
    zooms.push_back(620966);
    zooms.push_back(1207212);
    zooms.push_back(2422726);
    zooms.push_back(4845452);
    zooms.push_back(9690904);
}

double MapInfo::GetBestZoomLevel(double dist)
{
    QVector<double> zooms;
    GetZoomsLevel(zooms);
    int zoomIndexBest = -1;
    for(int zoomIndex = 0; zoomIndex < zooms.size()-1; zoomIndex++)
    {
        if(zooms[zoomIndex+1] > dist && zooms[zoomIndex] < dist)
        {
            zoomIndexBest = zoomIndex;
            break;
        }
    }
    if(zoomIndexBest == -1)
        return zooms[zooms.size()-1];
    double diff = zooms[zoomIndexBest+1] - dist;
    if(diff < (zooms[zoomIndexBest] - dist))
        return zooms[zoomIndexBest+1];
    return  zooms[zoomIndexBest] ;
}

void MapInfo::UpdateWithImage(const Point & start)
{
    double zoomLevel = 1000.0;
    QDir directory = QDir();
    QStringList images = directory.entryList(QStringList() << "*.png",QDir::Files);
    QString fileNameImg = "";
    foreach(QString filename, images) {
        fileNameImg=filename;
        zoomLevel = filename.split(".")[0].toDouble();
    }
    CalCBound(start,zoomLevel);
    _pixmap.load(fileNameImg);
}

void MapInfo::Load(const Point & start, const Point & end)
{
    QString quoteEscaped = "\"";
    qDebug() << quoteEscaped;
    double dist = Point::computeDistance(start, end);
    qDebug() << "distance" << dist;
    dist = MapInfo::GetBestZoomLevel(dist*2.0);
    qDebug() << "zoom" << dist;
    QString param = quoteEscaped + QString::number(start.GetLatitude()) + quoteEscaped + " " + quoteEscaped + QString::number(start.GetLongitude()) + quoteEscaped + " " + quoteEscaped + QString::number(dist) + quoteEscaped ;
    QByteArray ba = param.toLocal8Bit();
    const char *c_str2 = ba.data();
    qDebug()  << param;
    //qDebug() << "param" << param;
    //ShellExecuteA(NULL,"open","D:\\dev\\selenium\\test build\\roboto.jar",c_str2,0,SW_NORMAL);
    ShellExecuteA(NULL,"open","roboto.jar",c_str2,0,SW_NORMAL);
}

void MapInfo::CalCBound(const Point &start, double distance)
{
    Point pLeft = start.Destination(270,distance);
    Point pRight = start.Destination(90,distance);
    Point pBottom = start.Destination(180,distance/2.0);

    _mapLngLeft = pLeft.GetLongitude();
    _mapLngRight = pRight.GetLongitude();
    _mapLatBottom = pBottom.GetLatitude();
}

//Point MapInfo::fromMercator(QPointF pt) const
//{
//    const double EARTH_RADIUS = 6371000;//20037508.34;//

//    double lon = (pt.x() / EARTH_RADIUS) * 180.0;
//    double lat = (pt.y() / EARTH_RADIUS) * 180.0;
//    lat = 180.0 / M_PI * (2 * atan(exp(lat * M_PI / 180.0)) - M_PI / 2.0);
//    Point p;
//    p.SetLatitude(lat);
//    p.SetLongitude(lon);

//    return p;

//}

//QPointF MapInfo::toMercator(Point p) const
//{
//    const double EARTH_RADIUS = 6371000;//20037508.34;//

//    double x = p.GetLongitude() * EARTH_RADIUS / 180.0;
//    double y = log(tan((90.0 + p.GetLatitude()) * M_PI / 360.0)) / (M_PI / 180.0);
//    y = y * EARTH_RADIUS / 180.0;

//    return QPointF(x, y);
//}

QPixmap MapInfo::pixmap() const
{
    return _pixmap;
}

void MapInfo::setPixmap(const QPixmap &pixmap)
{
    _pixmap = pixmap;
}


