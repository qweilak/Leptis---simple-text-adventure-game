#include "container.h"
#include "constants.h"

Container::Container()
{
}


Container::~Container()
{
}

void Container::ShowInRoom(const short lat, const short lon)
{
	if ((_myLatitude == lat) && (_myLongitude == lon) && (_state== 'g'))
		printf(Show_Item(_desc.c_str()));
}

void Container::ToInventory(const short lat, const short lon)
{
	if ((_myLatitude == lat) && (_myLongitude == lon) && (_state == 'g'))
	{
		_state = 's';
		printf(Pick(BAG));
	}else
		printf(Not_found(BAG));
}

Item::Node* Container::GetFromContainer(std::string obj)
{
	if (ilist.Size() <= 0)
		return nullptr;

	return ilist.ReturnNode(obj);

}

void Container::DropItem(const short lat, const short lon)
{
	if (_state == 's')
	{
		_state = 'g';
		_myLatitude = lat;
		_myLongitude= lon;
		printf(Drop_Item(BAG));
	}
	else
		printf(NO_BAG);
}
