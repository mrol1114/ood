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
			if (observer == other.observer)
			{
				return type < other.type;
			}

			return observer < other.observer;
		}

		ObserverType* observer;
		EventType type;
	};

	using InsertIterator = std::multiset<ObserverElement>::iterator;

public:
	void RegisterObserver(ObserverType& observer, unsigned int priority, EventType type)override
	{
		if (m_observerToPosition.contains({ &observer, type }))
		{
			throw std::runtime_error("Observer with given type already registered!");
		}
		else
		{
			ObserverElement observerElement(&observer, priority, type);
			ObserverElementKey observerKey(&observer, type);

			auto insertIterator = m_observers.insert(m_observers.end(), observerElement);
			try
			{
				m_observerToPosition[observerKey] = insertIterator;
			}
			catch (std::exception& ex)
			{
				m_observers.erase(insertIterator);
				throw ex;
			}
		}
	}

	void NotifyObservers()override
	{
		auto observers = m_observers;
		for (auto& observerContainer : observers)
		{
			observerContainer.observer->Update(GetChangedData(observerContainer.type), 
				observerContainer.type);
		}
	}
	// добавить метод дл€ отписки от событи€ removeObserver удал€ет всех
	void RemoveObserver(ObserverType& observer, EventType type)override
	{
		ObserverElementKey observerKey(&observer, type);
		if (!m_observerToPosition.contains(observerKey))
		{
			throw std::runtime_error("Can not remove observer which is not registered!");
		}
		else
		{
			InsertIterator& it = m_observerToPosition.at(observerKey);
			m_observers.erase(it);
			m_observerToPosition.erase(observerKey);
		}
	}

protected:
	virtual Data GetChangedData(EventType type)const = 0;

private:
	std::multiset<ObserverElement> m_observers;
	std::map<ObserverElementKey, InsertIterator> m_observerToPosition;
};