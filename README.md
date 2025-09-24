# TelegramControlESP32 📲🔌

Una biblioteca educativa para controlar múltiples pines del ESP32 mediante comandos de Telegram. Diseñada para jóvenes, docentes y entusiastas de la robótica que buscan una forma sencilla, segura y divertida de integrar comunicación bidireccional entre hardware y mensajería.

---

## 🚀 Características

- Control de múltiples pines con comandos personalizados (`/encender_luz`, `/estado_motor`, etc.)
- Comunicación segura con Telegram usando `UniversalTelegramBot`
- Envío de mensajes desde el ESP32 al chat de Telegram
- Registro dinámico de pines con alias amigables
- Código modular, claro y fácil de enseñar

---

## 📦 Instalación

1. Clona este repositorio:
   ```bash
   git clone https://github.com/tu-usuario/TelegramControlESP32.git

2. Pega la carpeta TelegramControlESP32 dentro de la carpeta libraries de Arduino.
3. Asegúrate de tener instaladas las siguientes librerías:
- WiFi.h
- WiFiClientSecure.h
- UniversalTelegramBot
- ArduinoJson

Ejemplo:
```cpp
#include "TelegramControlESP32.h"

#define BOT_TOKEN "TU_TOKEN"
#define CHAT_ID "TU_CHAT_ID"
#define WIFI_SSID "TU_SSID"
#define WIFI_PASS "TU_PASSWORD"

TelegramControlESP32 bot(WIFI_SSID, WIFI_PASS, BOT_TOKEN, CHAT_ID);

void setup() {
  bot.iniciar();
  bot.registrarPin("luz", 2);
  bot.registrarPin("motor", 4);
  bot.enviarMensaje("ESP32 conectado correctamente ✅");
}

void loop() {
  bot.actualizar();

  if (digitalRead(4)) {
    bot.enviarMensaje("⚙️ El motor está activo");
    delay(5000);
  }
}
```
📚 Comandos disponiblesUna vez registrado un pin con nombre "nombre", el bot acepta:- /encender_nombre
- /apagar_nombre
- /estado_nombre
- /menu → muestra todos los comandos disponibles
  
🧠 Ideal para…- Clases de robótica educativa
- Proyectos STEAM con jóvenes
- Prototipos accesibles y personalizados
- Comunicación aumentativa y tecnología de apoyo


📜 LicenciaEste proyecto está bajo la licencia MIT. Puedes usarlo, modificarlo y compartirlo libremente, siempre reconociendo al autor original.
✨ AutorGustavo — Prof en robótica educativa, apasionado por la inclusión, la creatividad y el aprendizaje colaborativo.
