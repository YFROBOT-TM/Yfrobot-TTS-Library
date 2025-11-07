# Yfrobot-TTS-Library
YFROBOT TTS module Library for Arduino
注意，硬件有更新V2模块。

![](./assets/YFTTS.jpg)![](./assets/yfrobot_tts.png)


## 相关链接 Links

* 产品购买链接: [YFROBOT商城](https://www.yfrobot.com/)、[YFROBOT淘宝商城](https://yfrobot.taobao.com/).

#### 库使用说明：
* 调用库：
`#include <YFTTS.h>   // 包含头文件`
`#include <YFTTSV2.h>   // 包含头文件 V2版本模块`

* 创建对象：

UNO 主板：
`#include <SoftwareSerial.h>`

`SoftwareSerial mySerial(-1, 10);  // RX, TX ;假设我们使用10号引脚，不使用主板的 RX引脚`

`YFTTS YF_TTS(mySerial);           // 绑定串口设备`

ESP32 主板：
`YFTTS YF_TTS(&Serial2);`

Methods：

* 初始化TTS引擎，设置通信波特率和默认参数。

UNO 主板：
`YF_TTS.begin(115200);  // 初始化TTS，默认波特率115200，请注意初始化需要500ms左右`

ESP32 主板：
`YF_TTS.begin(115200, -1, 25);  // 初始化TTS，默认波特率115200, 主板TX引脚25，请注意初始化需要500ms左右`

* 设置TTS参数，如发音人、音量、语速和语调。

    @param parameter 参数类型，'m'为发音人，'s'为语速，'t'为语调，'v'为音量。
    @param value 参数的值，范围为0-9。
    查看更多详情：https://pjfcckenlt.feishu.cn/wiki/JRItwhMCWi9DuOklQZScmdUjnVb

`YF_TTS.setTTSParameters('m', 0);`

* 让TTS引擎说话。
    @param data 要朗读的文本。
    查看更多详情：https://pjfcckenlt.feishu.cn/wiki/OZcfwiVoziNnkxkKkIRcJwIZndg

`YF_TTS.speak("谢谢使用");` 

* 让TTS引擎说话， 支持字符串类型。

`String text = "字符串测试";`
`YF_TTS.speak(text);` 

* 让TTS引擎说话， 支持数字类型。

`YF_TTS.speak(20);` 


## 硬件支持列表 Hardware Support
主板型号            | ArduinoC    | 备注
------------------ | :----------: | -----
arduino uno  R3      |   √已测试    | 软串口
ESP32系列             |   √已测试    | 硬串口Serial2

## 更新日志 Release Note

* V2.0.1    新增语音合成模块V2支持(V2模块支持UTF8编码，完全适配arduino，显著减少Flash占用，程序空间释放，更适合多功能应用)，并修改更新example，已测试。Update Date: 20251107
* V0.0.4    增加speak函数，适配字符串变量、数字变量，并修改更新example，已测试。Update Date: 20240923
* V0.0.3    修改代码，兼容ESP32，并增加example，已测试。Update Date: 20240607
* V0.0.2    优化代码及相关注释，增加example。Update Date: 20240606
* V0.0.1    基础功能完成，语音合成播报。Update Date: 20240430

## 联系我们 Contact Us
* http://www.yfrobot.com.cn/wiki/index.php?title=%E8%81%94%E7%B3%BB%E6%88%91%E4%BB%AC

## 其他扩展库 Other extension libraries

## 参考 Reference Resources