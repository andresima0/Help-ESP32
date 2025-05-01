
# ILI9488 3.5" Display (480x320) with ESP32

This repository contains tested and verified examples for using the ILI9488 3.5" SPI display with an ESP32. If you are working with this model, follow the instructions below carefully to ensure correct setup and operation.

https://github.com/user-attachments/assets/d003ab97-f8d3-4522-9e78-adcebe305b31

## ✅ Requirements

- ESP32 development board  
- ILI9488 3.5" TFT display (480x320, SPI interface)  
- Correct wiring between the display and ESP32, as described in the [Pin Configuration](#pin-configuration) section  
- `TFT_eSPI` library (exact version and configuration from this repository)

## ⚙️ Setup Instructions

1. Wire the hardware according to the pin configuration provided below.
2. Download and install the `TFT_eSPI` library:
   - **Option A:** Use the version included in this repository to ensure full compatibility.
   - **Option B:** Use the official version from [Bodmer’s GitHub](https://github.com/Bodmer/TFT_eSPI) but **replace** the `User_Setup.h` file with the one provided here.

⚠️ **Important:** You must use the exact configuration provided. Any changes or missing files may prevent the display from working properly.

---

## 🧩 Installing the `TFT_eSPI` Library

### ✅ Arduino IDE

1. Via Library Manager (recommended)
   
   1.1. In Arduino IDE, go to **Sketch > Include Library > Manage Libraries...**  
   1.2. Search for **TFT_eSPI** and install the library by **Bodmer**.  
   1.3. Replace the `User_Setup.h` file inside the library folder with the one from this repository:

   📁 Default path on Windows:  
   `Documents/Arduino/libraries/TFT_eSPI/User_Setup.h`

   🔗 Custom setup file:  
   [User_Setup.h (GitHub)](https://github.com/andresima0/Help-ESP32/blob/main/displays/ILI9488_480X320/User_Setup.h)

   1.4. Restart Arduino IDE if it's already open.  
   1.5. Compile and upload the example sketches.

2. Manual Installation via ZIP

   2.1. Download the custom library from the link below:  
   🔗 [TFT_eSPI.zip (GitHub)](https://github.com/andresima0/Help-ESP32/blob/main/displays/ILI9488_480X320/TFT_eSPI.zip)

   2.2. In Arduino IDE, go to **Sketch > Include Library > Add .ZIP Library…**  
   2.3. Select the downloaded `.zip` file.  
   2.4. Make sure the folder is named `TFT_eSPI` under:  
   `Documents/Arduino/libraries/TFT_eSPI`

---

### 🧰 PlatformIO (VS Code)

1. Using `platformio.ini` (recommended)

   1.1. In your project, open the `platformio.ini` file and add:
   ```ini
   lib_deps =
     bodmer/TFT_eSPI
   ```

   1.2. Create a custom setup file at:  
   📁 `lib/TFT_eSPI/User_Setup.h`

   1.3. Copy the content of the custom `User_Setup.h` into this location:  
   🔗 [User_Setup.h (GitHub)](https://github.com/andresima0/Help-ESP32/blob/main/displays/ILI9488_480X320/User_Setup.h)

   > ✅ PlatformIO will prioritize this `User_Setup.h` from the `lib/` folder during compilation.

2. Manual Installation via ZIP
   
   2.1. Download the custom library from the link below:  
   🔗 [TFT_eSPI.zip (GitHub)](https://github.com/andresima0/Help-ESP32/blob/main/displays/ILI9488_480X320/TFT_eSPI.zip)

   2.2. Extract the contents into your project folder, for example:  
   📁 `lib/TFT_eSPI/`

   2.3. Make sure the custom `User_Setup.h` is included in that folder.

## 📌 Pin Configuration

This display uses SPI communication for both image control (Display) and the touch panel. Below are the connections to an ESP32:

### 📺 Display

| Pin | Name | ESP32 | Function |
|-----|------|-------|----------|
| 1   | VDD  | VIN   | Power Supply (3.3V or 5V) |
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

https://github.com/user-attachments/assets/d003ab97-f8d3-4522-9e78-adcebe305b31

## ✅ Requisitos

- Placa de desenvolvimento ESP32  
- Display TFT ILI9488 3.5" (480x320, interface SPI)  
- Fiação correta entre os pinos do display e do ESP32, conforme a seção [Configuração de Pinos](#configuração-de-pinos---display-ili9488-35-com-touch-480x320-pixels)  
- Biblioteca `TFT_eSPI` (versão e configuração exatas deste repositório)

## ⚙️ Instruções de Instalação

1. Realize a conexão do hardware conforme a configuração de pinos descrita abaixo.
2. Baixe e instale a biblioteca `TFT_eSPI`:
   - **Opção A:** Utilize a versão incluída neste repositório para garantir total compatibilidade.
   - **Opção B:** Use a versão oficial no [GitHub do Bodmer](https://github.com/Bodmer/TFT_eSPI) mas **substitua** o arquivo `User_Setup.h` pelo fornecido aqui.

⚠️ **Importante:** É fundamental utilizar a configuração exata disponibilizada. Qualquer modificação ou ausência de arquivos pode impedir o funcionamento correto do display.

---

## 🧩 Instalação da Biblioteca `TFT_eSPI`

### ✅ Arduino IDE

1. Pelo Gerenciador de Bibliotecas (recomendado)
   
   1.1. Na Arduino IDE, vá em **Sketch > Include Library > Manage Libraries...**  
   1.2. Procure por **TFT_eSPI** e instale a biblioteca do autor **Bodmer**.  
   1.3. Substitua o arquivo `User_Setup.h` dentro da pasta da biblioteca pelo fornecido neste repositório:

   📁 Caminho padrão no Windows:  
   `Documents/Arduino/libraries/TFT_eSPI/User_Setup.h`

   🔗 Arquivo personalizado:  
   [User_Setup.h (GitHub)](https://github.com/andresima0/Help-ESP32/blob/main/displays/ILI9488_480X320/User_Setup.h)

   1.4. Reinicie a Arduino IDE (caso já esteja aberta).  
   1.5. Compile e envie os exemplos para o seu dispositivo.

3. Instalação manual via ZIP
   2.1. Baixe a versão personalizada da biblioteca no link abaixo:  
   🔗 [TFT_eSPI.zip (GitHub)](https://github.com/andresima0/Help-ESP32/blob/main/displays/ILI9488_480X320/TFT_eSPI.zip)

   2.2. Na Arduino IDE, vá em **Sketch > Include Library > Add .ZIP Library…**  
   2.3. Selecione o arquivo `.zip` baixado.  
   2.4. Certifique-se de que a pasta tenha o nome `TFT_eSPI` dentro da pasta:  
   `Documents/Arduino/libraries/TFT_eSPI`

---

## 🧰 PlatformIO (VS Code)

1. Pelo `platformio.ini` (recomendado)
   1.1. No seu projeto, abra o arquivo `platformio.ini` e adicione:
   ```ini
   lib_deps =
     bodmer/TFT_eSPI
   ```

   1.2. Crie um arquivo customizado com suas configurações no caminho:  
   📁 `lib/TFT_eSPI/User_Setup.h`

   1.3. Copie o conteúdo do `User_Setup.h` personalizado para esse local:  
   🔗 [User_Setup.h (GitHub)](https://github.com/andresima0/Help-ESP32/blob/main/displays/ILI9488_480X320/User_Setup.h)

   > ✅ O PlatformIO dará prioridade para esse `User_Setup.h` da pasta `lib/` ao compilar.

2. Instalação manual via ZIP
   2.1. Baixe a biblioteca personalizada no link:  
   🔗 [TFT_eSPI.zip (GitHub)](https://github.com/andresima0/Help-ESP32/blob/main/displays/ILI9488_480X320/TFT_eSPI.zip)

   2.2. Extraia o conteúdo dentro da pasta do seu projeto, por exemplo:  
   📁 `lib/TFT_eSPI/`

   2.3. Certifique-se de que o `User_Setup.h` personalizado está incluído nessa pasta.

## 📌 Configuração de Pinos

Este display utiliza comunicação SPI tanto para o controle da imagem (Display) quanto para o touch (Touch Panel). Abaixo estão as conexões com um ESP32:

### 📺 Display

| Pino | Nome | ESP32 | Função |
|------|------|-------|--------|
| 1    | VDD  | VIN   | Alimentação (3V3 ou 5V) |
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
