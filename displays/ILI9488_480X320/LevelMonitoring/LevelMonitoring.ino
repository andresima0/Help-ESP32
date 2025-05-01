/*
  Sistema de Monitoramento de Nível com ESP32, Tela ILI9488 e Touchscreen XPT2046.

  Funcionalidades gerais:
  - Inicializa a tela e exibe "Connecting to Wi-Fi..." imediatamente ao ligar.
  - Tenta conexão Wi-Fi em até 30 segundos.
  - Se não conectar:
      - Exibe "No signal" na tela.
      - Ativa o pino 33 para resetar fisicamente o modem.
      - Reinicia o ESP32 junto com o modem.
  - Exibição dinâmica do MAC Address e IP na Top Bar após conexão.
  - Leitura analógica contínua de um potenciômetro (pino 34) com suavização por média de 10 amostras.
  - Interface touchscreen com fluxo de confirmação para envio dos dados:
      - Tela inicial exibe o nível atual.
      - Botão "Send" para solicitar envio.
      - Tela de confirmação "Confirm submission?" com "Confirm" e "Cancel".
      - Apenas após confirmação, o valor é atualizado para a página web.
  - Página web:
      - Exibe "Level submitted: X%".
      - Atualização automática a cada 3 segundos.
  - Tratamento de falhas:
      - Se perder a conexão em operação: exibe "No signal", ativa o pino 33 e reinicia o ESP32.

  Instruções de uso:
  - Configure o SSID e senha Wi-Fi no código.
  - Compile e carregue o firmware no ESP32.
  - Ao ligar, observe o IP mostrado no display para acessar via navegador: http://<IP_DO_ESP32>/submit
  - Ajuste o potenciômetro e confirme o envio através do touchscreen.
*/

#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "esp_system.h"

TFT_eSPI tft = TFT_eSPI();
SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS);
AsyncWebServer server(80);

// Wi-Fi
const char* ssid = "Nome da rede";
const char* password = "Senha da rede";

// Tela
#define SCREEN_WIDTH   480
#define SCREEN_HEIGHT  320
#define FONT_MAIN        4
#define FONT_SMALL       2
#define TOP_BAR_HEIGHT  24
#define COLOR_TOP_BAR   TFT_LIGHTGREY

// Botões
#define BUTTON_W       200
#define BUTTON_H        60
#define BUTTON_Y  (SCREEN_HEIGHT - TOP_BAR_HEIGHT - BUTTON_H - 15)
#define BUTTON_GAP      60
#define SEND_X    ((SCREEN_WIDTH - BUTTON_W)/2)
#define CANCEL_W  ((SCREEN_WIDTH/2) - BUTTON_GAP*1.5)
#define CONFIRM_W CANCEL_W
#define CANCEL_X BUTTON_GAP
#define CONFIRM_X (SCREEN_WIDTH/2 + BUTTON_GAP/2)
#define COLOR_SEND_BTN    TFT_GREEN
#define COLOR_CANCEL_BTN  TFT_RED
#define COLOR_CONFIRM_BTN TFT_GREEN

// Potenciômetro
#define POT_PIN 34

// Calibração do touchscreen
#define TOUCH_X_MIN  200
#define TOUCH_X_MAX 3700
#define TOUCH_Y_MIN 240
#define TOUCH_Y_MAX 3800

// Estados
enum class AppState {
  InitialScreen,
  ConfirmScreen,
  SuccessScreen,
  WifiFailure
};

AppState currentState = AppState::InitialScreen;
int weight = 0, lastWeight = -1;
int submittedWeight = -1;

// Leitura suavizada
int readAnalogSmooth(int pin) {
  const int samples = 10;
  long sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(pin);
    delay(1);
  }
  return sum / samples;
}

void drawTopBar() {
  tft.fillRect(0, 0, SCREEN_WIDTH, TOP_BAR_HEIGHT, COLOR_TOP_BAR);
  tft.setTextColor(TFT_BLACK, COLOR_TOP_BAR);
  tft.setTextDatum(TL_DATUM);
  tft.drawString("MAC: " + WiFi.macAddress(), 2, (TOP_BAR_HEIGHT - 8)/2, FONT_SMALL);
  tft.setTextDatum(TR_DATUM);
  tft.drawString("IP: " + WiFi.localIP().toString(), SCREEN_WIDTH - 2, (TOP_BAR_HEIGHT - 8)/2, FONT_SMALL);
}

void drawInitialScreen() {
  tft.fillScreen(TFT_WHITE);
  drawTopBar();
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("Current Level:", SCREEN_WIDTH/2, BUTTON_Y - 120, FONT_MAIN);
  tft.drawString(String(weight) + " %", SCREEN_WIDTH/2, BUTTON_Y - 80, FONT_MAIN);
  tft.fillRoundRect(SEND_X, BUTTON_Y, BUTTON_W, BUTTON_H, 10, COLOR_SEND_BTN);
  tft.setTextColor(TFT_BLACK, COLOR_SEND_BTN);
  tft.drawCentreString("Send", SEND_X + BUTTON_W/2, BUTTON_Y + BUTTON_H/2 - (FONT_MAIN*4)/2, FONT_MAIN);
}

void drawConfirmationScreen() {
  tft.fillScreen(TFT_WHITE);
  drawTopBar();
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("Level: " + String(weight) + " %", SCREEN_WIDTH/2, BUTTON_Y - 120, FONT_MAIN);
  tft.drawString("Confirm submission?", SCREEN_WIDTH/2, BUTTON_Y - 80, FONT_MAIN);
  tft.fillRoundRect(CANCEL_X, BUTTON_Y, CANCEL_W, BUTTON_H, 10, COLOR_CANCEL_BTN);
  tft.setTextColor(TFT_WHITE, COLOR_CANCEL_BTN);
  tft.drawCentreString("Cancel", CANCEL_X + CANCEL_W/2, BUTTON_Y + BUTTON_H/2 - (FONT_MAIN*4)/2, FONT_MAIN);
  tft.fillRoundRect(CONFIRM_X, BUTTON_Y, CONFIRM_W, BUTTON_H, 10, COLOR_CONFIRM_BTN);
  tft.setTextColor(TFT_BLACK, COLOR_CONFIRM_BTN);
  tft.drawCentreString("Confirm", CONFIRM_X + CONFIRM_W/2, BUTTON_Y + BUTTON_H/2 - (FONT_MAIN*4)/2, FONT_MAIN);
}

void updateWeightDisplay() {
  if (weight != lastWeight) {
    tft.fillRect(0, BUTTON_Y - 80 - FONT_MAIN * 8, SCREEN_WIDTH, FONT_MAIN * 8, TFT_WHITE);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(String(weight) + " %", SCREEN_WIDTH/2, BUTTON_Y - 80, FONT_MAIN);
    lastWeight = weight;
  }
}

void showSentMessage() {
  tft.fillScreen(TFT_WHITE);
  drawTopBar();
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("Submission successful!", SCREEN_WIDTH/2, (SCREEN_HEIGHT + TOP_BAR_HEIGHT)/2, FONT_MAIN);
}

void handleWifiFailure() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("No signal", SCREEN_WIDTH/2, SCREEN_HEIGHT/2, FONT_MAIN);
  pinMode(33, OUTPUT);
  digitalWrite(33, HIGH);
  delay(1000);
  digitalWrite(33, LOW);
  delay(5000);
  ESP.restart();
}

void handleSubmission(AsyncWebServerRequest* req) {
  String payload;
  if (submittedWeight >= 0)
    payload = "Level submitted: " + String(submittedWeight) + " %";
  else
    payload = "No submission yet.";
  String html = "<meta http-equiv=\"refresh\" content=\"3\">" + payload;
  req->send(200, "text/html", html);
  Serial.println("[WEB] Served: " + payload);
}

bool isInside(int tx, int ty, int bx, int by, int bw, int bh) {
  return tx >= bx && tx <= bx + bw && ty >= by && ty <= by + bh;
}

void setup() {
  Serial.begin(115200);

  // Inicializa a tela
  tft.init();
  tft.setRotation(1);
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  touchscreen.setRotation(1);

  pinMode(POT_PIN, INPUT);
  pinMode(33, OUTPUT); // Pino do modem reset (relé / circuito)

  // Exibe logo na inicialização
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("Connecting to Wi-Fi...", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, FONT_MAIN);

  // Inicia Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  unsigned long start = millis();
  const unsigned long wifiTimeout = 30000; // 30 segundos para tentar

  while (WiFi.status() != WL_CONNECTED && millis() - start < wifiTimeout) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    // Se falhou: mostra "No signal"
    tft.fillScreen(TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("No signal", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, FONT_MAIN);

    // ✅ RESETAR modem + ESP JUNTOS:
    digitalWrite(33, HIGH); // Ativa o reset do modem
    delay(100);             // Dá tempo do pulso ser reconhecido
    ESP.restart();          // Reinicia o ESP32 imediatamente
  }

  // Se conectou, vida normal:
  Serial.println("Connected: " + WiFi.localIP().toString());

  server.on("/submit", HTTP_GET, handleSubmission);
  server.begin();

  drawInitialScreen();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED && currentState != AppState::WifiFailure)
    currentState = AppState::WifiFailure;

  switch (currentState) {
    case AppState::InitialScreen:
      weight = map(readAnalogSmooth(POT_PIN), 0, 4095, 0, 100);
      updateWeightDisplay();
      if (touchscreen.touched()) {
        TS_Point p = touchscreen.getPoint();
        int tx = map(p.x, TOUCH_X_MIN, TOUCH_X_MAX, 0, SCREEN_WIDTH);
        int ty_raw = map(p.y, TOUCH_Y_MIN, TOUCH_Y_MAX, 0, SCREEN_HEIGHT);
        int ty = SCREEN_HEIGHT - ty_raw;

        if (isInside(tx, ty, SEND_X, BUTTON_Y, BUTTON_W, BUTTON_H)) {
          drawConfirmationScreen();
          currentState = AppState::ConfirmScreen;
        }
      }
      break;

    case AppState::ConfirmScreen: {
      unsigned long t0 = millis();
      while (millis() - t0 < 10000) {
        if (touchscreen.touched()) {
          TS_Point q = touchscreen.getPoint();
          int cx = map(q.x, TOUCH_X_MIN, TOUCH_X_MAX, 0, SCREEN_WIDTH);
          int cy_raw = map(q.y, TOUCH_Y_MIN, TOUCH_Y_MAX, 0, SCREEN_HEIGHT);
          int cy = SCREEN_HEIGHT - cy_raw;

          if (isInside(cx, cy, CANCEL_X, BUTTON_Y, CANCEL_W, BUTTON_H)) {
            drawInitialScreen();
            currentState = AppState::InitialScreen;
            break;
          }

          if (isInside(cx, cy, CONFIRM_X, BUTTON_Y, CONFIRM_W, BUTTON_H)) {
            submittedWeight = weight;
            showSentMessage();
            currentState = AppState::SuccessScreen;
            break;
          }
        }
        delay(100);
      }
      if (currentState == AppState::ConfirmScreen) {
        drawInitialScreen();
        currentState = AppState::InitialScreen;
      }
      break;
    }

    case AppState::SuccessScreen:
      delay(2000);
      drawInitialScreen();
      currentState = AppState::InitialScreen;
      break;

    case AppState::WifiFailure:
      handleWifiFailure();
      break;
  }

  delay(100);
}