#pragma once

#include "Fly/FlyBehavior.h"
#include "Quack/QuackBehavior.h"
#include "Dance/DanceBehavior.h"

#include <iostream>

class Duck
{
public:
	Duck(const FlyStrategy& flyBehavior,
		const QuackStrategy& quackBehavior,
		const DanceStrategy& danceBehavior)
		: m_flyBehavior(flyBehavior)
		, m_quackBehavior(quackBehavior)
		, m_danceBehavior(danceBehavior)
	{
	}

	void Quack()
	{
		m_quackBehavior();
	}

	void Swim()
	{
		std::cout << "I'm swimming" << std::endl;
	}

	void Fly()
	{
		m_flyBehavior();
	}

	virtual void Dance()
	{
		m_danceBehavior();
	}

	void SetFlyBehavior(const FlyStrategy& flyBehavior)
	{
		m_flyBehavior = flyBehavior;
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyStrategy m_flyBehavior;
	QuackStrategy m_quackBehavior;
	DanceStrategy m_danceBehavior;
};