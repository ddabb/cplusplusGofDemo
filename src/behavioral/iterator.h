#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace design_patterns::behavioral::iterator {

template<typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual T next() = 0;
    virtual T currentItem() const = 0;
    virtual void reset() = 0;
};

template<typename T>
class Aggregate {
public:
    virtual ~Aggregate() = default;
    virtual std::unique_ptr<Iterator<T>> createIterator() const = 0;
    virtual size_t size() const = 0;
    virtual T get(size_t index) const = 0;
};

template<typename T>
class ConcreteIterator : public Iterator<T> {
public:
    explicit ConcreteIterator(const Aggregate<T>& aggregate)
        : aggregate_(aggregate), currentIndex_(0) {
        std::cout << "[ConcreteIterator] Created" << std::endl;
    }

    bool hasNext() const override {
        return currentIndex_ < aggregate_.size();
    }

    T next() override {
        if (hasNext()) {
            return aggregate_.get(currentIndex_++);
        }
        throw std::out_of_range("No more elements");
    }

    T currentItem() const override {
        return aggregate_.get(currentIndex_);
    }

    void reset() override {
        currentIndex_ = 0;
        std::cout << "[ConcreteIterator] Reset to start" << std::endl;
    }

private:
    const Aggregate<T>& aggregate_;
    size_t currentIndex_;
};

template<typename T>
class ReverseIterator : public Iterator<T> {
public:
    explicit ReverseIterator(const Aggregate<T>& aggregate)
        : aggregate_(aggregate), currentIndex_(aggregate.size() - 1) {
        std::cout << "[ReverseIterator] Created" << std::endl;
    }

    bool hasNext() const override {
        return currentIndex_ < aggregate_.size();
    }

    T next() override {
        if (hasNext()) {
            return aggregate_.get(currentIndex_--);
        }
        throw std::out_of_range("No more elements");
    }

    T currentItem() const override {
        return aggregate_.get(currentIndex_);
    }

    void reset() override {
        currentIndex_ = aggregate_.size() - 1;
        std::cout << "[ReverseIterator] Reset to end" << std::endl;
    }

private:
    const Aggregate<T>& aggregate_;
    size_t currentIndex_;
};

template<typename T>
class ListAggregate : public Aggregate<T> {
public:
    ListAggregate() {
        std::cout << "[ListAggregate] Created" << std::endl;
    }

    void add(const T& item) {
        items_.push_back(item);
        std::cout << "[ListAggregate] Added: " << item << std::endl;
    }

    std::unique_ptr<Iterator<T>> createIterator() const override {
        return std::make_unique<ConcreteIterator<T>>(*this);
    }

    std::unique_ptr<Iterator<T>> createReverseIterator() const {
        return std::make_unique<ReverseIterator<T>>(*this);
    }

    size_t size() const override {
        return items_.size();
    }

    T get(size_t index) const override {
        return items_[index];
    }

private:
    std::vector<T> items_;
};

}

namespace design_patterns::behavioral {

void iterator_demo() {
    std::cout << "\n========== Iterator Pattern Demo ==========" << std::endl;
    std::cout << "[Demo] 迭代器模式核心：顺序访问聚合对象元素，不暴露内部表示\n" << std::endl;

    std::cout << "[Demo] --- Creating List ---" << std::endl;
    iterator::ListAggregate<std::string> list;
    list.add("Apple");
    list.add("Banana");
    list.add("Cherry");
    list.add("Date");
    list.add("Elderberry");

    std::cout << "\n[Demo] --- Forward Iteration ---" << std::endl;
    auto forwardIterator = list.createIterator();
    while (forwardIterator->hasNext()) {
        std::cout << "Element: " << forwardIterator->next() << std::endl;
    }

    std::cout << "\n[Demo] --- Reverse Iteration ---" << std::endl;
    auto reverseIterator = list.createReverseIterator();
    while (reverseIterator->hasNext()) {
        std::cout << "Element: " << reverseIterator->next() << std::endl;
    }

    std::cout << "\n[Demo] --- Integer List ---" << std::endl;
    iterator::ListAggregate<int> intList;
    intList.add(10);
    intList.add(20);
    intList.add(30);
    intList.add(40);
    intList.add(50);

    std::cout << "\n[Demo] --- Iterating Integer List ---" << std::endl;
    auto intIterator = intList.createIterator();
    while (intIterator->hasNext()) {
        std::cout << "Number: " << intIterator->next() << std::endl;
    }

    std::cout << "\n==========================================\n" << std::endl;
}

}
