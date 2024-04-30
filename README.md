# Yfrobot-TTS-Library
YFROBOT TTS module Library for Arduino

![](./assets/YFTTS.jpg)![](./assets/yfrobot_tts.png)


## 相关链接 Links

* 产品购买链接: [YFROBOT商城](https://www.yfrobot.com/)、[YFROBOT淘宝商城](https://yfrobot.taobao.com/).

#### 库使用说明：
调用库：

`#include <YFTTS.h>   // 包含头文件`

创建对象：

UNO 主板：
`YFROBOTTTS YF_TTS(9, 8);  //软串口引脚，RX：D9    TX：D8`

ESP32 主板：
`YFROBOTTTS YF_TTS(16, 17); // 使用 ESP32 的硬件串口2，自定义引脚RX：16    TX：17`

Methods：

初始化，成功则返回模组序列号(String)，否则返回""。

`YF_TTS.getChipSN();`

验证指纹，并返回指纹ID
参数：true，无手指时，LED反馈；false，无手指时，无LED反馈。

`YF_TTS.identify()`

在ID位置注册指纹
参数：注册ID，默认拼接4次（可自定义次数）。

`YF_TTS.enroll(ID, 4);` 
`YF_TTS.enroll(ID, 6);`


删除ID位置的指纹

`YF_TTS.deleteID(ID);`

清空指纹库

`YF_TTS.empty();`

查询当前已注册指纹数量

`YF_TTS.inquiry();`


## 更新日志 Release Note
* V0.0.6    适配ESP32系列主板，测试在ESP32-WROOM-32E。Update Date: 04-15-2024
* V0.0.5    适配ESP32系列主板，测试在ESP32-WROOM-32E。Update Date: 04-11-2024
* V0.0.4    更改library.properties文件。
* V0.0.3    新增已注册指纹(有效模板)查询函数。
* V0.0.2    优化LED控制，增加多种LED状态；
            优化验证指纹，增加无指纹时，LED灯控制参数；
            优化添加指纹，增加参数，可控指纹拼接次数；
            新增LED自由控制函数。
* V0.0.1    基础功能完成，验证指纹，删除指纹，添加指纹。

## 联系我们 Contact Us
* http://www.yfrobot.com.cn/wiki/index.php?title=%E8%81%94%E7%B3%BB%E6%88%91%E4%BB%AC

## 其他扩展库 Other extension libraries

## 参考 Reference Resources