#define CATCH_CONFIG_MAIN
#include "../../../../../lib/catch.hpp"
#include "../WeatherStationDuo/WeatherData.h"

#include <vector>
#include <string>

class CMock : public IObserver<CWeatherData>
{
public:
	CMock(std::vector<std::string>* vector)
		: m_vector(vector)
	{
	}

private:
	void Update(CWeatherData const& weatherData) override
	{
		if (weatherData.GetType() == CWeatherData::WeatherDataType::Indoor)
		{
			m_vector->push_back("1");
		}
		if (weatherData.GetType() == CWeatherData::WeatherDataType::Outdoor)
		{
			m_vector->push_back("2");
		}
	}

	std::vector<std::string>* m_vector;
};

SCENARIO("watching for 2 observable")
{
	GIVEN("1 mockObserver and 2 observable")
	{
		CIndoorWeatherData indoor;
		COutsideWeatherData outside;

		std::vector<std::string> vector;

		CMock observer(&vector);

		indoor.RegisterObserver(observer, 1);
		outside.RegisterObserver(observer, 1);

		indoor.NotifyObservers();
		outside.NotifyObservers();

		REQUIRE(vector.size() == 2);
		REQUIRE(vector[0] == "1");
		REQUIRE(vector[1] == "2");
	}
}