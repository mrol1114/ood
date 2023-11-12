#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>

#include "Observer.h"
// пенести определение в observer 
class CWeatherData : public CObservable<CWeatherData>
{
public:
	enum class WeatherDataType
	{
		Indoor,
		Outdoor,
	};

	virtual WeatherDataType GetType() const = 0;

	double GetTemperature() const
	{
		return m_temperature;
	}

	double GetHumidity() const
	{
		return m_humidity;
	}

	double GetPressure() const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}

protected:
	const CWeatherData* GetSubject() const override
	{
		return this;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

class COutsideWeatherData : public CWeatherData
{
public:
	WeatherDataType GetType()const override
	{
		return WeatherDataType::Outdoor;
	}
};

class CIndoorWeatherData : public CWeatherData
{
public:
	WeatherDataType GetType()const override
	{
		return WeatherDataType::Indoor;
	}
};

class CDisplay : public IObserver<CWeatherData>
{
private:
	void Update(CWeatherData const& weatherData) override
	{
		if (weatherData.GetType() == CWeatherData::WeatherDataType::Indoor)
		{
			std::cout << "Indoor weather:" << std::endl;
		}
		if (weatherData.GetType() == CWeatherData::WeatherDataType::Outdoor)
		{
			std::cout << "Outdoor weather:" << std::endl;
		}

		std::cout << "Current Temp " << weatherData.GetTemperature() << std::endl;
		std::cout << "Current Hum " << weatherData.GetHumidity() << std::endl;
		std::cout << "Current Pressure " << weatherData.GetPressure() << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<CWeatherData>
{
public:
	CStatsDisplay()
	{
		for (const auto& [key, value] : m_statsDisplayNames) {
			Stats stats;
			m_statistics[key] = stats;
		}
	}

private:
	enum class StatsType
	{
		Temperature,
		Humidity,
		Pressure
	};

	struct Stats
	{
		double min = std::numeric_limits<double>::infinity();
		double max = -std::numeric_limits<double>::infinity();
		double sum = 0;
		unsigned countAccurance = 0;
	};

	void Update(CWeatherData const& weatherData) override
	{
		if (weatherData.GetType() == CWeatherData::WeatherDataType::Indoor)
		{
			std::cout << "Indoor weather:" << std::endl;
		}
		if (weatherData.GetType() == CWeatherData::WeatherDataType::Indoor)
		{
			std::cout << "Outside weather:" << std::endl;
		}

		UpdateStats(weatherData.GetHumidity(), StatsType::Humidity);
		UpdateStats(weatherData.GetPressure(), StatsType::Pressure);
		UpdateStats(weatherData.GetTemperature(), StatsType::Temperature);

		DisplayStats(StatsType::Humidity);
		DisplayStats(StatsType::Pressure);
		DisplayStats(StatsType::Temperature);
	}

	void UpdateStats(double newValue, StatsType type)
	{
		Stats* stats = &m_statistics.at(type);

		if (stats->min > newValue)
		{
			stats->min = newValue;
		}
		if (stats->max < newValue)
		{
			stats->max = newValue;
		}
		stats->sum += newValue;
		++stats->countAccurance;
	}

	void DisplayStats(StatsType type)
	{
		Stats stats = m_statistics.at(type);
		std::string displayName = m_statsDisplayNames.at(type);

		std::cout << "Max " + displayName + " " << stats.max << std::endl;
		std::cout << "Min " + displayName + " " << stats.min << std::endl;
		std::cout << "Average " + displayName + " " << (stats.sum / stats.countAccurance) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	std::map<StatsType, Stats> m_statistics;
	std::map<StatsType, std::string> m_statsDisplayNames = {
		{StatsType::Temperature, "Temp"},
		{StatsType::Humidity, "Humidity"},
		{StatsType::Pressure, "Pressure"}
	};
};