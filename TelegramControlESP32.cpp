#include "TelegramControlESP32.h"

TelegramControlESP32::TelegramControlESP32(const char* ssid, const char* password, const char* botToken, const char* chatID, int intervalo)
  : ssid(ssid), password(password), botToken(botToken), chatID(chatID), intervalo(intervalo), ultimoTiempo(0), bot(botToken, client) {}

void TelegramControlESP32::iniciar() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando WiFi...");
  }
  Serial.println("Conectado. IP: " + WiFi.localIP().toString());
}

void TelegramControlESP32::registrarPin(String nombre, int pin) {
  pines[nombre] = pin;
  estados[pin] = LOW;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void TelegramControlESP32::actualizar() {
  if (millis() - ultimoTiempo > intervalo) {
    int nuevosMensajes = bot.getUpdates(bot.last_message_received + 1);
    while (nuevosMensajes) {
      manejarMensajes(nuevosMensajes);
      nuevosMensajes = bot.getUpdates(bot.last_message_received + 1);
    }
    ultimoTiempo = millis();
  }
}

void TelegramControlESP32::manejarMensajes(int cantidad) {
  for (int i = 0; i < cantidad; i++) {
    String chat_id = bot.messages[i].chat_id;
    String texto = bot.messages[i].text;
    String nombre = bot.messages[i].from_name;

    if (chat_id != chatID) {
      bot.sendMessage(chat_id, "Usuario no autorizado", "");
      continue;
    }

    if (texto == "/menu") {
      String respuesta = "Hola, " + nombre + "\nComandos disponibles:\n";
      for (auto const& [nombrePin, pin] : pines) {
        respuesta += "              ""\n";
        respuesta += "/encender_" + nombrePin + "\n";
        respuesta += "/apagar_" + nombrePin + "\n";
        respuesta += "/estado_" + nombrePin + "\n";
        respuesta += "______________""\n";
      }
      bot.sendMessage(chat_id, respuesta, "");
    }

    for (auto const& [nombrePin, pin] : pines) {
      if (texto == "/encender_" + nombrePin) {
        estados[pin] = HIGH;
        digitalWrite(pin, HIGH);
        bot.sendMessage(chat_id, "Encendido: " + nombrePin, "");
      } else if (texto == "/apagar_" + nombrePin) {
        estados[pin] = LOW;
        digitalWrite(pin, LOW);
        bot.sendMessage(chat_id, "Apagado: " + nombrePin, "");
      } else if (texto == "/estado_" + nombrePin) {
        String estadoTexto = digitalRead(pin) ? "ENCENDIDO" : "APAGADO";
        bot.sendMessage(chat_id, nombrePin + ": " + estadoTexto, "");
      }
    }
  }
}

void TelegramControlESP32::enviarMensaje(String texto) {
  bot.sendMessage(chatID, texto, "");
}