# TCC-Ciencia-da-Computacao
Instruções para executar o código para uma instância, sem script:
- Abra o terminal dentro da pasta 'CG_source' execute a seguinte linha de comando:
- $ g++ bitMapGraph.cpp dimacsFile.cpp main.cpp
- Depois disso, execute a seguinte linha de comando:
- $ ./a.out ../InstanciasSinteticas/dimension2/br70L1/syntheticDim2_v104_d7_l1_br70-1.dat
- Este segundo caminho é o caminho da instância que será testada, deve-se mudar de acordo com a instância que desejar testar. Execute uma instância por vez.

Instruções para executar o código para um grupo de instâncias, com script:
- Abra o terminal dentro da pasta 'CG_source' execute a seguinte linha de comando:
- $ g++ bitMapGraph.cpp dimacsFile.cpp main.cpp
- Depois disso, execute as duas linhas de comando abaixo:
- $ cd ..
- $ ./ResultsGeneratorGCP.sh
- O primeiro comando sai da pasta 'CG_source'.
- O segundo comando executa o script para rodar o código para um grupo de instâncias, e um arquivo .csv é gerado na pasta 'TCC-Ciencia-da-Computacao'.
