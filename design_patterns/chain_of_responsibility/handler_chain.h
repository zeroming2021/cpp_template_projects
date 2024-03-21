#ifndef HANDLER_CHAIN_H
#define HANDLER_CHAIN_H
#include "handler.h"
// using T=Handler;
template<typename T>
class HandlerChain {
    public:
    HandlerChain() : head_(nullptr), tail_(nullptr) {}
    void addHandler(T* handler);
    void handle() {head_->handle();}

    private:
    std::shared_ptr<T> head_;
    std::shared_ptr<T> tail_;

};

template<typename T>
void HandlerChain<T>::addHandler(T* handler) {
    handler->setNextHandler(nullptr);
    if (head_ == nullptr) {
        head_ = std::shared_ptr<T>(handler);
        tail_ = head_;
        return;
    }
    tail_->setNextHandler(handler);
    tail_ = tail_->getNextHandler();
}


#endif  // HANDLER_CHAIN_H