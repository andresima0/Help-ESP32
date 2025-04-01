## Pin Configuration - ILI9488 3.5" Display with Touch (480x320 pixels)

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

---

### ℹ️ Notes

- The ILI9488 display can operate with **3.3V or 5V**, depending on the model.
- **BL (Backlight)** can be controlled with PWM to adjust brightness.
- Make sure signal levels are compatible with ESP32's **3.3V logic**.
- You may need pull-up/pull-down resistors on the **PEN** (IRQ) pin.

### Portuguese version

## Configuração de Pinos - Display ILI9488 3.5" com Touch (480x320 pixels)

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

---

### ℹ️ Observações

- O display ILI9488 pode operar com alimentação de **3V3 ou 5V**, verifique o modelo.
- O **BL (Backlight)** pode ser controlado com PWM para ajuste de brilho.
- Certifique-se de que os níveis de sinal sejam compatíveis com 3V3 do ESP32.
- Utilize resistores de pull-up/pull-down se necessário no pino **PEN** (IRQ).

