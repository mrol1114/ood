#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>
#include <set>

#include "Observer.h"

enum class StatsType
{
	Temperature,
	Humidity,
	Pressure,
	WindSpeed,
	WindDirection,
};

class CWeatherData : public CObservable<CWeatherData>
{
public:
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

protected:
	const CWeatherData* GetSubject() const override
	{
		return this;
	}

	void UpdateMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	std::vector<StatsType> m_statsTypes = { StatsType::Humidity, StatsType ::Temperature, StatsType ::Pressure };
};

class COutsideWeatherData : public CWeatherData
{
public:
	void SetMeasurements(double temp, double humidity, double pressure)
	{
		UpdateMeasurements(temp, humidity, pressure);

		MeasurementsChanged();
	}
private:
	double m_windDirection = 0;
	double m_windSpeed = 0;
};

class CIndoorWeatherData : public CWeatherData
{
public:
	void SetMeasurements(double temp, double humidity, double pressure)
	{
		UpdateMeasurements(temp, humidity, pressure);

		MeasurementsChanged();
	}
};

class CDisplay : public IObserver<CWeatherData>
{
private:
	void Update(CWeatherData const& weatherData) override
	{
		if (auto indoorData = dynamic_cast<const CIndoorWeatherData*>(&weatherData))
		{
			std::cout << "Indoor weather:" << std::endl;
		}
		if (auto ousideData = dynamic_cast<const COutsideWeatherData*>(&weatherData))
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
	struct Stats
	{
		double min = std::numeric_limits<double>::infinity();
		double max = -std::numeric_limits<double>::infinity();
		double sum = 0;
		unsigned countAccurance = 0;
	};

	struct StaticStats
	{
		std::map<double, unsigned int> values = {};
		double maxEncounterKey = -std::numeric_limits<double>::infinity();
	};

	void Update(CWeatherData const& weatherData) override
	{
		UpdateStats(data.humidity, StatsType::Humidity);
		UpdateStats(data.pressure, StatsType::Pressure);
		UpdateStats(data.temperature, StatsType::Temperature);
		UpdateStats(data.windSpeed, StatsType::WindSpeed);
		UpdateStaticStats(data.windDirection, StaticStatsType::WindDirection);

		DisplayStats(StatsType::Humidity);
		DisplayStats(StatsType::Pressure);
		DisplayStats(StatsType::Temperature);
		DisplayStats(StatsType::WindSpeed);
		DisplayStaticStats(StaticStatsType::WindDirection);
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

	void UpdateStaticStats(double newValue, StaticStatsType type)
	{
		if (!m_staticStatistics.contains(type))
		{
			m_staticStatistics[type] = {};
		}

		StaticStats* stats = &m_staticStatistics.at(type);
		stats->values[newValue]++;

		if (!stats->values.contains(stats->maxEncounterKey)
			|| stats->values.at(stats->maxEncounterKey) < stats->values.at(newValue))
		{
			stats->maxEncounterKey = newValue;
		}
	}

	void DisplayStats(StatsType type)
	{
		const Stats& stats = m_statistics.at(type);
		const std::string& displayName = m_statsDisplayNames.at(type);

		std::cout << "Max " + displayName + " " << stats.max << std::endl;
		std::cout << "Min " + displayName + " " << stats.min << std::endl;
		std::cout << "Average " + displayName + " " << (stats.sum / stats.countAccurance) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	void DisplayStaticStats(StaticStatsType type)
	{
		const StaticStats& stats = m_staticStatistics.at(type);
		const std::string& displayName = m_staticStatsDisplayNames.at(type);

		std::cout << "Max " + displayName + " " << stats.values.rbegin()->first << std::endl;
		std::cout << "Min " + displayName + " " << stats.values.begin()->first << std::endl;
		std::cout << "Average " + displayName + " " << stats.maxEncounterKey << std::endl;
		std::cout << "----------------" << std::endl;
	}

	std::map<StatsType, Stats> m_statistics;
	std::map<StatsType, std::string> m_statsDisplayNames = {
		{StatsType::Temperature, "Temp"},
		{StatsType::Humidity, "Humidity"},
		{StatsType::Pressure, "Pressure"},
		{StatsType::WindSpeed, "Wind speed"},
	};

	std::map<StaticStatsType, StaticStats> m_staticStatistics;
	std::map<StaticStatsType, std::string> m_staticStatsDisplayNames = {
		{StaticStatsType::WindDirection, "Wind direction"},
	};
};