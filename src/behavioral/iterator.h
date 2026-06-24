#pragma once
// 文件: src/behavioral/iterator.h
// 说明: 迭代器模式示例，展示顺序访问聚合对象元素
// 建议: 模板类适合教学，生产项目可考虑使用标准库迭代器。

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace design_patterns::behavioral::iterator {

/**
 * @brief 迭代器接口
 *
 * 定义迭代器的通用接口。
 */
template<typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    /**
     * @brief 是否有下一个元素
     * @return 是否有下一个元素
     */
    virtual bool hasNext() const = 0;
    /**
     * @brief 获取下一个元素
     * @return 下一个元素
     */
    virtual T next() = 0;
    /**
     * @brief 获取当前元素
     * @return 当前元素
     */
    virtual T currentItem() const = 0;
    /**
     * @brief 重置迭代器
     */
    virtual void reset() = 0;
};

/**
 * @brief 聚合接口
 *
 * 定义聚合对象的通用接口。
 */
template<typename T>
class Aggregate {
public:
    virtual ~Aggregate() = default;
    /**
     * @brief 创建迭代器
     * @return 迭代器对象
     */
    virtual std::unique_ptr<Iterator<T>> createIterator() const = 0;
    /**
     * @brief 获取大小
     * @return 元素数量
     */
    virtual size_t size() const = 0;
    /**
     * @brief 获取指定索引的元素
     * @param index 索引
     * @return 指定索引的元素
     */
    virtual T get(size_t index) const = 0;
};

/**
 * @brief 具体迭代器
 *
 * 顺序遍历聚合对象。
 */
template<typename T>
class ConcreteIterator : public Iterator<T> {
public:
    explicit ConcreteIterator(const Aggregate<T>& aggregate)
        : aggregate_(aggregate), currentIndex_(0) {
        std::cout << "[具体迭代器] 创建" << std::endl;
    }

    bool hasNext() const override {
        return currentIndex_ < aggregate_.size();
    }

    T next() override {
        if (hasNext()) {
            return aggregate_.get(currentIndex_++);
        }
        throw std::out_of_range("没有更多元素");
    }

    T currentItem() const override {
        return aggregate_.get(currentIndex_);
    }

    void reset() override {
        currentIndex_ = 0;
        std::cout << "[具体迭代器] 重置到开始" << std::endl;
    }

private:
    const Aggregate<T>& aggregate_;
    size_t currentIndex_;
};

/**
 * @brief 反向迭代器
 *
 * 反向遍历聚合对象。
 */
template<typename T>
class ReverseIterator : public Iterator<T> {
public:
    explicit ReverseIterator(const Aggregate<T>& aggregate)
        : aggregate_(aggregate), currentIndex_(aggregate.size() - 1) {
        std::cout << "[反向迭代器] 创建" << std::endl;
    }

    bool hasNext() const override {
        return currentIndex_ < aggregate_.size();
    }

    T next() override {
        if (hasNext()) {
            return aggregate_.get(currentIndex_--);
        }
        throw std::out_of_range("没有更多元素");
    }

    T currentItem() const override {
        return aggregate_.get(currentIndex_);
    }

    void reset() override {
        currentIndex_ = aggregate_.size() - 1;
        std::cout << "[反向迭代器] 重置到末尾" << std::endl;
    }

private:
    const Aggregate<T>& aggregate_;
    size_t currentIndex_;
};

/**
 * @brief 列表聚合
 *
 * 使用向量存储元素的聚合对象。
 */
template<typename T>
class ListAggregate : public Aggregate<T> {
public:
    ListAggregate() {
        std::cout << "[列表聚合] 创建" << std::endl;
    }

    /**
     * @brief 添加元素
     * @param item 元素
     */
    void add(const T& item) {
        items_.push_back(item);
        std::cout << "[列表聚合] 添加: " << item << std::endl;
    }

    std::unique_ptr<Iterator<T>> createIterator() const override {
        return std::make_unique<ConcreteIterator<T>>(*this);
    }

    /**
     * @brief 创建反向迭代器
     * @return 反向迭代器
     */
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
void iterator_demo();

}
