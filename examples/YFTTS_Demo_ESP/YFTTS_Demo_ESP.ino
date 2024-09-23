/*
  语音合成测试程序-ESP32系列主板

  关于引脚使用说明
    语音合成模块使用串口通讯，引脚顺序为 G V RX TX；
    理论上需要双引脚进行串口通讯，但实际模块只需要接收主板串口发送的数据，所以只需要使用模块的RX引脚。
*/

#include <YFTTS.h>
YFTTS YF_TTS(&Serial2);  // 绑定串口Serial2, 默认引脚RX在GPIO16, TX在GPIO17

// 配置主板RX、TX引脚根据实际连接更改
//假设我们使用10号引脚，不使用主板的 RX引脚
void setup() {
  Serial.begin(9600);
  YF_TTS.begin(115200, -1, 25);  // 初始化TTS，默认波特率115200, 主板TX引脚25，请注意初始化需要500ms左右
  /*
    支持男声/女声发音人、10 级音量、10 级语速、10 级语调调节 
    发音人：[m0]为女声，[m1]为男声，默认为[m0]女声 
    音量：  [v0]-[v9]，音量由小到大，默认为中间值 
    语速：  [s0]-[s9]，语速由快到慢，默认为中间值正常语速 
    语调：  [t0]-[t9]，语调由低到高，默认为中间值正常语调
  查看更多详情：https://pjfcckenlt.feishu.cn/wiki/JRItwhMCWi9DuOklQZScmdUjnVb
  */
  // 配置TTS，设置发音人、音量、语速、语调，以下配置可选，begin函数中已经默认配置
  YF_TTS.setTTSParameters('m', 0);  // 发音人；
  delay(500);
  YF_TTS.setTTSParameters('s', 5);  // 语速；
  delay(500);
  YF_TTS.setTTSParameters('t', 5);  // 语调；
  delay(500);
  YF_TTS.setTTSParameters('v', 1);  // 音量；注意喇叭功率有限，推荐音量不超过2使用；
  delay(500);

  /* 支持 15 种内置提示音效，其中:铃声 5 首；信息提示音 5 首；警示音 5 首
    铃声
        ring_1、ring_2、ring_3、ring_4、ring_5
    信息提示音
        message_1、message_2、message_3、message_4、message_5
    警示音 
        alert_1、alert_2、alert_3、alert_4、alert_5
  */
  YF_TTS.speak("alert_4");
  delay(2000);
  YF_TTS.speak("ring_1");
  delay(2000);

  String text = "字符串测试";
  YF_TTS.speak(text); // 支持字符串类型
  delay(2000);
  
  text = "100";
  YF_TTS.speak(text); // 支持字符串类型
  delay(2000);

  int textint = 20;
  YF_TTS.speak(textint); // 支持数字类型
  delay(2000);

  /* 语音合成测试 */
  YF_TTS.speak("谢谢使用");
  delay(3000);
  YF_TTS.speak("您好，欢迎光临");
  delay(3000);
  YF_TTS.speak("当前环境温度：26摄氏度");
  delay(4000);

  /* 带文本标注语音合成测试-
      详情说明：https://pjfcckenlt.feishu.cn/wiki/OZcfwiVoziNnkxkKkIRcJwIZndg */

  /* 带文本标注-多音字标记方式，语音合成测试 */
  YF_TTS.speak("空调[=tiao2]调[=tiao2]到三十度");
  delay(4000);
  /* 带文本标注-数字标记方式，语音合成测试 */
  YF_TTS.speak("共消费[n2]100 元，请拨打电话[n1]95511，手机号码[n3]17696701116。");
  delay(9000);
  /* 带文本标注-短停标记方式，语音合成测试 */
  YF_TTS.speak("欢迎使用[w0]我司的语音合成模块");
  delay(8000);
}

void loop() {
  // delay(5000); // 每10秒说一次
}
