
# ILI9488 3.5" Display (480x320) with ESP32

This repository contains tested and verified examples for using the ILI9488 3.5" SPI display with an ESP32. If you are working with this model, follow the instructions below carefully to ensure correct setup and operation.

## ✅ Requirements

- ESP32 development board  
- ILI9488 3.5" TFT display (480x320, SPI interface)  
- Correct wiring between the display and ESP32, as described in the [Pin Configuration](#pin-configuration) section  
- `TFT_eSPI` library (exact version and configuration from this repository)

## ⚙️ Setup Instructions

1. Wire the hardware according to the pin configuration provided below.
2. Download and install the `TFT_eSPI` library:
   - **Option A (Recommended):** Use the version included in this repository to ensure full compatibility.
   - **Option B:** Download the official version from [Bodmer’s GitHub](https://github.com/Bodmer/TFT_eSPI) and **replace** the `User_Setup.h` file with the one provided here.

⚠️ **Important:** You must use the exact configuration provided. Any changes or missing files may prevent the display from working properly.

---

## 📦 Using with Arduino IDE or PlatformIO

### 🧩 Arduino IDE

1. Install the `TFT_eSPI` library via the Library Manager or manually.
2. Replace the file `User_Setup.h` inside the library folder with the one provided in this repository.
   - On Windows, the path is usually:  
     `Documents/Arduino/libraries/TFT_eSPI/User_Setup.h`
3. Restart the Arduino IDE if it is open.
4. Compile and upload the example sketches.

### 🧰 PlatformIO (VS Code)

1. Add the following to your `platformio.ini`:
   ```ini
   lib_deps =
     bodmer/TFT_eSPI
   ```
2. Inside your project directory, create a file at:  
   `lib/TFT_eSPI/User_Setup.h`
3. Copy the `User_Setup.h` from this repository into that location.
4. PlatformIO will prioritize this file over the default.

---

## 📌 Pin Configuration - ILI9488 3.5" Display with Touch (480x320 pixels)

This display uses SPI communication for both image control (Display) and the touch panel. Below are the connections to an ESP32:

### 📺 Display

| Pin | Name | ESP32 | Function |
|-----|------|-------|----------|
| 1   | VDD  | 5V    | Power Supply (3.3V or 5V) |
| 2   | GND  | GND   | Ground |
| 3   | CS   | D15   | Chip Select for Display |
| 4   | RST  | EN    | Reset for Display Controller |
| 5   | D/C  | D2    | Command/Data Selection |
| 6   | SDI  | D13   | MOSI (ESP → Display, SPI) |
| 7   | SCK  | D14   | Serial Clock (SPI) |
| 8   | BL   | D4    | Backlight (3.3V, 5V or PWM) |
| 9   | SDO  | D12   | MISO (Display → ESP, SPI) |

### ✍️ Touch (Resistive Panel with SPI Controller)

| Pin | Name | ESP32 | Function |
|-----|------|-------|----------|
| 10  | TCK  | D25   | SPI Clock for Touch |
| 11  | TCS  | D26   | Chip Select for Touch |
| 12  | TDI  | D27   | MOSI (ESP → Touch) |
| 13  | TDO  | D32   | MISO (Touch → ESP) |
| 14  | PEN  | D33   | IRQ (Touch Interrupt) |

### ℹ️ Notes

- The ILI9488 display can operate with **3.3V or 5V**, depending on the model.
- **BL (Backlight)** can be controlled with PWM to adjust brightness.
- Make sure signal levels are compatible with ESP32's **3.3V logic**.
- You may need pull-up/pull-down resistors on the **PEN** (IRQ) pin.

---

## 📘 Versão em Português

Este repositório contém exemplos testados e verificados para o uso do display ILI9488 3.5" SPI com ESP32. Se você estiver utilizando este modelo, siga atentamente as instruções abaixo para garantir uma montagem correta e o funcionamento adequado.

### ✅ Requisitos

- Placa de desenvolvimento ESP32  
- Display TFT ILI9488 3.5" (480x320, interface SPI)  
- Fiação correta entre os pinos do display e do ESP32, conforme a seção [Configuração de Pinos](#configuração-de-pinos---display-ili9488-35-com-touch-480x320-pixels)  
- Biblioteca `TFT_eSPI` (versão e configuração exatas deste repositório)

### ⚙️ Instruções de Instalação

1. Realize a conexão do hardware conforme a configuração de pinos descrita abaixo.
2. Baixe e instale a biblioteca `TFT_eSPI`:
   - **Opção A (Recomendada):** Utilize a versão incluída neste repositório para garantir total compatibilidade.
   - **Opção B:** Baixe a versão oficial no [GitHub do Bodmer](https://github.com/Bodmer/TFT_eSPI) e **substitua** o arquivo `User_Setup.h` pelo fornecido aqui.

⚠️ **Importante:** É fundamental utilizar a configuração exata disponibilizada. Qualquer modificação ou ausência de arquivos pode impedir o funcionamento correto do display.

---

## 📦 Usando com Arduino IDE ou PlatformIO

### 🧩 Arduino IDE

1. Instale a biblioteca `TFT_eSPI` pelo Gerenciador de Bibliotecas ou manualmente.
2. Substitua o arquivo `User_Setup.h` da pasta da biblioteca pelo que está neste repositório.
   - No Windows, o caminho geralmente é:  
     `Documentos/Arduino/libraries/TFT_eSPI/User_Setup.h`
3. Reinicie o Arduino IDE se ele estiver aberto.
4. Compile e envie os exemplos.

### 🧰 PlatformIO (VS Code)

1. Adicione o seguinte ao seu `platformio.ini`:
   ```ini
   lib_deps =
     bodmer/TFT_eSPI
   ```
2. Dentro do diretório do projeto, crie o arquivo:  
   `lib/TFT_eSPI/User_Setup.h`
3. Copie o `User_Setup.h` deste repositório para essa localização.
4. O PlatformIO irá priorizar esse arquivo sobre o padrão da biblioteca.

---

## 📌 Configuração de Pinos - Display ILI9488 3.5" com Touch (480x320 pixels)

Este display utiliza comunicação SPI tanto para o controle da imagem (Display) quanto para o touch (Touch Panel). Abaixo estão as conexões com um ESP32:

### 📺 Display

| Pino | Nome | ESP32 | Função |
|------|------|-------|--------|
| 1    | VDD  | 5V    | Alimentação (3V3 ou 5V) |
| 2    | GND  | GND   | Terra |
| 3    | CS   | D15   | Chip Select do Display |
| 4    | RST  | EN    | Reset do Controlador do Display |
| 5    | D/C  | D2    | Seleção de Comando/Dados |
| 6    | SDI  | D13   | MOSI (ESP → Display, SPI) |
| 7    | SCK  | D14   | Clock Serial SPI |
| 8    | BL   | D4    | Backlight (3V3, 5V ou PWM) |
| 9    | SDO  | D12   | MISO (Display → ESP, SPI) |

### ✍️ Touch (Painel Resistivo com Controladora SPI)

| Pino | Nome | ESP32 | Função |
|------|------|-------|--------|
| 10   | TCK  | D25   | Clock SPI do Touch |
| 11   | TCS  | D26   | Chip Select do Touch |
| 12   | TDI  | D27   | MOSI (ESP → Touch) |
| 13   | TDO  | D32   | MISO (Touch → ESP) |
| 14   | PEN  | D33   | IRQ (Interrupção Touch) |

### ℹ️ Observações

- O display ILI9488 pode operar com alimentação de **3V3 ou 5V**, verifique o modelo.
- O **BL (Backlight)** pode ser controlado com PWM para ajuste de brilho.
- Certifique-se de que os níveis de sinal sejam compatíveis com os **3V3 do ESP32**.
- Utilize resistores de pull-up/pull-down se necessário no pino **PEN** (IRQ).

---
