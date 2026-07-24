#pragma once
#include <vector>
using namespace std;

template <typename I>
class Inventory 
{
public:
	void Add(int id, int count)
	{
		for (auto& item : items)
		{
			if (item.ID == id)
			{
				item.count += count;
				return;
			}
		}
		items.push_back(I{id, count });
	}
	bool Remove(int id, int count)
	{
		for (auto item = items.begin(); item != items.end(); ++item)
		{
			if (item->ID == id)
			{
				if (item->count < count)
					return false;

				item->count -= count;
				if (item->count == 0)
				{
					items.erase(item);
				}
				return true;
			}
		}
		return false;
	}
	const vector<I>& ViewInventory() const
	{
		return items;
	}
private: 
	vector<I> items;
}; 