# c语言课程设计 华中科技大学人工智能与自动化学院 2025.4.25验收A-通过
## 一.前言：
### 1.选题介绍：农田无人机喷洒农药模拟系统
  	主要功能说明：利用无人机进行农作物生长监测，针对不同病害进行农药配制，对农药喷洒路径进行规划，模拟无人机喷洒过程等功能。
### 2.编写背景：
  	在当下科技的逐步发展，人们已经不满足于先前的机械化农业，即使用各种机械化设备配合人力进行工作，这样并没有真正的解放劳动力，再加上农村的人员外流，以及当下人们的愿景逐渐趋于可以采取一种完全解放劳动力的种植方式，这推动了自动化行业的发展，将自动化技术和智能技术应用于种植当中，可以智能监测农田的生长情况，并且针对不同的病害进行处理，同时它可以克服地形和气候对人的影响，大大提高劳作的灵活程度，从而提高产量。但并非所有农民都明白如何去对无人机进行喷洒规划，也不明白怎样的飞行是效率最高，工作时间最短，得到的产率最大
  	基于这些问题，编者编写了这个农田无人机喷洒农药模拟系统，旨在帮助更多的农民用户在图形化的界面了解自己农田可能出现的问题，了解如何对虫害进行更快处理，从而提高产量。我们欢迎所有希望采用全自动技术进行劳作的劳动者们，希望通过此项技术可以模拟出真实环境下无人机喷洒的实际演示，来让劳动者们得到更高效的生产方式，便宜自身。
### 3.编写目的：
  	通过“无人机喷洒农药模拟系统”，我们可以通过图形化的页面让用户自由绘制自己的农田，或者将农田分块进行处理，来达到更加灵活的规划，在此同时我们支持不同的无人机型号，也具备各种灵活的规划，针对这一项目，我们编写了这项报告，希望 从项目概述，功能分析，代码实现以及一些核心算法解释这些方面来进行解答，旨在让用户通过阅读本篇报告来了解整个项目的原理和尽快熟练使用整个程序。
### 4.参考资料：
	1.周纯杰，何顶新等. 程序设计教程—用C/C++语言编程. 北京: 机械工业出版社, 2016
	2.王士元. C高级实用程序设计. 北京: 清华大学出版社. 1996
### 5.食用说明：
 	1.将文件库中h.zip、c.zip、hzk.zip下载并解压，内部文件分别为全部.h文件、全部.c文件和汉字库。将HZK文件夹和全部.c、.h单个文件放在同一个SOURCE文件夹中。
  	2.接下来设置文件路径。
   
## 二.任务概述：
### 1.需求分析：
	用户可以进入一个农田数据管理的界面，产生像素风格界面的沉浸感。
	用户可以在简易图形的引导与安排下，在拟合现实的情况下（时间流动等），自行安排对农田状态和无人机飞控的部署规划（如在哪块地种什么，在模拟时获得怎样的预期效果）。
  	用户在使用本系统时可以获得挑战性、多样性（如农田虫害的挑战，合理规划无人机性能和飞行轨迹）。 
  	用户使用本系统时要实现对农田不同时段的模拟，如天气变化，虫害发生，飞行规划，时间推移等。 
  	用户可以在管理农田中得到责任感、成就感、满足感，同时系统实现退出展示动画（退出致谢）。
### 2.可行性分析：
	通过新的画图函数实现像素风格；
	通过新的绘制图片，实现简单易懂的图像绘制；
	通过数据记录在.dat文件中进行数据读取与写入；
	通过主界面集成不同界面，实现界面跳转；
	通过手动规划和自动规划两方面进行飞控模拟；
### 3.编写规范：
  	1.注释：对于代码，我们尽可能多的加入了注释，有利于使用者了解代码工作原理（不计入工作量）；
  	2.函数命名根据其具体功能及页面进行命名；

## 三.运行环境与配置：
### 1.硬件接口：
	处理器：Intel Pentium 166 MX 或以上。
  	硬盘：空间 500MB 以上。
  	屏幕适配器：VGA 接口。
  	系统运行内存：要求 32MB 以上。
### 2.软件接口：
  	开发软件工具：Borland C++ 3.1 For DOS 
  	文字编辑工具：Visual Studio Code、Visual Studio 2022 Preview 
  	数据库：记事本 
  	操作系统：DOS WINDOWS 9X/ME/2000/XP/WINDOWS 7
### 3.控制
  	该系统通过鼠标与键盘实现对界面的与功能的控制。 
  	1. 在欢迎页面通过点击语言模式实现切换中英文系统。通过点击退出实现退出模拟系统。点击登录进入登陆页面。 
  	2. 在登录注册界面通过鼠标实现输入框、进入按键、点击注册、退出按键的控制。 
  	3. 在主界面内为鼠标模式，单击退出以实现退出系统，单击返回键退回到登陆页面，单击对应按钮进入对应子界面。 
 	4. 用鼠标实现对其余功能，其余按键的点击。

## 四.主要功能：
  	1. 实现注册/登录/切换语言。 
 	2. 第一次进入主界面显示六个模块：退出，无人机，农田，农药，检测，日志。 
  	3. 进入农田界面，点击农田，点击信封获取当前登陆账号农田信息或创造新农田，保存。回到上一级，点击画笔设置农田位置，点击水设置水源位置，点击橡皮进行擦除，保存。回到上一级，点击植物显示三种作物水稻、玉米、甘蔗，点击对应类别，单击田地对应格子进行种植。单击铲子进行删除作物。回到上一级，单击房子，在地图上点击空白土地进行设置。完成任务，退回到homepage。
 	4. 进入无人机界面，单击录入无人机输入名称，输入质量，机翼数，天气和使用时间，单击确认完成录入。单击查看无人机，可以查询到该账号下全部已经录入的无人机。 
  	5. 进入农药界面，单击管理农药，点击以往该账号已经录入的农药信息；回到上一级，单击名称录入新农药名称，喷洒周期和对应虫害种类。 
  	6. 进入监测界面，选择模式（自动/手动）。右上角可自主输入对应时间天数，或者单击向上或向下三角形调整天数。自动模式下，选择无人机数量（一个/多个），选择set，输入对应房子内无人机种类，输入两种农药调配配方；双击start，开始按时间顺序进行自主喷洒农药，自动模式最大模拟天数60天。单击chart，可见田地内各种数据。手动模式下，单击route手动规划路径（不必设置返航路径），完成后单击start开始自主喷洒农药模拟。 
  	7. 进入日志界面，选择要查看的用户名，选择要查看的类别，单击文件名，对于农田界面，可以展示农田具体设置和房子、作物信息；对于无人机，可以显示无人机名称和对应天气；对于农药，可以显示农药名。
  	8. 单击退出，显示退出致谢动画。

## 五.课设感想：
  	尽管有了一个学期的 C 语言基础作为底子，但是实际上根据课题自主设计并编写一 个程序对我们而言也是相当巨大的挑战。因为工程部分的相关内容大部分在上学期的课程中没有系统性的学习，所以课设的最开始我们进度缓慢，基本上是一边摸索着一边缓慢地熟悉软件和相关功能。
	三月底到四月，面对部分功能仍未实现的急迫情况，通过尽力寻找时间和示例代码，这对于我这部分功能的编写很有帮助。感谢c语言程序设计课本对于编写代码的巨大作用，里面的规范代码对我来说作用很大.
	感谢yzk学长对于代码的提供，为我们减少太多太多压力；感谢人工智能2301班组织的学风建设活动，让我和学长进行了深入交流，学习了debug技术；感谢刘导，在南一楼陪我做c课设到凌晨；感谢jzh、lsy、lyx、ghz、wsa、yxy、lhr、ha、bzx、wb、wjf、byh、hkz、lck等同学，我们互帮互助交流想法，解决了诸多难题；感谢AirHust的飞控脚本，为我们提供了真实可信的飞行路线规划算法；最重要的是感谢c语言课程设计的各位老师，您们的付出，指导我们完成了这份课设，为我们的未来提供了宝贵经验。
	不禁想起来光电大楼，我在那里多次通宵。手边放着一瓶可乐，耳机里听着M83的《Midnight City》，坐在灰扑扑的沙发上，抬头时看到了安静的星空，也看到了震撼人心的关山岭晨光。
