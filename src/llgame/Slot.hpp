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
    Item addItem(Item newItem);
    Item setItem(Item newItem);

    Item operator=(Item newItem);

protected:
    virtual bool canBePlaced(Item newItem);

    Item item;
};

//-------------------------------------

template<typename T>
auto Slot<T>::getItem() const -> const Item
{
    return this->item;
}

template<typename T>
auto Slot<T>::addItem(Item newItem) -> Item
{
    if(this->item) {
        return this->item->transferFrom(newItem);
    }
    if(!canBePlaced(newItem)) return newItem;
    this->item = newItem;
    return {};
}

template<typename T>
bool Slot<T>::canBePlaced(Item newItem)
{
    return true;
}

template<typename T>
auto Slot<T>::setItem(Item newItem) -> Item
{
    if(this->item == newItem) return {};
    this->item.swap(newItem);
    return newItem;
}

template<typename T>
auto Slot<T>::operator=(Item newItem) -> Item
{
    return setItem(newItem);
}

} // namespace llgame
