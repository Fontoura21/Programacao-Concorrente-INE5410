## Exercício 1

Um engenheiro escreveu o programa presente no arquivo main.c. Só o engenheiro sabe o que esse código faz, mas você pode observar que cada iteração do for é independente de todas as demais. Utilize OpenMP para paralelizar esse programa.

O programa lê o número de threads e o tamanho do vetor a ser calculado como argumentos de linha de comando. A implementação em OpenMP deve usar o número de threads indicado na variável n_threads. O programa também inclui uma medida do tempo gasto realizando o cálculo. Compute o speedup do seu programa executando-o com diferentes números de threads.

## Exercício 2

O programa fornecido inicializa duas matrizes quadradas com o tamanho fornecido como argumento de linha de comando e as multiplica. Esse programa foi paralelizado com OpenMP por um estagiário. O cliente ligou enfurecido para o suporte dizendo que o programa não está tão rápido quanto deveria, e que ele produz resultados incorretos. Arrume o(s) erro(s) cometido(s) pelo estagiário de modo que o cliente fique satisfeito. Além disso, pense se a configuração das diretivas usadas pelo estagiário pode ser modificada de forma a melhorar o desempenho da solução.

Uma vez resolvido o problema, explique para o estagiário o que ele fez de errado (texto fornecido direto no Moodle, durante a submissão). Seja didático, para que o estagiário compreenda o problema e não volte a cometer o mesmo erro...

## Exercício 3

O programa fornecido calcula o desvio padrão de uma sequência de números gerados aleatoriamente. O tamanho da sequência é lido como argumento da linha de comando. Paralelize a computação realizada pela função standard_deviation() usando OpenMP.
