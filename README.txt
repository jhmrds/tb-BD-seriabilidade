Autoria:
    Gustavo T. Komura     GRR20102342
    Weyne C. Pietniczka   GRR20105501

README:

Descricao do algoritmo:

Ideia do algoritmo:
Primeiro o algoritmo le do arquivo da entrada padrao ate a primeira operacao commit e constroi o agendamento. Depois com base no agendamento ele constroi um grafo, representado por uma lista de adjacentes, e verifica a seriabilidade, para cada atributo diferente. Todo esse processo se repete ate que todos os agendamentos presentes no arquivo sejam testados.
    O programa apresenta 5 funcoes que serao descritas a seguir:
     - constroi_agendamento(): Ele comeca lendo a primeira linha do arquivo e com base nos dados lidos, constroi-se o agendamento da seguinte forma: com base no identificador da transacao lido ha duas possibilidades: se a transacao nao estiver incluida no agendamento faz-se a inclusao da seguinte forma: reserva-se 3 linhas a partir da ultima transacao que esta no agendamento. Na primeira linha armazena-se na primeira coluna a operacao realizada no momento. Na segunda linha armazena-se na primeira coluna o atributo afetado pela operacao. Na terceira linha adiciona-se o timestamp da operacao. Se a transacao ja estiver incluida, com base no identificador dela multiplicado por 3 acessa-se a linha resultante na matriz agendamento e reserva-se a proxima coluna a partir da ultima utilizada e adiciona-se na linha resultante a operacao, na (linha resultante + 1) o atributo e na (linha resultante + 2) o timestamp. Todo esse processo se repete ate a leitura do primeiro commit.
     - proximo_vizinho(): Dado um vertice do grafo ela retorna o proximo vizinho.
     - busca_prof(): Realiza uma busca em profundidade em um grafo com o objetivo de encontrar ciclo (teste de seriabilidade).
     - constroi_verifica_grafo(): Com base no agendamento recem construido essa funcao constroi o grafo atraves do algoritmo de teste de seriabilidade por conflito visto em sala de aula, brevemente descrito a seguir:
        1 - Cria-se um vertice para cada transacao T do agendamento.
        2 - Aresta Ti -> Tj, para cada r(x) em Tj depois de w(x) em Ti.
        3 - Aresta Ti -> Tj, para cada w(x) em Tj depois de r(x) em Ti.
        4 - Aresta Ti -> Tj, para cada w(x) em Tj depois de w(x) em Ti.
       Com o grafo construido essa funcao ainda testa a seriabilidade chamando a funcao busca_prof().
     - verifica_seriabilidade(): Essa funcao esta responsavel por realizar o teste de seriabilidade em cada agendamento lido do arquivo. Isto eh feito por meio da chamada das funcoes constroi_agendamento() e constroi_verifica_grafo() enquanto o arquivo nao for totalmente lido, isto eh, enquanto nao encontrarmos a constante EOF.

