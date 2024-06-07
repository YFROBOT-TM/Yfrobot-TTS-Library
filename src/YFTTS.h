
#ifndef YFTTS_H
#define YFTTS_H

#include <Arduino.h>
#include <UTF8ToGB2312.h>

#if defined(__AVR__) || defined(ESP8266) || defined(NRF52)
#include <SoftwareSerial.h>
#define tserial SoftwareSerial
#elif defined(ESP32)
#include <HardwareSerial.h>
#define tserial HardwareSerial*
#endif

/**
 * @brief YFTTS类用于实现语音合成功能
 * 该类通过SoftwareSerial与外部语音合成模块通信，
 * 提供了开始通信、说话、设置语音参数和检查工作状态等功能。
 */
class YFTTS {
public:
    /**
     * @brief 构造函数初始化语音合成器的串口通信
     */
    YFTTS(tserial serial);

    /**
     * @brief 初始化串口通信速率
     * @param baudRate 串口通信速率
     */
    void begin(long baudRate);

    /**
     * 初始化串口通信，适用ESP32主板自定义引脚
     *  该函数用于初始化串口通信，设置通信速率和收发引脚。
     *  在使用串口通信之前，必须先调用此函数进行初始化。
     * @param baudRate 串口通信的波特率。决定了数据传输的速度。
     * @param rxPin 串口接收数据的引脚编号。设置为-1表示不使用接收引脚。
     * @param txPin 串口发送数据的引脚编号。设置为-1表示不使用发送引脚。
     */
    void begin(long baudRate, int rxPin, int txPin);

    /**
     * @brief 让语音合成器说出给定的数据
     * @param data 要说的数据，以字符串形式提供
     */
    void speak(const char *data);
    /**
     * @brief 设置语音合成参数
     * @param parameter 参数标识符
     * @param value 参数值
     */
    void setTTSParameters(char parameter, int value);
    /**
     * @brief 检查语音合成器的工作状态 （默认不使用）
     * @return int 工作状态码，具体含义依赖于语音合成器的实现
     */
    int checkWorkState();

private:
    U2GB u2gb;                          /**< UTF8到GB2312转换对象，用于处理中文字符 */


#if defined(__AVR__) || defined(ESP8266) || defined(NRF52)
    SoftwareSerial _serial;                    /**< 用于与语音合成器通信的软件串口 */
#elif defined(ESP32)
    HardwareSerial* _serial;            /**< 用于与语音合成器通信的硬件串口 */
#endif

    void sendData(const char *data);    /**< 发送数据到语音合成器的私有方法 */
    // unsigned char calculateXOR(const unsigned char *data, int length);
};

#endif
