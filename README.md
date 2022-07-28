# Trabalhos Práticos - Sistemas Operacionais

## TP01

Simulação, do que consiste um gerenciamento de processos em ambiente Linux. Para isso serão implementadas algumas funções, sendo as principais delas: (1) criação de processo; (2) substituição da imagem vigente no processo por uma imagem nova; e (3) realização de troca de contexto. Neste trabalho utilizaremos também quatro chamadas de sistema presentes no sistema operacional Linux, sendo elas:  (1) fork(); (2) wait(); (3) pipe(); e (4) sleep() 

![print_1](https://user-images.githubusercontent.com/45442173/177600599-bbe8dd19-236a-4d00-910b-ee9f5a7f534f.png)

## TP02
A demanda por mais memória e memórias mais rápidas capazes de armazenar e executar todos os programas desejados em multiprogramação ainda não são uma realidade barata nos dias atuais. Sendo assim, para lidar com adversidades de disponibilidade de espaço dos sistemas faz-se necessário a utilização de funções de gerenciamento de memória.
Para lidar com a alocação de processos neste trabalho, faremos uso de quatro diferentes técnicas quanto à escolha do local de reservar a memória, sendo elas: _first fit_, _next fit_, _best fit_ e _worst fit_.


### Memória Principal e Memória Virtual
![Captura de tela de 2022-07-28 15-17-32](https://user-images.githubusercontent.com/45442173/181613822-a5071ae8-3a6c-4c7d-b7a0-b981d249ca1a.png)


### Tabela de Processos modificada 
![Captura de tela de 2022-07-28 15-44-43](https://user-images.githubusercontent.com/45442173/181614580-5ac98cf3-d1ca-4bc0-9bf6-920f9d7ef18b.png)