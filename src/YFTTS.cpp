
#include "YFTTS.h"
#include "UTF8ToGB2312.h"

YFTTS::YFTTS(int rxPin, int txPin)
  : _serial(rxPin, txPin) {}

void YFTTS::begin(long baudRate) {
  _serial.begin(baudRate);
  setTTSParameters('m', 1);
  setTTSParameters('v', 2);
  setTTSParameters('s', 4);
  setTTSParameters('t', 8);
}

void YFTTS::speak(const char *data) {
  if (checkWorkState() != 0) {
    return;
  }
  sendData(data);
}

int YFTTS::checkWorkState() {
  // 假定设备总是空闲
  return 0;
}

void YFTTS::sendData(const char *data) {
  size_t utf8Length = strlen(data);
  unsigned char gb2312_str[utf8Length * 2];  // Assuming maximum size after conversion
  size_t lenGB2312 = u2gb.UTF8ToGB2312(data, gb2312_str, sizeof(gb2312_str));

  unsigned int dat_len = lenGB2312 + 3;
  unsigned char output[dat_len + 5];

  output[0] = 0xFD;
  output[1] = (dat_len >> 8) & 0xFF;
  output[2] = dat_len & 0xFF;
  output[3] = 0x01;
  output[4] = 0x01;

  for (size_t i = 0; i < lenGB2312; i++) {
    output[i + 5] = gb2312_str[i];
  }

  output[lenGB2312 + 5] = calculateXOR(output, dat_len + 5);

  for (size_t i = 0; i < dat_len + 6; i++) {
    _serial.write(output[i]);
  }
}

unsigned char YFTTS::calculateXOR(const unsigned char *data, int length) {
  unsigned char xorValue = 0;
  for (int i = 0; i < length; i++) {
    xorValue ^= data[i];
  }
  return xorValue;
}

void YFTTS::setTTSParameters(char parameter, int value) {
  // 参数有效性检查
  if (value < 1 || value > 10) {
    return;  // 值范围不正确
  }

  // 根据参数类型和值构造参数代码
  char parameterCode[4] = { 0x5B, 0x00, 0x30 + (value - 1), 0x5D };  // [x0]格式，x为参数类型，0-9为值
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
  unsigned char output[10];  // 根据需要设置缓冲区大小

  // 设置帧头和固定参数
  output[0] = 0xFD;  // 帧头
  output[1] = 0x00;  // 数据长度的高字节
  output[2] = 0x06;  // 数据长度的低字节 (6 bytes for parameter code + 1 for command + 1 for encoding)
  output[3] = 0x01;  // 命令字
  output[4] = 0x01;  // 编码参数

  // 复制参数代码到发送缓冲区
  for (int i = 0; i < 4; i++) {
    output[i + 5] = parameterCode[i];
  }

  // 计算校验和
  output[9] = calculateXOR(output, 9);  // 从帧头开始到参数代码结束

  // 发送数据
  for (int i = 0; i < 10; i++) {
    _serial.write(output[i]);
  }
}
