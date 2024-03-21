#ifndef HANDLER_H
#define HANDLER_H
#include <memory>
#include <string>
#include <iostream>



struct SharedHandlerParams {
  int a;
  int b;
  ~SharedHandlerParams() {
    std::cout << "~SharedHandlerParams" << std::endl;
  }
};

class Handler {
 public:
  Handler() : next_(nullptr) {};
  Handler(Handler* next) : next_(next){};
  virtual ~Handler() {
    std::cout << "~Handler" << std::endl;
  }
  std::shared_ptr<Handler> getNextHandler() const { return next_; }
  void setNextHandler(Handler* next) { next_ = std::shared_ptr<Handler>(next); }
  static void setParams(SharedHandlerParams *param) {params_ = std::shared_ptr<SharedHandlerParams>(param);}
  static SharedHandlerParams* getSharedHandlerParams() {return params_.get();}
  std::string handle();

 private:
  std::shared_ptr<Handler> next_;
  virtual bool doHandle() = 0;
  static std::shared_ptr<SharedHandlerParams> params_;
};



class TestHandler : public Handler {
  public:
  bool doHandle() override {
    std::cout << "TestHandler" << std::endl;
    if (getSharedHandlerParams()!=nullptr) {
      getSharedHandlerParams()->a = 6666;
    } 
    return true;
  };
};

class ZjqHandler : public Handler {
  public:
    bool doHandle() override {
    std::cout << "ZjqHandler" << std::endl;
    if (getSharedHandlerParams()!=nullptr) {
      getSharedHandlerParams()->b = 999;
    }
    return true;
  };
};

class CjhHandler : public Handler {
  public:
    bool doHandle() override {
    std::cout << "CjhHandler" << std::endl;
    return true;
  };
};

#endif  // HANDLER_H
