#include "WeatherData.h"

int main()
{
	CIndoorWeatherData indoorWd;
	COutsideWeatherData outsideWd;

	CDisplay display;
	indoorWd.RegisterObserver(display, 2);

	CStatsDisplay statsDisplay;
	indoorWd.RegisterObserver(statsDisplay, 1);
	outsideWd.RegisterObserver(statsDisplay, 2);

	indoorWd.SetMeasurements(3, 0.7, 760);
	outsideWd.SetMeasurements(3, 0.7, 760, 50, 90);
	outsideWd.SetMeasurements(4, 0.8, 761, 60, 180);

	indoorWd.RemoveObserver(statsDisplay);

	indoorWd.SetMeasurements(10, 0.8, 761);
	outsideWd.SetMeasurements(-10, 0.8, 761, 60, 270);
	return 0;
}