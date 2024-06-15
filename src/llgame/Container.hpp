#pragma once
#include <vector>

namespace llgame
{

template<typename T>
class Container
{
public:
    using Slots                  = std::vector<T>;
    using iterator               = typename Slots::iterator;
    using const_iterator         = typename Slots::const_iterator;
    using reverse_iterator       = typename Slots::reverse_iterator;
    using const_reverse_iterator = typename Slots::const_reverse_iterator;

    explicit Container(std::size_t size);

    template<typename It>
    auto setItem(
    std::size_t x, It it) -> decltype(std::declval<T>().setItem(it));
    T& getSlot(std::size_t x);
    const T& getSlot(std::size_t x) const;

    Slots& getSlots() { return slots; }
    const Slots& getSlots() const { return slots; }

    std::size_t size() const { return slots.size(); }

    // Iterators
    iterator begin() { return slots.begin(); }
    const_iterator begin() const { return slots.begin(); }
    const_iterator cbegin() const { return slots.cbegin(); }
    iterator end() { return slots.end(); }
    const_iterator end() const { return slots.end(); }
    const_iterator cend() const { return slots.cend(); }
    // Reverse iterator
    reverse_iterator rbegin() { return slots.rbegin(); }
    const_reverse_iterator rbegin() const { return slots.rbegin(); }
    const_reverse_iterator crbegin() const { return slots.crbegin(); }
    reverse_iterator rend() { return slots.rend(); }
    const_reverse_iterator rend() const { return slots.rend(); }
    const_reverse_iterator crend() const { return slots.crend(); }

private:
    Slots slots;
};

//-------------------------------------


template<typename T>
Container<T>::Container(std::size_t size)
: slots(size)
{}

template<typename T>
template<typename It>
auto Container<T>::setItem(
std::size_t x, It it) -> decltype(std::declval<T>().setItem(it))
{
    if(x >= slots.size()) return it;
    return slots[x].setItem(it);
}

template<typename T>
auto Container<T>::getSlot(std::size_t x) -> T&
{
    return slots.at(x);
}

template<typename T>
auto Container<T>::getSlot(std::size_t x) const -> const T&
{
    return slots.at(x);
}


} // namespace llgame
