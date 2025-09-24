#ifndef TELEGRAM_CONTROL_ESP32_H
#define TELEGRAM_CONTROL_ESP32_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <map>

class TelegramControlESP32 {
  private:
    const char* ssid;
    const char* password;
    const char* botToken;
    const char* chatID;
    int intervalo;
    unsigned long ultimoTiempo;
    WiFiClientSecure client;
    UniversalTelegramBot bot;
    std::map<String, int> pines;
    std::map<int, bool> estados;

  public:
    TelegramControlESP32(const char* ssid, const char* password, const char* botToken, const char* chatID, int intervalo = 1000);
    void iniciar();
    void registrarPin(String nombre, int pin);
    void actualizar();
    void enviarMensaje(String texto);  // ✅ NUEVA FUNCIÓN

  private:
    void manejarMensajes(int cantidad);
};

#endif