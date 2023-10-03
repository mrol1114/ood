#include "WeatherData.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display, 2, StatsType::WindSpeed);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 1, StatsType::WindDirection);

	wd.SetMeasurements(3, 0.7, 760, 50, 90);
	wd.SetMeasurements(4, 0.8, 761, 60, 180);

	wd.RemoveObserver(statsDisplay, StatsType::WindDirection);

	wd.SetMeasurements(10, 0.8, 761, 50, 180);
	wd.SetMeasurements(-10, 0.8, 761, 60, 270);
	return 0;
}