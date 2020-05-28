#ifndef DRONETYPE_H
#define DRONETYPE_H
#include "WingType.h"


class DroneType
{
    public:
		DroneType();
		DroneType(float, double, double, float, float, WingType);
		DroneType(const DroneType &);
		DroneType& operator=(const DroneType &);
        virtual ~DroneType();

		float getWeightCapacity() const { return _weightCapacity; }
        void setWeightCapacity(float val) { _weightCapacity = val; }
        double getMaxAltitude() const { return _maxAltitude; }
        void setMaxAltitude(double val) { _maxAltitude = val; }
		double getMaxRange() const { return _maxRange; }
        double getMaxRangeMeter() const { return _maxRange*1000.0; }
        void setMaxRange(double val) { _maxRange = val; }
		float getCruiseSpeed() const { return _cruiseSpeed; }
        void setCruiseSpeed(float val) { _cruiseSpeed = val; }
		float getAutonomy() const { return _autonomy; }
        void setAutonomy(float val) { _autonomy = val; }
		WingType getWingType() const { return _wingType; }
		void setWingType(WingType val) { _wingType = val; }


		void readObject(const QJsonObject &json);
		void writeObject(QJsonObject &json) const;

        //Temporary to check the good creation
        void infos();
		QString toQString();
		std::string toString();

    protected:

    private:
        float _weightCapacity; //kg
        double _maxAltitude; //m
        double _maxRange; //km at cruise speed
        float _cruiseSpeed; //km/h
        float _autonomy; //h
		WingType _wingType;
};

#endif // DRONETYPE_H
