#include <YFTTSV2.h>

/**
 * YFTTS类的构造函数
 * @param serial 串口设备名称，用于指定TTS引擎使用的串口设备
 * 
 * 该构造函数初始化YFTTS类的实例，绑定一个特定的串口设备用于TTS引擎的通信。
 * 它是类的一个重要组成部分，因为TTS引擎的正确初始化离不开正确的串口配置。
 */
YFTTSV2::YFTTSV2(tserial serial)
: _serial(serial) {} // 初始化_serial成员变量

/**
 * 初始化TTS引擎，设置通信波特率和默认参数。
 * @param baudRate 串行通信的波特率。
 */
void YFTTSV2::begin(long baudRate) {
#if defined(__AVR__) || defined(ESP8266) || defined(NRF52) || defined(NRF5)
  _serial.begin(baudRate);
#endif
  setTTSParameters('m', 0);
  setTTSParameters('s', 5);
  setTTSParameters('t', 5);
  setTTSParameters('v', 1);
  delay(500);
}

/**
 * 初始化文本转语音（TTS）模块
 * 
 * 此函数用于在给定的波特率和收发引脚上初始化串口，并设置TTS的初始参数。
 * 初始化后，会等待一段时间以确保TTS模块正确启动。
 * 
 * @param baudRate 串口通信的波特率。
 * @param rxPin 串口接收引脚的编号。
 * @param txPin 串口发送引脚的编号。
 */
void YFTTSV2::begin(long baudRate, int rxPin, int txPin) {
#ifdef ESP32
  _serial->begin(baudRate, SERIAL_8N1, rxPin, txPin);  // 初始化串口通信
  setTTSParameters('m', 0);  // 设置音调模式为正常
  setTTSParameters('s', 5);  // 设置语速为中等
  setTTSParameters('t', 5);  // 设置音调为中等
  setTTSParameters('v', 1);  // 设置音量为正常
  delay(500);  // 等待TTS模块启动完成
#endif
}

/**
 * 让TTS引擎说话。
 * @param data 要朗读的文本。
 */
void YFTTSV2::speak(const char *data) {
  if (checkWorkState() != 0) {
    return;
  }
  sendData(data);
}

/**
 * 让TTS引擎说话。
 * @param data 要朗读的文本。
 */
void YFTTSV2::speak(const String& data) {
  speak(data.c_str());  // 调用已存在的 const char* 版本
}

/**
 * 让TTS引擎说话。
 * @param number 要朗读的数字，会被转换成字符串。
 */
void YFTTSV2::speak(int number) {
  char buffer[20];  // 假设最多处理20位数字
  snprintf(buffer, sizeof(buffer), "%d", number);
  speak(buffer);  // 调用 const char* 版本的 speak
}

/**
 * 检查TTS引擎的工作状态。
 * @return 工作状态码，0表示空闲，其他值表示忙。
 */
int YFTTSV2::checkWorkState() {
  // 假定设备总是空闲
  return 0;
}

/**
 * 发送数据到TTS引擎。
 * @param data 要发送的文本数据。
 */

void YFTTSV2::sendData(const char *data) {
  // 直接使用UTF-8编码的消息
  String utf8_str = String(data);

  // 获取UTF-8字符串的字节长度
  unsigned int len = utf8_str.length();
  unsigned char buffer[len + 6];  // 包括头字节和长度字节

  // 填充缓冲区
  buffer[0] = 0xFD;           // 帧头
  buffer[1] = (len + 2) >> 8; // 数据长度高字节
  buffer[2] = (len + 2) & 0xFF; // 数据长度低字节
  buffer[3] = 0x01;           // cmd byte
  buffer[4] = 0x04;           // 编码参数：0x04表示UTF-8编码

  // 复制UTF-8编码数据
  for (unsigned int i = 0; i < len; i++) {
    buffer[i + 5] = utf8_str.charAt(i);
  }

    // 发送数据
  for (unsigned int i = 0; i < len + 5; i++) {
#if defined(__AVR__) || defined(ESP8266) || defined(NRF52) || defined(NRF5)
    _serial.write(buffer[i]);
#elif defined(ESP32)
    _serial->write(buffer[i]);
#endif
  }
}

/**
 * 设置TTS参数，如发音人、音量、语速和语调。
 * @param parameter 参数类型，'m'为发音人，'s'为语速，'t'为语调，'v'为音量。
 * @param value 参数的值，范围为0-9。
 */
void YFTTSV2::setTTSParameters(char parameter, int value) {
  // 参数有效性检查
  if (value < 0 || value > 9) {
    return;  // 值范围不正确
  }
  /*
    支持男声/女声发音人、10 级音量、10 级语速、10 级语调调节 
    发音人：[m0]为女声，[m1]为男声，默认为[m0]女声 
    音量：  [v0]-[v9]，音量由小到大，默认为中间值 
    语速：  [s0]-[s9]，语速由快到慢，默认为中间值正常语速 
    语调：  [t0]-[t9]，语调由低到高，默认为中间值正常语调
  */
  // 根据参数类型和值构造参数代码
  char parameterCode[4] = { 0x5B, 0x00, 0x30 + value, 0x5D };  // [x0]格式，x为参数类型，0-9为值
  switch (parameter) {
    case 'm':                   // 发音人
      parameterCode[1] = 0x6D;  // 'm' 的 GB2312 编码
      break;
    case 'v':                   // 音量
      parameterCode[1] = 0x76;  // 'v' 的 GB2312 编码
      break;
    case 's':                   // 语速
      parameterCode[1] = 0x73;  // 's' 的 GB2312 编码
      break;
    case 't':                   // 语调
      parameterCode[1] = 0x74;  // 't' 的 GB2312 编码
      break;
    default:
      return;  // 未知参数
  }

  // 构造发送缓冲区
  unsigned char output[9];  // 根据需要设置缓冲区大小

  // 设置帧头和固定参数
  output[0] = 0xFD;  // 帧头
  output[1] = 0x00;  // 数据长度的高字节
  output[2] = 0x06;  // 数据长度的低字节 (6 bytes for parameter code + 1 for command + 1 for encoding)
  output[3] = 0x01;  // 命令字
  output[4] = 0x04;  // 编码参数 for YFTTS_V2 UTF8

  // 复制参数代码到发送缓冲区
  for (int i = 0; i < 4; i++) {
    output[i + 5] = parameterCode[i];
  }

//   // 计算校验和
//   output[9] = calculateXOR(output, 9);  // 从帧头开始到参数代码结束

  // 发送数据
  for (int i = 0; i < 9; i++) {
#if defined(__AVR__) || defined(ESP8266) || defined(NRF52) || defined(NRF5)
    _serial.write(output[i]);
#elif defined(ESP32)
    _serial->write(output[i]);
#endif
  }
}

// unsigned char YFTTSV2::calculateXOR(const unsigned char *data, int length) {
//   unsigned char xorValue = 0;
//   for (int i = 0; i < length; i++) {
//     xorValue ^= data[i];
//   }
//   return xorValue;
// }
