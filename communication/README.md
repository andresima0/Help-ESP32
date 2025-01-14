
# SCALE SIMULATOR

Simulador de balança utilizando ESP32, projetado para gerar dados randômicos de peso, permitindo o teste de dispositivos de leitura de balanças na ausência de um equipamento físico.

---

## 📋 Funcionalidades

O **SCALE SIMULATOR** opera como uma balança simulada, enviando dados conforme solicitado por um dispositivo externo. Ele utiliza um protocolo de comunicação simples e eficiente:

1. **Protocolo de Comunicação:**
   - **Configurações:**
     - 1 Stop Bit;
     - 8 Bits de dados;
     - Sem paridade.
   - **Comando de solicitação:** 
     - O dispositivo externo deve enviar o comando `ENQ` (ASCII 05H ou 0x05) para iniciar a transmissão.
   - **Pacote de Dados Enviado:** 
     ```
     [STX][PPPPP][ETX]
     ```
     - `STX` (02H ou 0x02): Início da transmissão.
     - `PPPPP`: Peso em gramas, representado por 5 caracteres ASCII (sem ponto decimal).
     - `ETX` (03H ou 0x03): Término da transmissão.

---

## ⚙️ Conexões

Configure as conexões conforme o esquema abaixo:

| **ESP32 SCALE SIMULATOR** | **Dispositivo Externo (Outro ESP32)** |
|----------------------------|---------------------------------------|
| RX (16)                   | TX (17)                              |
| TX (17)                   | RX (16)                              |
| GND                       | GND                                  |

### 🔑 Observações Importantes:
- Certifique-se de conectar todos os dispositivos ao mesmo **GND**.
- Para usar uma balança real, é necessário incluir um módulo **RS232** para conversão TTL serial.

---

## 🚀 Como Usar

1. Conecte os dispositivos conforme descrito na seção de conexões.
2. Programe o dispositivo externo para enviar o comando `ENQ`.
3. O SCALE SIMULATOR responderá com o peso simulado no formato especificado.

---

## 🛠️ Requisitos

- **Hardware Necessário:**
  - ESP32 para o simulador.
  - Dispositivo externo com comunicação serial (outro ESP32, microcontrolador ou computador).
  - Módulo RS232 (caso utilize uma balança real).
