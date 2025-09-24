#include "TelegramControlESP32.h"
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

#define BOT_TOKEN " "
#define CHAT_ID " "
#define WIFI_SSID " "
#define WIFI_PASS " "

TelegramControlESP32 bot(WIFI_SSID, WIFI_PASS, BOT_TOKEN, CHAT_ID);

void setup() {
  bot.iniciar();
  bot.registrarPin("luz", 2);
  bot.registrarPin("motor", 4);
  bot.enviarMensaje("Control activado correctamente ✅");
}

void loop() {
  bot.actualizar();
}