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
`YFROBOTTTS YF_TTS(9, 8);  //软串口引脚，RX：D9（可以忽略）   TX：D8`

ESP32 主板：
`YFROBOTTTS YF_TTS(16, 17); // 使用 ESP32 的硬件串口2，自定义引脚RX：16    TX：17`

Methods：

初始化TTS引擎，设置通信波特率和默认参数。
`YF_TTS.begin(115200);`

设置TTS参数，如发音人、音量、语速和语调。
@param parameter 参数类型，'m'为发音人，'s'为语速，'t'为语调，'v'为音量。
@param value 参数的值，范围为0-9。
查看更多详情：https://pjfcckenlt.feishu.cn/wiki/JRItwhMCWi9DuOklQZScmdUjnVb
`YF_TTS.setTTSParameters('m', 0);`

让TTS引擎说话。
@param data 要朗读的文本。
查看更多详情：https://pjfcckenlt.feishu.cn/wiki/OZcfwiVoziNnkxkKkIRcJwIZndg
`YF_TTS.speak("谢谢使用");` 

## 更新日志 Release Note

* V0.0.2    优化代码及相关注释，增加example。Update Date: 20240606
* V0.0.1    基础功能完成，语音合成播报。Update Date: 20240430

## 联系我们 Contact Us
* http://www.yfrobot.com.cn/wiki/index.php?title=%E8%81%94%E7%B3%BB%E6%88%91%E4%BB%AC

## 其他扩展库 Other extension libraries

## 参考 Reference Resources