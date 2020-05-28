#ifndef MAPINFO_H
#define MAPINFO_H

#include <QPixmap>
#include "ControlPoint.h"
#include <QPainter>

//MAPINFO FOR MERCATOR PROJECTION ONLY
//https://developers.google.com/maps/documentation/javascript/coordinates
class MapInfo
{
public:
    MapInfo();
    MapInfo(const Point & ori, const Point & dest);

    //MapInfo(double mapLngLeft, double mapLngRight, double mapLatBottom, double defaultAltitude);
    //MapInfo(double mapLngLeft, double mapLngRight, double mapLatBottom, double defaultAltitude,QString fileName);

    double longitudeLeft() const;
    double longitudeRight() const;

    double latitudeBottom() const;
    //void setOriginY(double originY);

    double defaultAltitude() const;
    void setDefaultAltitude(double defaultAltitude);

    void Draw(QPainter& painter,QPen& pen) const;

    bool IsInMap(const Point & p) const;

    //Added a point via coordinate GPS WORLD and I want it on the screen in PIXEL
    QPoint GetScreenPos(Point  p) const;

    //clicked a point on the screen and want is PIXEL postion to get WORLD
    Point GetWorldPos(QPoint  p) const;

    int GetScreenLength(Point a, Point b) const;

    QString ToQString() const;
    std::string ToString() const;

    static void GetZoomsLevel(QVector<double> & zooms);
    static double GetBestZoomLevel(double dist);

    void UpdateWithImage(const Point & start);

    //Point fromMercator(QPointF pt) const;
    //QPointF toMercator(Point p) const;

    QPixmap pixmap() const;
    void setPixmap(const QPixmap &pixmap);

protected:
    void Load(const Point & start, const Point & end);
    void CalCBound(const Point & ori, double dist);
    //void SetOrigin(Point ori);


    double _mapLngLeft;
    double _mapLngRight;
    double _mapLatBottom;
    double _defaultAltitude;
    QPixmap _pixmap;


    //QPointF GetCartesianFromScreen(QPoint &p) const;
    //QPoint GetScreenPosFromCartesian(QPointF pf) const;
};

#endif // MAPINFO_H
