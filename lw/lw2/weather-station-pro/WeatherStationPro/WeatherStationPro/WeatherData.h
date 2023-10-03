#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>

#include "Observer.h"

enum class StatsType
{
	Temperature,
	Humidity,
	Pressure,
	WindSpeed,
	WindDirection,
};

namespace {
	const std::map<StatsType, std::string> STATS_DISPLAY_NAMES = {
		{ StatsType::Temperature, "Temp" },
		{ StatsType::Humidity, "Humidity" },
		{ StatsType::Pressure, "Pressure" },
		{ StatsType::WindSpeed, "Wind speed" },
		{ StatsType::WindDirection, "Wind direction" },
	};
}

class CDisplay : public IObserver<double, StatsType>
{
private:
	void Update(double const& data, StatsType type) override
	{
		std::cout << "Current " << STATS_DISPLAY_NAMES.at(type) << " " << data << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<double, StatsType>
{
public:
	CStatsDisplay()
	{
		for (auto type : m_types) {
			Stats stats;
			m_statistics[type] = stats;
		}

		for (auto type : m_staticTypes) {
			StaticStats stats;
			m_staticStatistics[type] = stats;
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

	void Update(double const& data, StatsType type)override
	{
		if (m_staticTypes.contains(type))
		{
			UpdateStaticStats(data, type);
			DisplayStaticStats(type);
		}
		else if (m_types.contains(type))
		{
			UpdateStats(data, type);
			DisplayStats(type);
		}
		else
		{
			throw std::runtime_error("Passed unknown type");
		}
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

	void UpdateStaticStats(double newValue, StatsType type)
	{
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
		const std::string& displayName = STATS_DISPLAY_NAMES.at(type);

		std::cout << "Max " + displayName + " " << stats.max << std::endl;
		std::cout << "Min " + displayName + " " << stats.min << std::endl;
		std::cout << "Average " + displayName + " " << (stats.sum / stats.countAccurance) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	void DisplayStaticStats(StatsType type)
	{
		const StaticStats& stats = m_staticStatistics.at(type);
		const std::string& displayName = STATS_DISPLAY_NAMES.at(type);

		std::cout << "Max " + displayName + " " << stats.values.rbegin()->first << std::endl;
		std::cout << "Min " + displayName + " " << stats.values.begin()->first << std::endl;
		std::cout << "Average " + displayName + " " << stats.maxEncounterKey << std::endl;
		std::cout << "----------------" << std::endl;
	}

	const std::set<StatsType> m_staticTypes = { StatsType::WindDirection };
	const std::set<StatsType> m_types = { 
		StatsType::Temperature, StatsType::Humidity, StatsType::Pressure, StatsType::WindSpeed
	};

	std::map<StatsType, Stats> m_statistics;
	std::map<StatsType, StaticStats> m_staticStatistics;
};

class CWeatherData : public CObservable<double, StatsType>
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

	double GetWindSpeed()const
	{
		return m_windSpeed;
	}

	double GetWindDirection()const
	{
		return m_windDirection;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed,
		double windDirection)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windSpeed = windSpeed;
		m_windDirection = windDirection;

		MeasurementsChanged();
	}

protected:
	double GetChangedData(StatsType type)const override
	{
		switch(type)
		{
		case StatsType::Temperature:
			return GetTemperature();
		case StatsType::Humidity:
			return GetHumidity();
		case StatsType::Pressure:
			return GetPressure();
		case StatsType::WindSpeed:
			return GetWindSpeed();
		case StatsType::WindDirection:
			return GetWindDirection();
		};
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0.0;
	double m_windDirection = 0.0;
};