# 📦 PEA_CAR

> 基于 ROS 的自动收割与剥豆小车，用于豌豆苗的收割与豆荚分离
> 目前，已经实现仿真环境的小车键盘运动控制，slam建图导航功能，主要用于自己学习，后续还会基于此小车开发经历展开更多测试研究。

--- 
> 演示视频链接：https://www.bilibili.com/video/BV1sbLwzKE68/?spm_id_from=333.1387.list.card_archive.click&vd_source=6334dfbde5934e51fd459206126b7fd1

---
## 🧠 技术栈（Tech Stack）

- ROS
- STM32（DJI RoboMaster 开发板C板）
- Gazebo + RViz 仿真
- URDF / Xacro 模型
- C++ / Python 节点开发
- DBus 遥控器协议
- SolidWorks（机械建模）

---

## 🗂️ 项目结构与文件说明（Project Structure & File Explanation）

bash
ros_pea_car/
- ├── config/                 # 参数配置文件（YAML）
- ├── launch/                 # 启动文件（.launch），用于一键启动多个ROS节点
- ├── map/                    # 存放的地图文件
- ├── meshes/                 # 机器人模型的三维几何文件（.stl）
- ├── param/                  # 路径规划配置参数文件
- ├── src/                    # C++ 节点源码
- ├── urdf/                   # 机器人模型（.urdf / .xacro），用于Gazebo仿真
- ├── worlds/                 # gazebo仿真环境
- ├── CMakeLists.txt          # 编译配置
- ├── package.xml             # ROS 包描述文件
- └── README.md               # 项目说明文档



### config 文件夹
*joint_names_pea_car.yaml* 小车控制器配置文件

### launch 文件夹  
*display.launch* 用于rviz中控制测试  
*gazebo.launch* 用于gazebo中仿真测试  
上述两者可同时运行使用  

*no_control_gazebo.launch* 与 *no_control_rviz.launch* 为solidworks导出自动生成文件，用于测试模型导入的正确性  

