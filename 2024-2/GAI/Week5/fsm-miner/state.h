#pragma once

template <typename T /* extends GameEntityBase */>
class StateBase {
  public:
    virtual ~StateBase() = default;
    virtual void enter(T* entity) = 0;
    virtual void execute(T* entity) = 0;
    virtual void exit(T* entity) = 0;
};
