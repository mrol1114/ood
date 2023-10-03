#pragma once

#include <set>
#include <functional>

template <typename Data, typename EventType>
class IObserver
{
public:
	virtual void Update(Data const& data, EventType type) = 0;
	virtual ~IObserver() = default;
};

template <typename Data, typename EventType>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<Data, EventType>& observer, unsigned int priority, EventType type) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<Data, EventType>& observer, EventType type) = 0;
};

template <typename Data, class EventType>
class CObservable : public IObservable<Data, EventType>
{
public:
	typedef IObserver<double, EventType> ObserverType;

private:
	struct ObserverElement
	{
		ObserverElement(ObserverType* observer, unsigned int priority, EventType type)
			: observer(observer)
			, priority(priority)
			, type(type)
		{
		}

		bool operator<(const ObserverElement& other) const
		{
			return priority < other.priority;
		}

		ObserverType* observer;
		unsigned int priority;
		EventType type;
	};

	struct ObserverElementKey
	{
		ObserverElementKey(ObserverType* observer, EventType type)
			: observer(observer)
			, type(type)
		{
		}

		bool operator<(const ObserverElementKey& other) const
		{
			return type < other.type;
		}

		ObserverType* observer;
		EventType type;
	};

public:
	void RegisterObserver(ObserverType& observer, unsigned int priority, EventType type)override
	{
		if (m_observerToPriority.contains({ &observer, type }))
		{
			throw std::runtime_error("Observer with given type already registered!");
		}
		else
		{
			m_observers.insert({ &observer, priority, type });
			m_observerToPriority[{ &observer, type }] = priority;
		}
	}

	void NotifyObservers()override
	{
		for (auto& observerContainer : m_observers)
		{
			observerContainer.observer->Update(GetChangedData(observerContainer.type), 
				observerContainer.type);
		}
	}

	void RemoveObserver(ObserverType& observer, EventType type)override
	{
		if (!m_observerToPriority.contains({ &observer, type }))
		{
			throw std::runtime_error("Can not remove observer which is not registered!");
		}
		else
		{
			m_observers.erase({ &observer, m_observerToPriority.at({&observer, type}), type });
			m_observerToPriority.erase({ &observer, type });
		}
	}

protected:
	virtual Data GetChangedData(EventType type)const = 0;

private:
	std::multiset<ObserverElement> m_observers;
	std::map<ObserverElementKey, unsigned int> m_observerToPriority;
};