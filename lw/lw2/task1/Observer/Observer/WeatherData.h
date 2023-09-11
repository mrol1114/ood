#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>

#include "Observer.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
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

	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		UpdateStats(data.humidity, StatsType::Humidity);
		UpdateStats(data.pressure, StatsType::Pressure);
		UpdateStats(data.temperature, StatsType::Temperature);

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

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
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
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};