#FILES=/home/mateus/Documentos/TCC2/AlgoritmoProbabilistico/InstanciasSinteticas2/br70L1/*.dat
#for f in $FILES
#do
#    timeout 3600s /home/mateus/Documentos/TCC2/AlgoritmoProbabilistico/CG_source/./a.out $f >> GCP_I2_br70L1_Results.txt
#    echo >> GCP_I2_br70L1_Results.txt
#done



# Para cada instância, rodar 10 vezes cada uma
#
echo "Nome da Instância; Valor da Solução; Acurácia; Tempo" >> GCP_graph_br90-1e2L1_Results.csv
max=10
FILES=/home/mateus/Documentos/TCC2/AlgoritmoProbabilistico/InstanciasNovas/*.dat
for f in $FILES
do
for i in `seq 1 $max`
do
    timeout 3600s /home/mateus/Documentos/TCC2/AlgoritmoProbabilistico/CG_source/./a.out $f >> GCP_graph_br90-1e2L1_Results.csv
done
    echo >> GCP_graph_br90-1e2L1_Results.csv
done



# Rodar cada instânia somente uma vez
#
#echo "Nome da Instância; Valor da solução; Acurácia; Tempo" >> GCP_spect_br70L1_Results.csv
#FILES=/home/mateus/Documentos/TCC2/AlgoritmoProbabilistico/CG_Instances/SPECTF_Heart_Data/br70L1/*.dat
#for f in $FILES
#do
#    timeout 3600s /home/mateus/Documentos/TCC2/AlgoritmoProbabilistico/CG_source/./a.out $f >> GCP_spect_br70L1_Results.csv
#    >> GCP_spect_br70L1_Results.csv
#done



#max=5
#for f in $FILES
#do
#for i in `seq 1 $max`
#...

#FILES=/home/phmacedoaraujo/workspace/GCP/instances/experiments/*.wei
#for f in $FILES
#do
#    timeout 3600s /home/phmacedoaraujo/workspace/GCP/ILP3/./gcp $f >> GCP_ILP3_Results.txt
#    echo >> GCP_ILP3_Results.txt
#done



