#pragma once

#include <iostream>
#include <algorithm>
#include <climits>
#include <map>
#include <set>
#include <functional>

#include "Observer.h"
#include "Stats.h"

enum class StatsType
{
	Temperature,
	Humidity,
	Pressure,
	WindSpeed,
	WindDirection,
};

namespace
{
	const std::map<StatsType, std::string> STATS_DISPLAY_NAMES = {
		{StatsType::Temperature, "Temp"},
		{StatsType::Humidity, "Humidity"},
		{StatsType::Pressure, "Pressure"},
		{StatsType::WindSpeed, "Wind speed"},
		{StatsType::WindDirection, "Wind direction"},
	};
}

class CWeatherData : public CObservable<CWeatherData>
{
public:
	using Data = std::map<StatsType, std::function<double()>>;

	enum class WeatherDataType
	{
		Indoor,
		Outdoor,
	};

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		NotifyObservers();
	}

	const Data& GetData()const
	{
		return m_stats;
	}

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

	virtual WeatherDataType GetType()const = 0;

protected:
	CWeatherData(const Data& additionalStats = {})
	{
		m_stats.insert(additionalStats.begin(), additionalStats.end());
	}

	const CWeatherData* GetSubject() const override
	{
		return this;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	Data m_stats = {
		{StatsType::Humidity, [&]() { return this->GetHumidity(); }},
		{StatsType::Temperature, [&]() { return this->GetTemperature(); }},
		{StatsType::Pressure, [&]() { return this->GetPressure(); }},
	};
};

class COutsideWeatherData : public CWeatherData
{
public:
	COutsideWeatherData()
		: CWeatherData({
			{StatsType::WindSpeed, [&]() { return this->GetWindSpeed(); }},
			{StatsType::WindDirection, [&]() { return this->GetWindDirection(); }}
		})
	{
	}

	void SetMeasurements(
		double temp,
		double humidity,
		double pressure,
		double windDirection,
		double windSpeed)
	{
		m_windDirection = windDirection;
		m_windSpeed = windSpeed;
		CWeatherData::SetMeasurements(temp, humidity, pressure);
	}

	WeatherDataType GetType()const override
	{
		return  CWeatherData::WeatherDataType::Outdoor;
	}

	double GetWindDirection()
	{
		return m_windDirection;
	}

	double GetWindSpeed()
	{
		return m_windSpeed;
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
		CWeatherData::SetMeasurements(temp, humidity, pressure);
	}

	WeatherDataType GetType()const override
	{
		return  CWeatherData::WeatherDataType::Indoor;
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

		for (auto [statsType, getter] : weatherData.GetData())
		{
			std::cout << "Current " << STATS_DISPLAY_NAMES.at(statsType) << " " << getter()
				<< std::endl;
		}
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<CWeatherData>
{
public:
	CStatsDisplay()
	{
		for (auto type : m_INDOOR_STATS) {
			Stats stats;
			m_statistics[CWeatherData::WeatherDataType::Indoor][type] = stats;
		}

		for (auto type : m_OUTDOOR_STATS) {
			Stats stats;
			m_statistics[CWeatherData::WeatherDataType::Outdoor][type] = stats;
		}
	}

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

		for (auto [statsType, getter] : weatherData.GetData())
		{
			UpdateStats(getter(), statsType, weatherData.GetType());
		}

		for (const auto& [statsType, stats] : m_statistics[weatherData.GetType()])
		{
			if (statsType == StatsType::WindDirection)
			{
				DisplayWindStats();
			}
			else
			{
				DisplayStats(weatherData.GetType(), statsType);
			}
		}
		std::cout << "----------------" << std::endl;
	}

	void UpdateStats(double newValue, StatsType statsType, CWeatherData::WeatherDataType dataType)
	{
		if (statsType == StatsType::WindDirection)
		{
			m_windStats.Update(newValue);
		}
		else
		{
			Stats* stats = &m_statistics.at(dataType).at(statsType);
			stats->Update(newValue);
		}
	}

	void DisplayStats(CWeatherData::WeatherDataType dataType, StatsType statsType)
	{
		const Stats& stats = m_statistics.at(dataType).at(statsType);
		const std::string& displayName = STATS_DISPLAY_NAMES.at(statsType);

		std::cout << "Max " + displayName + " " << stats.GetMax() << std::endl;
		std::cout << "Min " + displayName + " " << stats.GetMin() << std::endl;
		std::cout << "Average " + displayName + " " << (stats.GetSum() / stats.GetAccurenceCount())
			<< std::endl << std::endl;
	}

	void DisplayWindStats()
	{
		const std::string& displayName = STATS_DISPLAY_NAMES.at(StatsType::WindDirection);

		std::cout << "Average " + displayName + " " << m_windStats.GetAverageWindDirection()
			<< std::endl;
	}
	
	const std::set<StatsType> m_INDOOR_STATS = { 
		StatsType::Humidity, StatsType::Pressure, StatsType::Temperature
	};
	const std::set<StatsType> m_OUTDOOR_STATS = {
		StatsType::Humidity, 
		StatsType::Pressure, 
		StatsType::Temperature, 
		StatsType::WindDirection, 
		StatsType::WindSpeed,
	};
	std::map<CWeatherData::WeatherDataType, std::map<StatsType, Stats>> m_statistics;
	WindStats m_windStats;
};