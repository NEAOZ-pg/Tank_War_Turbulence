# 关于menu的个人拙见

---
## 1    学习定时器中断和按键中断

上课讲过 `registerKeyboardEvent` `registerTimerEvent`
不再赘述

---

## 2    NEAOZ的实现方式 
1。 先看按键中断（部分）
    
```c++
void keyevent(int key, int event)
{
	if (event == KEY_DOWN)
	{
		if (key == 0x41)
		{
			std::cout << "A = 1\n";
			key_A = 1;
		}
		else if (key == 0x57)
		{
			std::cout << "W = 1\n";
			key_W = 1;
		}
。。。
```

在按键中断中仅对每个key的flag(`key_W`)进行改变（stm32的书写习惯。。。）
这个是提醒你们在按键检验中就只改flag
花活在下面整

2. 再来看定时器中断（**重点**）

```c++
void timeevent(int timeID)
{
	if (timeID == TimeID_Game)
	{
		if (interface_state == interface_game_init)
		{
			beginPaint();
			map_test.wallmap_show();
			tank0.tank_show();
			endPaint();
			interface_state = interface_game_play;
		}
		else if (interface_state == interface_game_play)
		{
			if (key_A)

			}
		}
	}
}
```

注意其中的 `interface_state == interface_game_init` `interface_state == interface_game_play`

很粗暴地使用 `if` 通过 `interface_state` 判断是哪个界面
具体的 `interface_game_init` `interface_game_play`使用宏定义、
`#define interface_game_init 0`
`#define interface_game_play 1`

在每个界面要干的事情结束，在通过 `if` 判断，改变 `interface_state`(这个必须得做！！)
然后就可以在下一次定时器中断的时候进入下一个页面了。
（相当于`stm32`中`main`函数的`while（1）`循环，只不过这个循环每20ms进去一次）

---

## 3.此文档编辑工具
`maarkdown` 可以看作是超级简单版本的 `latex`
强烈建议学习，去替代该死的word！
30min快速入门
[点我学习](https://markdown.com.cn/)