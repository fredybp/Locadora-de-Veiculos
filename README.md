# Sistema de um gerenciamento de uma pequena locadora de veículos

<br> Visão geral sobre o funcionamento do programa: </b> </br> 
Nesse programa utilizamos duas listas ligadas. Uma referente aos carros, que serão inseridos, removidos, alugados etc., contendo data, hora, marca, modelo, chassis, a quilometragem e por ultimo um ponteiro para o proximo carro a ser inserido. E a outra, referente aos clientes; armazenando informações sobre o nome, código, um ponteiro para os carros alugados de um determinado cliente e um ponteiro para o proximo cliente. 

No programa temos um menu principal com 19 opções a serem escolhida pelo usuário. 
A primeira opção se refere a inserção de carros, adicionando o novo carro sempre no começo da lista. 
A segunda opção, à remoção de um determinado carro escolhido pelo usuário. 
A terceira opção é a inserção de um novo cliente, e em seguida a remoção de um cliente escolhido. 
A quinta e sexta posições são responsáveis pela alteração das informações de carros e de clientes cadastrados respectivamente.
As opções sétima e oitava são referentes a locação e devolução de um carro por um cliente, sendo que no ato da devolução realizaremos o calculo sobre a quantidade de combustivel que será cobrada ou não, caso o carro esteja com o tanque cheio. 
Na opção nove pedimos para que o usuário digite o código de um cliente para que seja impressa a lista de veículos alugados por ele.
Na decima opção, imprimimos a lista de carros disponíveis na locadora, ou seja, os carros que não foram locados por nenhum cliente. 
Na opção onze imprimimos todos os clientes cadastrados e junto todos os carros locados por cada um deles. 
Na decima segunda opção, imprimimos a quantidade de carros locados, e o valor da conta de um cliente selecionado.
Na decima terceira, permitimos que o usuário navegue pelos registros dos clientes, utilizando para isso teclas do teclado, determinadas pelo programa. 
Em seguida temos a opção referente a navegaçāo pelos registros dos carros, da mesma forma da opção anterior. Na opção 15, o usuário será capaz de escolher entre as opções de cores exibidas pelo programa, a cor de texto e cor de fundo que deseja. Na opção seguinte permitimos a recuperação de um cliente que foi apagado pelo usuário.
Em seguida, opções 17 e 18,  sāo referente a leitura e gravaçāo dos dados armazenados em um arquivo. 
E por último temos a opção 99, referente à saída do programa.

Em algumas opções do programa, como as de alteração de cliente e carros, utilizamos a posição da lista ligada para que seja escolhida a informação necessária para a realização de determinada função. Em outras funções escolhemos, por exemplo, o chassi do carro ou o código do cliente, deixando isso claro na mensagem de exibição. No ato da gravação das informações armazenadas em um arquivo .txt, o programa grava um codigo indificador na frente, sendo o numero 1 como gravaçao de um carro, numero 2 de um cliente e o numero 3 um carro alugado por um cliente
