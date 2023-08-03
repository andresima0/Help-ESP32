# PinOut

### "Pinos Proibidos"
O ESP32 possui alguns pinos que têm funções especiais ou são reservados para usos específicos. Esses pinos são conhecidos como "pinos proibidos" ou "pinos reservados". Ao desenvolver projetos com o ESP32, é importante estar ciente desses pinos e evitá-los para evitar conflitos ou problemas.

Aqui estão alguns dos pinos proibidos ou reservados no ESP32:

1. **Pinos GPIO 6 a 11:** Esses pinos são usados para a comunicação SPI interna. Se forem usados ​​incorretamente, podem interferir na comunicação SPI do ESP32.

2. **Pinos GPIO 34 a 39:** Esses pinos estão conectados à memória flash SPI interna do ESP32. Qualquer interferência nesses pinos pode afetar a operação da memória flash.

3. **Pinos GPIO 0 e 2:** Esses pinos estão envolvidos no processo de inicialização do ESP32 e também são usados para o upload de firmware. Ao fazer upload de um novo programa, é importante não conectar nenhum componente externo a esses pinos.

4. **Pinos de alimentação e terra:** Alguns pinos são projetados apenas para alimentação (VCC ou GND) e não devem ser usados como pinos de entrada ou saída.

5. **Pinos de cristal:** Os pinos GPIO 0, 2, 4, 12 a 15 e 25 a 27 também têm funções relacionadas a osciladores de cristal e devem ser tratados com cuidado.

É altamente recomendado consultar a documentação oficial do ESP32 ou o datasheet para obter informações detalhadas sobre os pinos proibidos e suas funções. Certifique-se de escolher os pinos adequados para o seu projeto e evite usar os pinos proibidos, a menos que você esteja ciente de suas funções e restrições.

Sempre verifique as informações mais recentes, pois as especificações podem mudar com atualizações de firmware ou revisões do ESP32.
