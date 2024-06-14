```
title: Amirkabir University of Technology 1400-2: Advanced Programming Course
tags: 
- c++
- homework
categories: c++
date: 2024-06-14
```

**写在前面**

于[CS自学指南](https://csdiy.wiki)中发现的一个c++课程，来源于 AmirKabir University of Technology。课程的 homework质量不错且有趣味。每个homework都有完备的单元测试。

以下是课程资源:

- 课程仓库地址：https://github.com/courseworks
- 我的实现：https://github.com/kanzakishigure/AP1400-2
- 贴一个实现：https://github.com/Daniel741312/AUT-1400

>- [x] [homework1](./AP1400-2-HW1):实现Matrix 类以及相关函数。
>
>- [x] [homework2](./AP1400-2-HW2):模拟加密货币客户端/服务端执行过程的程序。
>
>- [x] [homework3](./AP1400-2-HW3):实现 Binary Search Tree (BST)。
>
>- [x] [homework4](./AP1400-2-HW4):实现 C++ 中的 SharedPtr 和 UniquePtr 智能指针。
>
>- [x] [homework5](./AP1400-2-HW5):使用继承和多态实现咖啡饮品。
>
>- [ ] [homework6](./AP1400-2-HW6):使用 STL 库解决 4 个问题。
>
>- [ ] [homework7](./AP1400-2-HW7):一个 python 项目。

**配置环境**

课程使用了[Docker](https://www.docker.com/products/docker-desktop)管理环境，每个homework都提供了对应的**Dockerfile**，课程并不需要你编写**Dockerfile**，只需要使用**Dockerfile**创建镜像，并使用镜像启动容器。不了解Docker的可以查看[Docker 10分钟快速入门](https://www.bilibili.com/video/BV1s54y1n7Ev?vd_source=c1a4fe488e28c685f3d2b18671221525)快速了解Docker。

**Debug**

在完成homework中，可能希望在容器中对程序进行调试。为了实现这一目标你需要准备。

- [VSCode](https://code.visualstudio.com/)
- VSCode的[devcontainer](https://github.com/Microsoft/vscode-remote-release.git)扩展
- [Docker](https://www.docker.com/products/docker-desktop)

完成了以上准备了，我们可以在具体的homework目录打开VSCode,并使用<u>Ctrl+Shift+p</u> 中Reopen in Container。后续devcontainer会根据目录下的.devcontainer.json自动配装环境。

<img src=".\resource\devcontainer.gif" style="zoom:67%;" />
