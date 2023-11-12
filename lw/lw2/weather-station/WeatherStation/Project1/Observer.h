#pragma once

#include <set>
#include <functional>

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
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

template <class T>
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

		bool operator<(const ObserverWithPriority& other)const
		{
			return m_priority > other.m_priority;
		}

		ObserverType* m_observer;
		unsigned int m_priority;
	};

	using InsertIterator = std::multiset<ObserverWithPriority>::iterator;

public:
	void RegisterObserver(ObserverType& observer, unsigned int priority)override
	{
		if (m_observerToPosition.contains(&observer))
		{
			throw std::runtime_error("Observer already registered!");
		}
		else
		{
			ObserverWithPriority observerWithPriority(&observer, priority);
			auto insertIterator = m_observers.insert(m_observers.end(), observerWithPriority);
			try // неконсистентность данных при исключении, gsl::finally or boost::SCOPE_EXIT
			{
				m_observerToPosition[&observer] = insertIterator;
			}
			catch (std::exception& ex)
			{
				m_observers.erase(insertIterator);
				throw ex;
			}
		}
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();

		auto observers = m_observers;
		for (auto& observerContainer : observers)
		{
			observerContainer.m_observer->Update(data);
		}
	}

	void RemoveObserver(ObserverType& observer)override
	{
		if (!m_observerToPosition.contains(&observer))
		{
			throw std::runtime_error("Can not remove observer which is not registered!");
		}
		else
		{
			// удалит всех с указанным приоритетом
			InsertIterator& it = m_observerToPosition.at(&observer);
			m_observers.erase(it);
			m_observerToPosition.erase(&observer);
		}
	}

protected:
	virtual T GetChangedData()const = 0;

private:
	std::multiset<ObserverWithPriority> m_observers;
	std::map<ObserverType*, InsertIterator> m_observerToPosition;
};