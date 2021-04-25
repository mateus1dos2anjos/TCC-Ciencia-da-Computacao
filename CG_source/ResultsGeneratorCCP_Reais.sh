PASTA=/home/marcelo/TCC/tcc/CG_Instances/parkinsons/br70L1/*

for arquivo in $PASTA
do
	saida=$(./main "$arquivo")
	echo $saida >> resultadoRe_B70L1.txt
done

PASTA=/home/marcelo/TCC/tcc/CG_Instances/parkinsons/br70L2/*

for arquivo in $PASTA
do
	saida=$(./main "$arquivo")
	echo $saida >> resultadoRe_B70L2.txt
done

PASTA=/home/marcelo/TCC/tcc/CG_Instances/parkinsons/br70L3/*

for arquivo in $PASTA
do
	saida=$(./main "$arquivo")
	echo $saida >> resultadoRe_B70L3.txt
	done

	PASTA=/home/marcelo/TCC/tcc/CG_Instances/parkinsons/br70L4/*

	for arquivo in $PASTA
	do
		saida=$(./main "$arquivo")
		echo $saida >> resultadoRe_B70L4.txt
	done

	PASTA=/home/marcelo/TCC/tcc/CG_Instances/parkinsons/br70L5/*

	for arquivo in $PASTA
	do
		saida=$(./main "$arquivo")
		echo $saida >> resultadoRe_B70L5.txt
	done
	
