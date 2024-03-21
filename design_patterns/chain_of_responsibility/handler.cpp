#include "handler.h"
#include <stdexcept>


std::string Handler::handle() {
    bool success = false;
    if (params_!=nullptr) {
        std::cout << "a: " << params_->a << ", b: " << params_->b << std::endl;
    } else {
        throw std::invalid_argument("invalid argument: params_ is null");
    }
    success = this->doHandle();
    if (success && this->next_!=nullptr) {
        return this->next_->handle();
    }
    return "failed";
}