#pragma once

#include "Fly/FlyBehaviorContext.h"
#include "Quack/QuackBehaviorContext.h"
#include "Dance/DanceBehaviorContext.h"

#include <iostream>
#include <memory>

class Duck
{
public:
	Duck(const FlyStrategy& flyBehavior,
		const QuackStrategy& quackBehavior,
		const DanceStrategy& danceBehavior)
	{
		m_flyContext.SetStrategy(flyBehavior);
		m_quackContext.SetStrategy(quackBehavior);
		m_danceContext.SetStrategy(danceBehavior);
	}

	void Quack()
	{
		m_quackContext.PerformOperation();
	}

	void Swim()
	{
		std::cout << "I'm swimming" << std::endl;
	}

	void Fly()
	{
		m_flyContext.PerformOperation();
	}

	virtual void Dance()
	{
		m_danceContext.PerformOperation();
	}

	void SetFlyBehavior(const FlyStrategy& flyBehavior)
	{
		m_flyContext.SetStrategy(flyBehavior);
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyBehaviorContext m_flyContext;
	QuackBehaviorContext m_quackContext;
	DanceBehaviorContext m_danceContext;
};