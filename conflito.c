#include <stdio.h>
#include <stdlib.h>

typedef struct {
        int nv;
        int **m;
        int *grau;
        int *prox;
        int **res_busca;
} grafo;


const pai = 0;
const entr = 1;
const saida = 2;
const nivel = 3;


char **constroi_agendamento(char **atributos,int **transacoes,int *num_atributos,int *num_transacoes, int *num_linhas_lido, int num_escal)
{
	char **agendamento;
	int *transacao;
	char c = 'a';
	int pos, num_commit = 0;
	int tstamp, tran;
	int i = 0;
	char op, atrib, fim = 'n';

	tstamp = *num_atributos;// *num_atributos que veio da funcao verifica_seriabilidade() vai o primeiro elemento da linha(i.e. tstamp)
	*num_atributos = 0;
	transacao = NULL;
	agendamento = NULL;
	scanf("%d",&tran);
        scanf("%c",&op);
        scanf("%c",&c);
        scanf("%c",&op);
        scanf("%c",&atrib);
        (*num_linhas_lido)++;
        while(fim != 's')//Enquanto houver mais commits do mesmo agendamento
	{
	 while(c != 'C')
	 {
	  i = 0;
	  while(i < (*num_transacoes) && transacao[i] != tran)
	   i++;
	  if(i < (*num_transacoes))//a transacao jah realizou uma operacao antes
	  {
	   pos = i * 3;// a linha da transacao em questao dentro da matriz agendamento eh sempre o indice dessa transacao vezes 3(3 linhas por transacao)
	   (*transacoes)[i]++;// incrementa o numero de operacoes da transacao em questao
	   agendamento[pos] = (char *)realloc(agendamento[pos],(*transacoes)[i]*sizeof(char));
	   agendamento[pos+1] = (char *)realloc(agendamento[pos+1],(*transacoes)[i]*sizeof(char));
	   agendamento[pos+2] = (char *)realloc(agendamento[pos+2],(*transacoes)[i]*sizeof(char));
	   agendamento[pos][((*transacoes)[i]-1)] = c;
	   agendamento[pos+1][((*transacoes)[i]-1)] = atrib;
	   agendamento[pos+2][((*transacoes)[i]-1)] = (char)tstamp;
	  }
	  else
	  {
	    (*num_transacoes)++;
	    (*transacoes) = realloc((*transacoes),(*num_transacoes)* sizeof(char*));
	    (*transacoes)[((*num_transacoes)-1)] = 1;
	    transacao = realloc(transacao,(*num_transacoes)*sizeof(int));
	    transacao[(*num_transacoes)-1] = tran;
	    pos = ((*num_transacoes)-1)*3;
	    agendamento = realloc(agendamento,(*num_transacoes)* 3 *sizeof(char*));
	    agendamento[pos] = (char *)realloc(NULL,1 *sizeof(char));
	    agendamento[pos+1] = (char *)realloc(NULL,1 *sizeof(char));
	    agendamento[pos+2] = (char *)realloc(NULL,1 *sizeof(char));
	    agendamento[pos][0] = c;
	    agendamento[pos+1][0] = atrib;
	    agendamento[pos+2][0] = (char)tstamp;
	  }
	  i = 0;
	  while(i<(*num_atributos) && (*atributos)[i] != atrib)
	   i++;
	  if (i == (*num_atributos))// insere na lista de atributos um novo atributo
	  {
	   (*num_atributos)++;
	   (*atributos) = realloc((*atributos),(*num_atributos)*sizeof(int));
	   (*atributos)[(*num_atributos)-1] = atrib;
	  }
	  scanf("%c",&op);
	  scanf("%d",&tstamp);
          scanf("%d",&tran);
	  scanf("%c",&op);
          scanf("%c",&c);
	  scanf("%c",&op);
          scanf("%c",&atrib);
	  (*num_linhas_lido)++;// incrementa o numero de linhas lidos do arquivo de entrada
	 }
	 scanf("%c",&op);
	 num_commit++;
	 if(num_commit == (*num_transacoes))
	  fim = 's';
	 else
	 {
	  scanf("%d",&tstamp);
	  scanf("%d",&tran);
          scanf("%c",&op);
          scanf("%c",&c);
          scanf("%c",&op);
          scanf("%c",&atrib);
          (*num_linhas_lido)++;
	 }
        }
	printf("%d ",num_escal);
	for(i=0;i<(*num_transacoes);i++)
	 if(i==(*num_transacoes)-1)
	  printf("%d",transacao[i]);
	 else
	  printf("%d,",transacao[i]);
	return(agendamento);
}

int proximo_vizinho (grafo *G, int u)
{
        if ((G->prox[u]+1) < G->grau[u])
        {
         int proximo = G->m[u][++G->prox[u]];
         return proximo;
        }
        else return -1;
}

void busca_prof (grafo *G, int u, int *count, int *tem_ciclo)
{
        //visite u
        int v;

	G->res_busca[u][entr] = ++(*count);
        while ((v = proximo_vizinho(G,u)) != -1)
        {
         if (G->res_busca[v][entr] == 0) // entrada de v = 0 significa que v nao foi explorado
         {
          G->res_busca[v][pai] = u;
          G->res_busca[v][nivel] = G->res_busca[u][nivel] + 1;
          busca_prof(G,v,count,tem_ciclo);
         }
	 else// caso contrario, fecha ciclo
	  *tem_ciclo = 1;
        }
	if(v == -1)// significa que nao ha continuidade na busca  a partir do vertice 'v'
	 G->res_busca[u][entr] = 0;
        G->res_busca[u][saida] = ++(*count);
}

imprime(grafo *G)
{
        int i,j;

        for(i=0;i<G->nv;i++)
        {
         printf("\n %d     ",i);
         for(j=0;j<G->grau[i];j++)
          printf(",%d",G->m[i][j]);
         printf("\n");
        }
}


constroi_verifica_grafo(grafo *G, char **agendamento, char *atributos, int *transacoes, int num_atributos, int num_transacoes)
{
        int tem_ciclo = 0;
        char op, atributo;
        int i,j,k,t,p,tstamp;
	int count = 0;

	G->m = (int **)malloc(G->nv*sizeof(int*));
        for(i=0;i<G->nv;i++)
         G->m[i] = NULL;
        for(i=0;i<num_atributos && tem_ciclo == 0;i++)
        {
         atributo = atributos[i];
         for(j=0;j<(num_transacoes-1)*3;j=j+3)// Nao preciso testar a ultima transacao com as anteriores pois todas as anteriores ja testarao a ultima
         //j deve incrementar em 3 em 3
          for(k=0;k<transacoes[(j/3)];k++)// Enquanto k for menor do que o numero de operacoes na transacao j+1
           if(agendamento[j+1][k] == atributo)
           {
            op = agendamento[j][k];
            tstamp = (int)agendamento[j+2][k];
            if (op == 'R')
            {
             for(t=j+3;t<(num_transacoes*3);t=t+3)//t deve incrementar em 3 em 3
              for(p=0;p<transacoes[(t/3)];p++)
               if (agendamento[t][p] == 'W')
                if(agendamento[t+1][p] == atributo)
                 if(tstamp < (int)agendamento[t+2][p])// Parte aresta da transacao j/3 para a transacao t/3
                 {
                  G->grau[(j/3)]++;
		          G->m[(j/3)] = (int *)realloc(G->m[(j/3)],G->grau[(j/3)]*sizeof(int));
                  G->m[(j/3)][G->grau[(j/3)]-1] = (t/3);
                 }
                 else// parte aresta da transacao t/3 para a transacao j/3
                 {
                  G->grau[(t/3)]++;
		          G->m[(t/3)] = (int *)realloc(G->m[(t/3)],G->grau[(t/3)]*sizeof(int));
                  G->m[(t/3)][G->grau[(t/3)]-1] = (j/3);
                 }
             }
             else // Se a operacao eh 'W'
             {
              for(t=j+3;t<num_transacoes*3;t=t+3)//t deve incrementar em 3 em 3
               for(p=0;p<transacoes[(t/3)];p++)
                if (agendamento[t][p] == 'W' || 'R')//talvez nao precise desse teste ja que soh ha essas duas operacoes****
                 if(agendamento[t+1][p] == atributo)
                  if(tstamp < (int)agendamento[t+2][p])// Parte aresta da transacao j/3 para atransacao t/3
                  {
                   G->grau[(j/3)]++;
		           G->m[(j/3)] = (int *)realloc(G->m[(j/3)],G->grau[(j/3)]*sizeof(int));
                   G->m[(j/3)][G->grau[(j/3)]-1] = (t/3);
                  }
                  else
                  {
                   G->grau[(t/3)]++;
		           G->m[(t/3)] = (int *)realloc(G->m[(t/3)],G->grau[(t/3)]*sizeof(int));
                   G->m[(t/3)][G->grau[(t/3)]-1] = (j/3);
                  }
              }
             }
	   j = 0;
	   while(tem_ciclo == 0 && j < num_transacoes)//testa seriabilidade
	    {
	     busca_prof (G, j, &count, &tem_ciclo);
	     for(t=0;t<num_transacoes;t++)
	     {
	      count = 0;
	      G->res_busca[t][pai] = 0;
	      G->res_busca[t][nivel] = 0;
	      G->res_busca[t][entr] = 0;
	      G->res_busca[t][saida] = 0;
       	  G->prox[t] = -1;
       	 }
	     j++;
	    }
	//   imprime(G);
	   for (j=0;j<G->nv;j++)
            G->grau[j] = 0;
          }
	if(tem_ciclo == 1)
	 printf(" NAO\n");
	else
	 printf(" SIM\n");
}


verifica_seriabilidade(grafo *G, int *num_linhas_lido)
{
	int i, num_escalonamento, num_atributos, num_transacoes;
	char *atributos, *c;
    char **agendamento;
    int *transacoes;

	c = malloc(1 * sizeof(char));//para usar a funcao atoi()
	num_escalonamento = 0;
	while(scanf("%c",&c[0]) != EOF)
	{
	 if((*num_linhas_lido) >= 10)// se o numero de linhas lido ja passou de 9 entao o timestamp vale o que foi lido na variavel 'c' vezes 10 + o valor lido em num_atrib
         {
          scanf("%d",&num_atributos);
          num_atributos = num_atributos + 10 * atoi(c);
         }
         else
          num_atributos = atoi(c);// se o numero de linhas nao ultrapassou 9 entao o timestamp vale o valor lido em 'c'
	 agendamento = NULL;
	 transacoes = NULL;
	 atributos = NULL;
	 num_escalonamento++;
         agendamento = constroi_agendamento(&atributos,&transacoes,&num_atributos,&num_transacoes,num_linhas_lido,num_escalonamento);
         G->grau = malloc(sizeof(int) * num_transacoes);
         G->nv = num_transacoes;
         G->prox = malloc(sizeof(int) * G->nv);
	 for (i=0;i<G->nv;i++)
          G->grau[i] = 0;
         for(i=0;i<G->nv;i++)
          G->prox[i] = -1;
         G->res_busca = malloc(sizeof(int *) * G->nv);
         for (i=0;i<G->nv;i++)
          G->res_busca[i] = malloc(sizeof(int) * 4);
         for (i=0;i<G->nv;i++)
          G->res_busca[i][pai] = G->res_busca[i][entr] = G->res_busca[i][saida] = G->res_busca[i][nivel] = 0;
	 constroi_verifica_grafo(G,agendamento,atributos,transacoes,num_atributos,num_transacoes);
         num_atributos = 0;
         num_transacoes = 0;
         // libera estruturas usadas
	 free(transacoes);
	 free(atributos);
	 for(i=0;i<G->nv;i++)
	  free(G->m[i]);
	 free(G->m);
	 free(G->grau);
         free(G->prox);
         for(i=0;i<G->nv;i++)
          free(G->res_busca[i]);
         free(G->res_busca);
	 for(i=0;i<(num_transacoes)*3;i++)
	  free(agendamento[i]);
	 free(agendamento);
	}
}

int main()
{
	grafo G;
	int num_linhas_lido;

	num_linhas_lido = 0;
    verifica_seriabilidade(&G,&num_linhas_lido);
}
