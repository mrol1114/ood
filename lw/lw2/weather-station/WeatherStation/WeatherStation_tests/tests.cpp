#define CATCH_CONFIG_MAIN
#include "../../../../../lib/catch.hpp"
#include "../Project1/WeatherData.h"

#include <vector>

class CMockDisplay : public IObserver<SWeatherInfo>
{
public:
	CMockDisplay(CWeatherData* observable)
		: m_observable(observable)
	{
	}

private:
	void Update(SWeatherInfo const& data) override
	{
		m_observable->RemoveObserver(*this);
	}

	CWeatherData* m_observable;
};

class CMockInOrder : public IObserver<SWeatherInfo>
{
public:
	CMockInOrder(std::vector<CMockInOrder*>* vector)
		: m_vector(vector)
	{
	}

private:
	void Update(SWeatherInfo const& data) override
	{
		m_vector->push_back(this);
	}

	std::vector<CMockInOrder*>* m_vector;
};

SCENARIO("removing observer while notify")
{
	GIVEN("mock observer")
	{
		CWeatherData wd;

		CMockDisplay display(&wd);

		wd.RegisterObserver(display, 1);
		REQUIRE_NOTHROW(wd.NotifyObservers());
	}
}

SCENARIO("notify in order")
{
	GIVEN("3 mockInOrder observers with weatherData")
	{
		CWeatherData wd;

		std::vector<CMockInOrder*> vector;
		CMockInOrder observer1(&vector);
		CMockInOrder observer2(&vector);
		CMockInOrder observer3(&vector);

		wd.RegisterObserver(observer1, 1);
		wd.RegisterObserver(observer2, 2);
		wd.RegisterObserver(observer3, 1);

		wd.NotifyObservers();

		REQUIRE(vector.size() == 3);
		REQUIRE(vector[0] == &observer2);
		REQUIRE(vector[1] == &observer1);
		REQUIRE(vector[2] == &observer3);
	}
}