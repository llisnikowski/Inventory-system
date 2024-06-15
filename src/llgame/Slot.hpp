#pragma once
#include <vector>
#include <memory>

namespace llgame
{

template<typename T>
class Slot
{
public:
    using Item = std::shared_ptr<T>;

    virtual ~Slot() = default;

    const Item getItem() const;
    bool addItem(Item item);
    Item setItem(Item newItem);

    Item operator=(Item item);

protected:
    virtual bool canBePlaced(Item item);

    Item item;
};

//-------------------------------------

template<typename T>
auto Slot<T>::getItem() const -> const Item
{
    return item;
}

template<typename T>
bool Slot<T>::addItem(Item item)
{
    if(this->item) {
        return this->item->transferFrom(item);
    }
    if(!canBePlaced(item)) return false;
    this->item = item;
    return true;
}

template<typename T>
bool Slot<T>::canBePlaced(Item item)
{
    return true;
}

template<typename T>
auto Slot<T>::setItem(Item newItem) -> Item
{
    this->item.swap(newItem);
    return newItem;
}

template<typename T>
auto Slot<T>::operator=(Item item) -> Item
{
    return setItem(item);
}

} // namespace llgame
