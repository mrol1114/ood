#pragma once

#define _USE_MATH_DEFINES

#include <climits>
#include <math.h>

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