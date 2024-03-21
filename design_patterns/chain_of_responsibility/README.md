# 程序运行
1. 使用根目录下的 docker 镜像，将代码拷贝到容器内，并且进入容器本目录下
2. 执行下面指令
```shell
g++ *.cpp -o main --std=c++11
./main
```
# 代码简介
整体实现就是一个责任链模式
## Handler
handler.h 和 handler.cpp 定义了任务的执行体，有一个虚基类 `Handler` 和三个派生类 `TestHandler`、`ZjqHandler`、`CjhHandler`。
- `Handler` 的实现比较简单，主要执行体是 `handle`，内部会调用 `doHandle` 函数来完成工作，`doHandle` 的结果决定了这个任务链是否继续往下执行
- `SharedHandlerParams` 这个是一个参数类，用来传递各个过程的中间值。这里使用 `static`，是想做一个共享单元来用的，这样就不用在创建 `handler` 实例的时候，每个 `handler` 都要做一次 `setParams` 了。但这样做，抛弃了这个类并行的可能性，写的时候就是为了简单，有其他的解决方案。
这里菜过的坑
- 两个 `set` 函数最开始用的 `next_=std::make_shared<Handler>(next);` 这种，但是 `Handler` 是一个虚基类，无法通过编译
- `static` 定义的类成员，要显示初始化一下
##  HandlerChain
`handler_chain.h` 定义了 `HandlerChain` 的实现，这里用了一个模版来做，万一可以对 `Handler` 做替换呢
这里菜过的坑：
- 模版元编程要实现在 .h 文件里面， `class` 外部的实现要 `HandlerChain<T>` （最开始写成了 `HandlerChain`）
- `addHandler` 最后的 `tail_ = tail_->getNextHandler();` 这里，最开始写的是 `tail_ = std::shared_ptr<T>(handler)`，会 Segmentation fault。
## main
`main` 函数提供了两个 test function，`test1` 写的时候，没有 `HandlerChain`，可以看到，想要初始化整个责任链，流程比较麻烦；`test2` 使用的 `HandlerChain`，整体使用流程就更简单一些
