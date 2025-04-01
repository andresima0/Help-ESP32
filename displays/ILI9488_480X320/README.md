# ILI9488 3.5" Display (480x320) with ESP32

This repository contains tested and verified examples for using the ILI9488 3.5" SPI display with an ESP32. If you are working with this model, follow the instructions below carefully to ensure correct setup and operation.

## ✅ Requirements

- ESP32 development board  
- ILI9488 3.5" TFT display (480x320, SPI interface)  
- Correct wiring between the display and ESP32, as described in the [Pin Configuration](#pin-configuration) section  
- `TFT_eSPI` library (exact version and configuration from this repository)

## ⚙️ Setup Instructions

1. Wire the hardware according to the pin configuration provided in this `README.md`.
2. Download and install the `TFT_eSPI` library:
   - **Option A (Recommended):** Use the version included in this repository to ensure full compatibility.
   - **Option B:** Download the official version from [Bodmer’s GitHub](https://github.com/Bodmer/TFT_eSPI) and **replace** the `User_Setup.h` file with the one provided here.

⚠️ **Important:** You must use the exact configuration provided. Any changes or missing files may prevent the display from working properly.

---

## 📘 Versão em Português

Este repositório contém exemplos testados e verificados para o uso do display ILI9488 3.5" SPI com ESP32. Se você estiver utilizando este modelo, siga atentamente as instruções abaixo para garantir uma montagem correta e o funcionamento adequado.

### ✅ Requisitos

- Placa de desenvolvimento ESP32  
- Display TFT ILI9488 3.5" (480x320, interface SPI)  
- Fiação correta entre os pinos do display e do ESP32, conforme a seção [Configuração de Pinos](#configuração-de-pinos)  
- Biblioteca `TFT_eSPI` (versão e configuração exatas deste repositório)

### ⚙️ Instruções de Instalação

1. Realize a conexão do hardware conforme a configuração de pinos descrita neste `README.md`.
2. Baixe e instale a biblioteca `TFT_eSPI`:
   - **Opção A (Recomendada):** Utilize a versão incluída neste repositório para garantir total compatibilidade.
   - **Opção B:** Baixe a versão oficial no [GitHub do Bodmer](https://github.com/Bodmer/TFT_eSPI) e **substitua** o arquivo `User_Setup.h` pelo fornecido aqui.

⚠️ **Importante:** É fundamental utilizar a configuração exata disponibilizada. Qualquer modificação ou ausência de arquivos pode impedir o funcionamento correto do display.

---
