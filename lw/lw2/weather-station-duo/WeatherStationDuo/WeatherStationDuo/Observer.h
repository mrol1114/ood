#pragma once

#include <iostream>
#include <set>
#include <unordered_map>
#include <map>
#include <functional>

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& subject) = 0;
	virtual ~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, unsigned int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

template <typename T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

private:
	struct ObserverWithPriority
	{
		ObserverWithPriority(ObserverType* observer, unsigned int priority)
			: m_observer(observer)
			, m_priority(priority)
		{
		}

		bool operator<(const ObserverWithPriority& other) const
		{
			return m_priority > other.m_priority;
		}

		ObserverType* m_observer;
		unsigned int m_priority;
	};

public:
	void RegisterObserver(ObserverType& observer, unsigned int priority) override
	{
		if (m_observerToPriority.contains(&observer))
		{
			throw std::runtime_error("Observer already registered!");
		}
		else
		{
			m_observers.insert({ &observer, priority });
			m_observerToPriority[&observer] = priority;
		}
	}

	void NotifyObservers() override
	{
		auto subject = GetSubject();

		for (auto& observerContainer : m_observers)
		{
			observerContainer.m_observer->Update(*subject);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		if (!m_observerToPriority.contains(&observer))
		{
			throw std::runtime_error("Can not remove observer which is not registered!");
		}
		else
		{
			m_observers.erase({ &observer, m_observerToPriority.at(&observer) });
			m_observerToPriority.erase(&observer);
		}
	}

protected:
	virtual const T* GetSubject() const = 0;

private:
	std::multiset<ObserverWithPriority> m_observers;
	std::map<ObserverType*, unsigned int> m_observerToPriority;
};