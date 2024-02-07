#pragma once

#include <deque>

#include "./IOriginator.h"

template <typename MementoType>
class CHistory
{
public:
	using Originator = IOriginator<MementoType>;

	CHistory(Originator* originator)
		: m_originator(originator)
	{
	}

	void Save()
	{
		if (m_nextMementoIndex < m_mementos.size())
		{
			++m_nextMementoIndex;
			m_mementos.resize(m_nextMementoIndex);
			m_mementos.back() = m_originator->Save();
		}
		else
		{
			m_mementos.emplace_back(nullptr);

			try
			{
				m_mementos.back() = m_originator->Save();
				++m_nextMementoIndex;
				if (m_nextMementoIndex > m_MAX_HISTORY_SIZE)
				{
					delete* m_mementos.begin();
					m_mementos.erase(m_mementos.begin());
					--m_nextMementoIndex;
				}
			}
			catch (...)
			{
				m_mementos.pop_back();
				throw;
			}
		}
	}

	void Undo()
	{
		if (CanUndo())
		{
			auto memento = m_mementos[m_nextMementoIndex - 1];
			m_originator->Restore(memento);
			--m_nextMementoIndex;
		}
	}

	void Redo()
	{
		if (CanRedo())
		{
			auto memento = m_mementos[m_nextMementoIndex];
			m_originator->Restore(memento);
			++m_nextMementoIndex;
		}
	}

	bool CanUndo()
	{
		return m_nextMementoIndex != 0;
	}

	bool CanRedo()
	{
		return m_nextMementoIndex != m_mementos.size();
	}

	~CHistory()
	{
		for (auto m : m_mementos)
		{
			delete m;
		}
	}

private:
	Originator* m_originator;
	std::deque<MementoType*> m_mementos;
	size_t m_nextMementoIndex = 0;

	inline static const size_t m_MAX_HISTORY_SIZE = 10;
};