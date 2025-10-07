#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <memory>

#include "Components.hpp"

using std::string;
using std::shared_ptr;

class Entity {
    public:
        void destroy();
        bool isActive();
        const string &tag();
        size_t id();
        // components
        shared_ptr<CTransform> cTransform;
        shared_ptr<CShape> cShape;
        shared_ptr<CCollision> cCollision;
        shared_ptr<CInput> cInput;
        shared_ptr<CScore> cScore;
        shared_ptr<CLifeSpan> cLifeSpan;
    private:
        string m_tag = "default";
        bool m_active;
        size_t m_id;
};

#endif // ENTITY_HPP