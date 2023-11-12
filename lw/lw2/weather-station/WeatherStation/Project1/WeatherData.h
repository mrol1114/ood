#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>

#include "Observer.h"

class Stats
{
public:
	void Update(double newValue)
	{
		if (m_min > newValue)
		{
			m_min = newValue;
		}
		if (m_max < newValue)
		{
			m_max = newValue;
		}
		m_sum += newValue;
		m_accurenceCount++;
	}

	double GetMin()
	{
		return m_min;
	}

	double GetMax()
	{
		return m_max;
	}

	double GetSum()
	{
		return m_sum;
	}

	double GetAccurenceCount()
	{
		return m_accurenceCount;
	}

private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_sum = 0;
	unsigned int m_accurenceCount = 0;
};

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo> // вынести в класс stats
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
		stats->Update(newValue);
	}

	void DisplayStats(StatsType type)
	{
		Stats& stats = m_statistics.at(type);
		std::string displayName = m_statsDisplayNames.at(type);

		std::cout << "Max " + displayName + " " << stats.GetMax() << std::endl;
		std::cout << "Min " + displayName + " " << stats.GetMin() << std::endl;
		std::cout << "Average " + displayName + " " << (stats.GetSum() / stats.GetAccurenceCount()) << std::endl;
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
	double GetTemperature()const
	{
		return m_temperature;
	}

	double GetHumidity()const
	{
		return m_humidity;
	}

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