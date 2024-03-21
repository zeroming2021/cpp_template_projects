#include "handler.h"
#include "handler_chain.h"

std::shared_ptr<SharedHandlerParams> Handler::params_ = nullptr;
void test1() {
    Handler *head = new TestHandler();
    SharedHandlerParams *param = new SharedHandlerParams{1,1};
    Handler *next = new ZjqHandler();
    //Handler::setParams(param);
    head->setNextHandler(next);
    next->setNextHandler(new CjhHandler());
    std::string message = head->handle();
    SharedHandlerParams *param1 = new SharedHandlerParams{3,3};
    Handler::setParams(param1);
    // head->handle();
    delete head;
}
void test2() {
    HandlerChain<Handler> handlerChain;
    SharedHandlerParams *param = new SharedHandlerParams{1,1};
    Handler::setParams(param);

    handlerChain.addHandler(new TestHandler());
    handlerChain.addHandler(new ZjqHandler());
    handlerChain.addHandler(new CjhHandler());
    handlerChain.handle();
    
}

int main() {
    test2();
    return 0;
}