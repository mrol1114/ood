#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>
#include <cmath>

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

	double GetMin()const
	{
		return m_min;
	}

	double GetMax()const
	{
		return m_max;
	}

	double GetSum()const
	{
		return m_sum;
	}

	double GetAccurenceCount()const
	{
		return m_accurenceCount;
	}

private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_sum = 0;
	unsigned int m_accurenceCount = 0;
};

class WindStats
{
public:
	void Update(double newValue)
	{
		m_cosSum += std::cos(ConvertDegreesToRadians(newValue));
		m_sinSum += std::sin(ConvertDegreesToRadians(newValue));
	}

	double GetAverageWindDirection()
	{
		return ConvertRadiansToDegrees(std::atan2(m_sinSum, m_cosSum));
	}

private:
	double ConvertDegreesToRadians(double degrees)
	{
		return degrees / 180 * M_PI;
	}

	double ConvertRadiansToDegrees(double degrees)
	{
		return degrees / M_PI * 180;
	}

private:
	double m_cosSum = 0;
	double m_sinSum = 0;
};

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
	}

private:
	void Update(double const& data, StatsType type)override
	{
		UpdateStats(data, type);

		if (type == StatsType::WindDirection)
		{
			DisplayWindStats();
		}
		else
		{
			DisplayStats(type);
		}
	}

	void UpdateStats(double newValue, StatsType type)
	{
		if (type == StatsType::WindDirection)
		{
			m_windStats.Update(newValue);
		}
		else
		{
			Stats* stats = &m_statistics.at(type);
			stats->Update(newValue);
		}
	}

	void DisplayStats(StatsType type)
	{
		const Stats& stats = m_statistics.at(type);
		const std::string& displayName = STATS_DISPLAY_NAMES.at(type);

		std::cout << "Max " + displayName + " " << stats.GetMax() << std::endl;
		std::cout << "Min " + displayName + " " << stats.GetMin() << std::endl;
		std::cout << "Average " + displayName + " " << (stats.GetSum() / stats.GetAccurenceCount())
			<< std::endl;
		std::cout << "----------------" << std::endl;
	}

	void DisplayWindStats()
	{
		const std::string& displayName = STATS_DISPLAY_NAMES.at(StatsType::WindDirection);

		std::cout << "Average " + displayName + " " << m_windStats.GetAverageWindDirection()
			<< std::endl;
		std::cout << "----------------" << std::endl;
	}

	const std::set<StatsType> m_types = {
		StatsType::Temperature, StatsType::Humidity, StatsType::Pressure, StatsType::WindSpeed
	};
	std::map<StatsType, Stats> m_statistics;
	WindStats m_windStats;
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