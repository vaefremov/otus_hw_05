#pragma once
#include <vector>
#include <map>
#include <list>
#include <memory>
#include <algorithm>
#include "shapes.h"

namespace OTUS
{

class IObserver 
{
    public:
    virtual ~IObserver() = default;
    virtual void update() = 0;

};

class IObservable 
{
    public:
    virtual ~IObservable() = default;
    virtual void subscribe(std::shared_ptr<IObserver> const&) = 0;
};


class BaseObservable : public IObservable {
public:
    void subscribe(const std::shared_ptr<IObserver>& obs) override {
        m_subscribers.emplace_back(obs);
    }

    void notify() {
        auto iter = std::begin(m_subscribers);
        while(iter != std::end(m_subscribers)) {
            auto ptr = iter->lock();
            if (ptr) {
                ptr->update();
                ++iter;
            } else {
                m_subscribers.erase(iter++);
            }
        }
    }
private:
    std::list<std::weak_ptr<IObserver>> m_subscribers;
};

using ModelID = BaseShape const*;

class Model: public BaseObservable
{
    public:
    Model() = default;
    ~Model() = default;

    ModelID createPoint(DPoint<> const& pt)
    {
        return createShape<Point>(pt);
    }

    ModelID createLine(DPoint<> const& start, DPoint<> const& end)
    {
        return createShape<Line>(start, end);
    }

    template<typename S, typename... Args>
    ModelID createShape(Args&&... args)
    {
        auto pt_ptr = std::make_unique<S>(std::forward<Args>(args)...);
        auto id = pt_ptr.get();
        m_elements.emplace_back(std::move(pt_ptr));
        notify();
        return id;
    }
    
    void setColourById(ModelID id, Colour c)
    {
        auto shp = findByID(id);
        shp->setColour(c);
        notify();
    }

    void deleteByID(ModelID id)
    {
        m_elements.remove_if([id](auto& e){return  e.get() == id;});
        notify();
    }

    void walk(IDrawVisitor *visitor)
    {
        for(auto& e: m_elements)
        {
            e->accept(visitor);
        }
    }
    /**
     *  Find all the IDs of the objects that are designated by the given point.
     * 
     * Currently, the collision occurs of the coordinates of an object (central point)
     * are near the point specified by the parameter \param pt.
     */
    std::vector<ModelID> findCollisions(DPoint<> const& pt);

    /**
     * Return size of the model (i.e. the total number of shapes mentionned in the model).
     */ 
    size_t size()
    {
        return m_elements.size();
    }

    private:
    std::list<std::unique_ptr<BaseShape>> m_elements;
    BaseShape* findByID(ModelID id);

};


}