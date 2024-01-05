# Fire Sensor Sensor

## Descrição
O Fire Sensor Sensor é uma aplicação desenvolvida em C++ para validar a saída de um sensor de fogo a cada segundo. A aplicação verifica se há presença de fogo e, em caso positivo, retorna essa informação para uma página web indicando um possível incêndio. Além disso, o sistema conta com um sensor adicional de temperatura e umidade que reporta constantemente os dados ao ThinkSpeak, oferecendo uma monitoração completa do ambiente.

## Tecnologias Utilizadas
[![My Skills](https://skillicons.dev/icons?i=arduino,cpp)](https://skillicons.dev)
- **ThinkSpeak**: Plataforma para coleta, análise e visualização de dados IoT.

## Compilação e Execução
Certifique-se de ter um compilador C++ disponível em seu ambiente. Em seguida, siga os passos abaixo:

1. Clone este repositório:
   ```bash
   git clone https://github.com/vsenadev/fire-sensor-sensor.git
   cd fire-sensor-sensor
   ```

2. Compile o código-fonte:
   ```bash
   g++ main.cpp -o fire-sensor
   ```

3. Execute o programa:
   ```bash
   ./fire-sensor
   ```

## Configuração
Antes de executar o programa, certifique-se de configurar as opções adequadas no código-fonte ou através de um arquivo de configuração, como a URL da página web para reportar a presença de fogo e as credenciais do ThinkSpeak para enviar os dados de temperatura e umidade.

## Uso
- A aplicação executa uma verificação contínua da saída do sensor de fogo.
- Em caso de detecção de fogo, a informação é enviada para a página web configurada.
- Os dados de temperatura e umidade são enviados constantemente para o ThinkSpeak para monitoramento remoto.

## Contribuição
Sinta-se à vontade para contribuir com melhorias, correções de bugs ou novos recursos. Basta seguir os passos mencionados no README ou abrir issues para discussões.

## Licença
Este projeto está licenciado sob a [MIT License](LICENSE).
