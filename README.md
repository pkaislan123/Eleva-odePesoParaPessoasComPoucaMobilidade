# Eleva-odePesoParaPessoasComPoucaMobilidade


Projeto para montagem de Elevação de Peso para Pessoas com Mobilidade Reduzida


O projeto a seguir utiliza de componentes do universo Arduino (IOT em geral) para ser usado no controle de movimento de um motor DC.


Para se montar o projeto é necessário

-> 1 x Arduino Nano

-> 3 x PushButtons (3 unidades para cada local de acionamento)

-> 2 x Chaves Fim de Curso

-> 1 x Módulo Ponte H L293D ou Similar (Verificar a potencia do motor)

-> 1 x Fonte 5v para alimentar o Arduino Nano e o Módulo L293D

-> 1 x Fonte de alimentação para o Motor

-> 1 x Motor DC

Funcionamento:

Resumo:
  O código implementa o controle de um motor usando um Arduino Nano e um driver L293D, 
  juntamente com três botões (SUBIR, DESCER e PARADA) 
  e duas chaves fim de curso (CIMA e BAIXO). 
  
  O objetivo do código é permitir que o motor se mova nos sentidos de subida e descida apenas se as condições corretas forem atendidas, 
  ou seja, o botão correspondente estiver pressionado e a chave fim de curso oposta estiver em estado HIGH. 
  Além disso, o motor é interrompido imediatamente se o botão de parada for acionado ou quando atingir uma das chaves fim de curso. 
  O status do sistema é exibido no monitor serial para fins de depuração e simulação. 
  O código também incorpora uma função de segurança que desliga o motor caso ocorra uma mudança inesperada no estado das chaves fim de curso durante o movimento.

<p align="center">
  <img src=https://raw.githubusercontent.com/pkaislan123/Eleva-odePesoParaPessoasComPoucaMobilidade/main/Simula%C3%A7%C3%A3o_Eleva_Cesto.png title="hover text">
</p>
