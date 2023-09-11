#pragma once

#include <set>
#include <functional>
#include <queue>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, unsigned int priority) override
	{
		if (!m_isLocked)
		{
			DoRegisterObserver(observer);
		}
		else
		{
			AddCommandToQueue(Command::Register, observer);
		}
	}

	void NotifyObservers() override
	{
		m_isLocked = true;

		T data = GetChangedData();
		for (auto& observer : m_observers)
		{
			observer->Update(data);
		}

		m_isLocked = false;
	}

	void RemoveObserver(ObserverType& observer) override
	{
		if (!m_isLocked)
		{
			DoRemoveObserver(&observer);
		}
		else
		{
			AddCommandToQueue(Command::Remove, observer);
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:

	void AddCommandToQueue(Command command, ObserverType& observer)
	{
		m_lockedCommands.push({ command, observer });
	}

	void ExecuteQueuedCommands()
	{
		while (m_lockedCommands.empty())
		{
			LockedCommand* command = m_lockedCommands.front();

			switch (command->commandType)
			{
			case Command::Register:
				DoRegisterObserver(command->commandType, command->payload);
			case Command::Remove:
				DoRegisterObserver(command->commandType, command->payload);
			}

			m_lockedCommands.pop();
		}
	}

	void DoRemoveObserver(ObserverType& observer)
	{
		m_observers.erase(&observer);
	}

	void DoRegisterObserver(ObserverType& observer)
	{
		m_observers.insert(&observer);
	}

	enum class NeedsLockCommandTypes {
		Register,
		Remove
	};

	struct LockedCommand
	{
		NeedsLockCommandTypes commandType;
		ObserverType& payload;
	};

	std::set<ObserverType*> m_observers;
	std::queue<LockedCommand> m_lockedCommands;
	bool m_isLocked;
};