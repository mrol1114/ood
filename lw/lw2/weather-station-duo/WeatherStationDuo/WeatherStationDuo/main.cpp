#include "WeatherData.h"

int main()
{
	CIndoorWeatherData indoorWd;
	COutsideWeatherData outsideWd;

	CDisplay display;
	indoorWd.RegisterObserver(display, 2);
	outsideWd.RegisterObserver(display, 2);

	CStatsDisplay statsDisplay;
	indoorWd.RegisterObserver(statsDisplay, 1);

	indoorWd.SetMeasurements(3, 0.7, 760);
	outsideWd.SetMeasurements(4, 0.8, 761);

	indoorWd.RemoveObserver(statsDisplay);

	indoorWd.SetMeasurements(10, 0.8, 761);
	outsideWd.SetMeasurements(-10, 0.8, 761);
	return 0;
}