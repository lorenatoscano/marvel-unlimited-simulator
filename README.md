## Marvel Unlimited

Para essa semana, nós vamos implementar um programa que faça algumas funcionalidades básicas similares ao aplicativo Marvel Unlimited. Esse aplicativo, baseado em assinatura, dá acesso a todo conteúdo Marvel em formato digital (quadrinhos desde 1939 até hoje). Procurei um similar da DC mas não encontrei, porque a Marvel é melhor mesmo. Além de poder ler tudo que a Marvel já publicou, ele ainda provê várias funcionalidades de listagem e busca, para que você possa explorar o conteúdo do universo Marvel de acordo com sua vontade. Eu por exemplo, estou lendo tudo em ordem cronológica (estou em 1965, acho que dá pra acabar antes de me aposentar 0_0).

O aplicativo tem como principal elemento de informação os quadrinhos, que são representados pelas seguintes informações:

* Título/Série: o nome do quadrinho, que representa uma série ou tiragem de histórias. Ex: Espetacular Homem-Aranha, X-Men, Star Wars First Order, Vingadores, etc...

* Número:​ ordem do quadrinho na série. Ex: 1, 2 30, 40...;

* Data:​ mês e ano de publicação;

* Lido:​ marcação se o quadrinho já foi lido ou não pelo usuário;

* Personagens: ​ personagens da Marvel presentes no quadrinho. Ex: Em Tales to Astonish 67, aparecem Hulk, Gigante e Vespa.

Um quadrinho pode ser identificado de forma única pelo conjunto ​ Título + número (ou seja, essa combinação não se repetirá em dois quadrinhos distintos e pode ser considerada como elemento identificador de cada quadrinho).
Para essa atividade você vão fazer um programa que executa uma sequência de operações até que o usuário decida encerrar a execução. O seu programa terá um Menu principal com as seguintes opções:

1 - Carregar base de dados: carrega os dados previamente cadastrados de um
arquivo. Se o arquivo não existir, imprime uma mensagem “Base de dados vazia”, e
continua a operação do programa.

2 - Adicionar um quadrinho: recebe dados de um quadrinho fornecidos pelo
usuário e adiciona à base. O programa deve fazer uma verificação se o quadrinho já existe,
para que não sejam inseridos quadrinhos repetidos. O quadrinho deve ser inserido sem
apagar o conteúdo previamente existente na base de dados de quadrinho. Se o arquivo de
base não existir (estiver vazio), ele deve criar o arquivo e inserir o quadrinho. Todo
quadrinho adicionado tem o status lido como falso.

3 - Remover um quadrinho: recebe um título e um número de um quadrinho,
fornecido pelo usuário, e verifica se o quadrinho existe na base. Caso positivo, ele é
removido. Caso ele não exista, imprime uma mensagem informando o usuário que o
quadrinho não foi encontrado.

4 - Consulta um quadrinho: recebe um título e um número de um quadrinho,
fornecido pelo usuário, e verifica se ele existe na base. Caso positivo, imprime na tela todas
as informações do quadrinho. Caso não exista, imprime uma mensagem informando o
usuário que o quadrinho não foi encontrado.

5 - Consultas Gerais: abre um submenu de consultas para listagens gerais de
quadrinhos de acordo com algum filtro escolhido pelo usuário.

5.1 - Listar quadrinhos por ano: lista todos os quadrinhos que foram lançados em
determinado ano. Deve ser informado apenas um inteiro representando o ano a ser
consultado.

5.2 - Listar quadrinhos por período: lista todos os quadrinhos que foram lançados
entre um mês/ano inicial e um mês/ano final, sendo esses períodos informados pelo
usuário.

5.3 - Listar quadrinhos por personagem: lista todos os quadrinhos em que um
personagem específico aparece. O personagem é informado pelo usuário. Os quadrinhos
devem aparecer em ordem cronológica de lançamento.

5.4 - Listar quadrinhos por Série/Título: lista todos os quadrinhos existentes de
uma série/título específico. Ex: todos os quadrinhos do Espetacular Homem-Aranha.

5.5 - Listar quadrinhos lidos​ : listar todos os quadrinhos que o usuário já tiver
marcado como lido.

6 - Marcar como lido: deve alterar o status de um quadrinho para lido. O usuário
informará o título e número do quadrinho. Se ele existir, o status de lido dele deve ser
setado como verdadeiro. Se ele já for verdadeiro, deve ser impresso uma mensagem
“Quadrinho já marcado”. Se o quadrinho não for encontrado, imprimir uma mensagem
“Quadrinho não encontrado” para o usuário.

7 - Sair​ : finaliza o programa.