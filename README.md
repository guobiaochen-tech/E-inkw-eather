# E-inkw-eather
墨水瓶气象站
# 🖥️ ESP32-S3 墨水屏天气站

基于 ESP32-S3 的 2.9 寸四色墨水屏天气显示站，支持温湿度监测、天气查询、MQTT 数据上报。

## ✨ 功能特性

- 🌡️ **实时温湿度监测** - SHT11 传感器，精度高
- 🌤️ **天气信息显示** - 心知天气 API，实时天气 + 3日预报
- 📊 **MQTT 数据上报** - 温度、湿度、电池电压、WiFi 信号
- 🔋 **智能休眠省电** - 白天 30 分钟唤醒，夜间 6 小时休眠
- 🎨 **四色墨水屏** - 黑白红黄，温度变色提示
- 📶 **信号强度显示** - WiFi 信号图标实时更新
- 🔋 **电池电量监测** - 电压采集 + 电量等级显示

## 📷 效果展示

```
┌────────────────────┐
│ 📶            🔋   │  ← WiFi信号 + 电池
│                    │
│      23.5℃        │  ← 大号温度（颜色随温度变化）
│       室内 65%     │
├────────────────────┤
│      ☀️ 晴天       │  ← 天气图标
│      舟山 25℃     │
├────────────────────┤
│ 预报               │
│ 明天: 晴 18~25℃    │  ← 天气预报
│ 后天: 多云 16~23℃  │
└────────────────────┘
```

## 🔧 硬件清单

| 组件 | 型号 | 说明 |
|------|------|------|
| MCU | ESP32-S3-DevKitC-1 | 主控板 |
| 显示屏 | GDEY029F51H | 2.9寸四色墨水屏 (128x296) |
| 温湿度传感器 | SHT11 | I2C 接口 |
| 电源 | 3.7V 锂电池 + 充电模块 | 可选 |

## 📌 引脚连接

### 墨水屏 (SPI)
| 功能 | GPIO |
|------|------|
| CS | 11 |
| DC | 10 |
| RST | 9 |
| BUSY | 8 |
| SCK | 12 |
| MOSI | 13 |

### SHT11 温湿度传感器
| 功能 | GPIO |
|------|------|
| DATA | 7 |
| CLK | 6 |

### 电池电压检测
| 功能 | GPIO |
|------|------|
| ADC | 3 |

## 🚀 快速开始

### 1. 克隆项目

```bash
git clone https://github.com/你的用户名/墨水屏2.9寸.git
cd 墨水屏2.9寸
```

### 2. 安装依赖

使用 PlatformIO 打开项目，依赖会自动安装。

### 3. 配置参数

编辑 `src/config.h`，填写你的配置：

```c
// WiFi 配置
#define WIFI_SSID "你的WiFi名称"
#define WIFI_PASS "你的WiFi密码"

// MQTT 配置
#define MQTT_SERVER "192.168.1.3"
#define MQTT_USER "你的MQTT用户名"
#define MQTT_PASS "你的MQTT密码"

// 心知天气 API
#define SENI_KEY "你的API_KEY"
#define LOCATION "101210901"  // 城市ID
```

### 4. 编译上传

```bash
pio run -t upload
```

## 📁 项目结构

```
墨水屏2.9寸/
├── src/
│   ├── main.cpp           # 主程序
│   ├── config.h           # 配置文件（敏感信息）
│   ├── debug_config.h     # 调试开关
│   ├── E_ink_128x296.cpp  # 墨水屏驱动
│   ├── E_ink_128x296.h
│   ├── SHT11.cpp         # 温湿度传感器
│   ├── SHT11.h
│   ├── User_timer.cpp    # WiFi/天气API/图标数据
│   ├── User_timer.h
│   └── User_u8g2.cpp     # 中文字体库
├── platformio.ini        # PlatformIO 配置
└── README.md
```

## 🔌 MQTT 主题

| 主题 | 说明 | 单位 |
|------|------|------|
| `home/sensor/temp` | 温度 | °C |
| `home/sensor/humi` | 湿度 | % |
| `home/sensor/battery` | 电池电压 | V |
| `home/sensor/wifi_signal` | WiFi 信号强度 | dBm |

## 🌐 天气 API

使用[心知天气](https://www.seniverse.com/) API：

- 免费版支持 400 次/天
- 提供实时天气 + 3日预报
- 支持天气代码转图标

## ⚠️ 注意事项

1. **首次使用** - 请确保填写 `config.h` 中的所有配置项
2. **电池安全** - 锂电池需配合充电保护电路使用
3. **墨水屏刷新** - 全刷会闪烁，正常现象
4. **休眠功耗** - 深度休眠约 10μA，理论续航数月

## 📝 更新日志

- **2026-03** - 初始版本
  - 实时温湿度显示
  - 心知天气 API 集成
  - MQTT 数据上报
  - 智能休眠策略

## 📜 开源协议

MIT License

## 🙏 致谢

- [GxEPD2](https://github.com/ZinggJM/GxEPD2) - 电子墨水屏驱动库
- [U8g2](https://github.com/olikraus/u8g2) - 中文字体库
- [心知天气](https://www.seniverse.com/) - 天气数据 API
