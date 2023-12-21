### 程序设计基础期末大作业实验报告    

# TANK TRUBULENCE    

### 作者 NEAOZ    

作者能力有限，文档或有纰漏

---

### 摘要    

《动荡坦克》原是是“射击”类游戏的一个flash小游戏，本实验在win32平台，基于C++和ACCLIB，混用了面向对象和面向过程实现了坦克，地图，地图元素，尽可能地对游戏的双人模式进行基本复刻。    

##### 关键词： 坦克动荡；C++;ACCLIB;大一上C语言期末作业    

---

## 0. About Developer
- NEAOZ 负责所有代码部分
- WangQyu 曾写过两个tank_judge函数，明确作业要求后被NEAOZ REWRITE
- PengYtong 绘制`introduction.bmp`和`developer.bmp`,暂且懒得改了
- PengYtong 原本负责开发菜单，由于没有使用ACCLIB，而且平台为x64，遂舍弃
- WangQyu 和 PengYtong 会有自己的程序作业

---

## 1. 游戏介绍    

双人射击游戏，玩家1玩家2可以分别操控绿、蓝两辆坦克，对敌方进行射击，射击出的子弹具有反弹功能。   

玩家1操作 WSAD和SPACE进行上下移动，左右旋转和向前射击    
玩家2操作 ↑↓←→和ENTER进行上下移动，左右旋转和向前射击    

---

## 2. ACCLIB库介绍    
>因为C语言本身是没有图形界面的库，然而初学者又希望能做出带界面的东西来，但做出带界面的程序要学习windows窗体程序，对初学者来说又难，所以就有了ACLLib库(浙江大学编写)。    
>
>ACLLib只是教学目的做的一个函数库，它对Windows的WIn32API做了简单的包装，用相对比较简单的方式可以编写出简单的图形界面程序来。由于是自己做的教学目的的库，今后的实际工作中不可能用到这样的库，这个库有教学和学习的价值。    
>
>[ACLLib现在是以GPL的方式放在github中](https://github.com/wengkai/ACLLib)[1]    

[1] [来源：https://zouzhongliang.com/index.php/2019/03/31/acllib%e5%ba%93%e6%98%af%e4%bb%80%e4%b9%88/](https://zouzhongliang.com/index.php/2019/03/31/acllib%e5%ba%93%e6%98%af%e4%bb%80%e4%b9%88/)   

---

## 3. 系统分析    

### 3.1 功能分析    
- 1. 游戏菜单界面跳转    
- 2. 随机生成连通图并正确显示   
- 3. 坦克交互式移动和边界判定    
- 4. 子弹发射,反弹,与坦克碰撞判定    
- 5. 分数统计    

### 3.2 类关系分析    
- 1. `SolidObject` 实体类    
- 2. `Tank` `public`继承`SolidObject`    
- 3. `Bullet` `public`继承`SolidObject`    
- 4. `WallMap` 地图类    

### 3.3 其中混杂的面向过程    
- 1. `map_create` 由于采取了并查集的算法(通常信竞代码都是面相过程的C++)，遂不创建一个新类   
- 2. 游戏各个界面跳转：受限于`ACCLIB`，在`time_event`中实现    
- 3. 按键触发   

---

## 4. 详细设计及实现   

### 4.1 场景与视窗    
在`Setup`中，实现 窗口初始化 图片加载 键盘鼠标中断使能 定时器使能    

### 4.2 窗口跳转实现    
在`time_event`中，每30ms（实际测试误差严重）跳转界面    
通过判断 `interface_state` 来确定该进入哪一个界面    
其中宏定义了如下界面    

```c++
    #define INTERFACE_GAME_INIT	        0
    #define INTERFACE_GAME_PLAY	        1
    #define INTERFACE_MENU_BEGIN        2
    #define INTERFACE_MENU_PAUSE        3
    #define INTERFACE_MENU_INTRODUCTION 4
    #define INTERFACE_MENU_DEVELPOER    5
```

#### 4.2.2 界面关系解析    

- 自己看代码去吧    

### 4.3 `SolidObject`类实现    

#### 4.3.1成员变量：    

```c++
	int _user;          //玩家（编号）
	ACL_Color _color;	  //颜色
	int _center[2];	    //以画布左上角为原点，SolidObject的中心坐标
	int _angle;	        //水平向右为正,顺时针自加
	int _half_length;	  //长度的1/2
	int _half_width;	  //宽度的1/2
	int _linear_v;      //线速度
	int _angular_v;     //角速度
```

其中采用 `_half_length` `_half_width` 可以方便通过对称快速求出物体的四角坐标    

#### 4.3.2成员函数：  

##### 4.3.2.1 `protected`    

```c++
/**
  * @brief  将center2赋值给center1
  * @param1	center1：赋入
  * @param2	center2：赋出
  * @retval None
  */
void SolidObject::_assign_center(int* center1, const int* center2);

/**
  * @brief  理想情况向前移动_center
  * @param1	new_center:理想情况移动后的值
  * @retval None
  */
void SolidObject::_for_move(int* new_center);

/**
  * @brief  理想情况向后移动_center
  * @param1	new_center:理想情况移动后的值
  * @retval None
  */
void SolidObject::_back_move(int* new_center);

/**
  * @brief  计算右方上角的点（相对_angle = 0)的坐标
  * @param  None
  * @retval 在画布坐标系下的坐标（x，y）
  */
POINT SolidObject::_point_coordinates(int* center, int angle);

/**
  * @brief  根据右方上角的点坐标求出四角坐标
  * @param  右方上角的点坐标
  * @retval	points[4]{x,y} 在画布坐标系下的四角坐标
  */
void SolidObject::_points_symmetric(POINT* points, int* center, int angle);
```

##### 4.3.2.1 `public`    

```c++
int SolidObject::get_angle()

/**
  * @brief  获取四角的坐标
  * @param  None
  * @retval None
  */
void SolidObject::get_points(POINT* points)
```

补充说明：设计之初还存在`SolidObject`的绘制函数，由于`Tank`和`Bullet`的绘制方法完全不同，遂未在此对象中实现    

### 4.4 `Tank`类实现（`public SolidObject`）  

#### 4.4.1成员变量： 

-  `None`    

#### 4.4.2成员函数：  

##### 4.4.2.1 `private`    

```c++
/**
  * @brief  计算坦克炮管的四个角地址
  * @param  point:用于存放炮管四个角位置
  * @retval None
  */
POINT* Tank::_points_cannon(POINT* points);

/**
  * @brief  判断坦克前后移动，并改变_center
  * @param  next_center：理想的下一个位置
  * @retval None
  * @author WangaQingyu
  */
int Tank::_judge_move_crash(int* next_center);

/**
  * @brief  判断坦克旋转，并改变_angle
  * @param  next_angle：理想的下一个旋转位置
  * @retval None
  * @author WangaQingyu
  */
int Tank::_judge_rotate_crash(int next_angle);
```

其中`_judge_move_crash` `_judge_rotate_crash` 仍然存在少量bug    

##### 4.4.2.2 `public`    

```c++
/**
  * @brief  清除上一次坦克位置显示
  * @param  None
  * @retval None
  */
void Tank::tank_unshow()；

/**
  * @brief  坦克位置显示
  * @param  None
  * @retval None
  */
void Tank::tank_show()；

/**
  * @brief  向前移动
  * @param  None
  * @retval None
  */
void Tank::move_for_per_time()；
/**
  * @brief  向后移动
  * @param  None
  * @retval None
  */
void Tank::move_back_per_time()；

/**
  * @brief  顺时针（clockwise）旋转
  * @param  None
  * @retval None
  */
void Tank::rotate_CW_per_time()；

/**
  * @brief  逆时针（counterclockwise）旋转
  * @param  None
  * @retval None
  */
void Tank::rotate_CCW_per_time()；

/**
  * @brief  随机生成tank的位置,位于每一个地图块的中央
  * @param  my_map : wallmap
  * @retval random_center[2]
  */
static int* Tank::random_coordinate(WallMap my_map)；
/**
  * @brief  随机生成angle(0,90,180,270)
  * @param  None
  * @retval angle
  */
static int Tank::random_angle()；

/**
  * @brief  显示tank分数
  * @param  None
  * @retval None
  */
static void Tank::show_score()；

/**
  * @brief  清除分数
  * @param  None
  * @retval None
  */
static void Tank::clear_score()；
```

- 懒得解释    

### 4.5 `Bullet`类实现（`public SolidObject`）   

#### 4.5.1成员变量：   

```c++
	int _is_use;	//1,using ,0 unused 
	int _survive_time;  //子弹存活时间
```

#### 4.5.2成员函数：   

##### 4.5.2.1 `private`    

```c++
/**
  * @brief  清除上一次的子弹位置显示
  * @param  None
  * @retval None
  */
void Bullet::_bullet_unshow()

/**
  * @brief  判断某一状态tank是否碰撞
  * @param  points：改状态的四个角的坐标
  * @retval 1：crash  2：uncrash
  */
int Tank::_judge_state(POINT* points)；

/**
  * @brief  判断当前位置子弹有无撞墙
  * @param  *center：预设预设子弹的x，y位置
  * @retval 1：UP	2：DOWN	3：LEFT	4：RIGHT
  				-1：TANK1（USER1）	-2：TANK2（USER2）
				0：None
  */
int Bullet::_bullet_state_judge(int* center)；

/**
  * @brief  判断子弹在运动到下一个位置过程中有无撞墙
  * @param1 *pre_center：先前的子弹x,y位置
  * @param2 *next_center：下一次的子弹理论的x,y位置
  * @retval 1：UP	2：DOWN	3：LEFT	4：RIGHT
				-1：TANK1（USER1）	-2：TANK2（USER2）
				0：None
  */
int Bullet::_bullet_judge(int* pre_center, int* next_center)	

/**
  * @brief  根据judge值移动子弹_center和反射_angle
  * @param1 judge：1：UP	2：DOWN	3：LEFT	4：RIGHT
				   	-1：TANK1（USER1）	-2：TANK2（USER2）
				   	0：None
  * @param2 *pre_center：先前的子弹x,y位置
  * @param3 *next_center：下一次的子弹理论的x,y位置
  * @retval 1：UP	2：DOWN	3：LEFT	4：RIGHT
				-1：TANK1（USER1）	-2：TANK2（USER2）
				0：None
  */
void Bullet::_bullet_move(int judge, int* pre_center, int* next_center)

/**
  * @brief  针对子弹刚发射时的小bug修复（还存在其他bug，称之为小彩蛋或者“有意为之”的逃课技巧）
  * @param  None
  * @retval None
  */
void Bullet::_first_shoot_anti_bug()
```

- 懒得解释    

##### 4.5.2.2 `public`    

```c++
/**
  * @brief  子弹发射时的启用初始化
  * @param1 orient：tank朝向
  * @param2 *tank_points：tank四角坐标
  * @retval None
  */
void Bullet::init(int orient, POINT* tank_points)

/**
  * @brief  游戏结束时子弹的弃用
  * @param  None
  * @retval None
  */
void Bullet::clear()

/**
  * @brief  子弹是否活着
  * @param  None
  * @retval 1：活着	0：死了
  */
bool Bullet::is_exist()

/**
  * @brief  子弹每一次的移动，并显示子弹在window上
  * @param  None
  * @retval None
  */
int Bullet::pre_time()

/**
  * @brief  子弹位置显示
  * @param  None
  * @retval None
  */
void Bullet::bullet_show()
```

- 懒得解释    

### 4.6 `WallMap`类实现    

#### 4.6.1 成员变量：  

```c++
	int _axis_x;
	int _axis_y;
	int _length;
	int _width;
	int*** wallmap;
```

#### 4.6.2 成员函数：  

##### 4.6.2.1 `private`    

```c++
/**
  * @brief  绘制一个单位block的四边的Wallmap
  * @param  line：0开始
  * @param	column: 0开始
  * @retval None
  */
void WallMap::_wallmap_showoneblock(int line, int column)；

/**
  * @brief  加粗Map的边框，防止Map边框穿角（可以删掉这个看看运行BUG）
  * @param  None
  * @retval None
  */
void WallMap::_wallmap_showframe()；
```

懒得解释    

##### 4.6.2.2 `public`

```c++
int WallMap::get_axis_x()；

int WallMap::get_axis_y()；

int WallMap::get_length()；

int WallMap::get_width()；

/**
  * @brief  绘制Map
  * @param  None
  * @retval None
  */
void WallMap::wallmap_show()；

/**
  * @brief  清空窗口屏幕
  * @param  None
  * @retval None
  */
void WallMap::windows_clear()；
```

- 懒得解释    

### 4.7 `map_create` 随机生成地图    

不想复制了，就用了一点并查集    

会用这两个函数就好    

```c++
/**
  * @brief	并查集基本操作，懒得解释
  * @param1
  * @retval
  */
void map_free(int*** newmap, int length, int width);

/**
  * @brief	生成新的地图
  * @param1	*length：即将随机的地图长度
  * @param2	*width：即将随机的地图宽度
  * @retval	生成的地图指针
  */
int*** map_creating(int* length, int* width);
```

如果闲来无事想要自己去生成地图的话，可以用开发之初的手动生成函数    
`void map_read(int length, int width)；`    
但是用了个全局变量，现在已经被删干净了    

### 4.8 `key_interrupt`   

处理按键和鼠标事件，通过置各个key的标志位，具体做什么在`time_event`中处理    
实际的if语句还要根据菜单在哪个界面进行下一步的判断    

### 4.9 `global_param`    

一些`main.cpp`需要与其他文件共享的全局变量    

---

## 5. 测试    
markdown里面添加图片有点烦，另外程序bug还有点多。。。    

---

## 6. GitHub    

```c++
GNU GENERAL PUBLIC LICENSE
                       Version 3, 29 June 2007

 Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 Everyone is permitted to copy and distribute verbatim copies
 of this license document, but changing it is not allowed.
```

关于分支：几乎所有活都是在`rotate`上干的，最后才合并到`master`上    
对于git的不熟练掌握和项目就是一个人线性开发，几乎没有其他分支    

---

## 6. 几个不足
- 1. git使用超不熟练    
- 2. 对于各个类的实现仍然不是很完整     
- 3. 由于浮点数（cos，sin的不精确性）的限制，暂时没有更好的方法规避，导致边界判断理论正确但实际bug百出    
- 4. `ACCLIB`的功能太蒟蒻了    
- 5. 想要实现的功能太复杂，浪费时间    
- 6. 项目文件管理    
- 7. 文档编写能力    

---

## 7. 以下内容来自网络    

> *大一入学时我是一个对计算机一无所知的小白，装了几十个 G 的 Visual Studio 天天和 OJ 你死我活。凭着高中的数学底子我数学课学得还不错，但在专业课上对竞赛大佬只有仰望。提到编程我只会打开那笨重的 IDE，新建一个我也不知道具体是干啥的命令行项目，然后就是 cin, cout, for 循环，然后 CE, RE, WA 循环。当时的我就处在一种拼命想学好但不知道怎么学，课上认真听讲但题还不会做，课后做作业完全是用时间和它硬耗的痛苦状态。我至今电脑里还存着自己大一上学期计算概论大作业的源代码 —— 一个 1200 行的 C++ 文件，没有头文件、没有类、没有封装、没有 unit test、没有 Makefile、没有 Git，唯一的优点是它确实能跑，缺点是“能跑”的补集。我一度怀疑我是不是不适合学计算机，因为童年对于极客的所有想象，已经被我第一个学期的体验彻底粉碎了*    

---

*Tank Turrbuance Copyleft(C) 2023 NEAOZ in UESTC*