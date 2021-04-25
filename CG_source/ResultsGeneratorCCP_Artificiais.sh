PASTA=/home/marcelo/TCC/tcc/InstanciasSinteticas/dimension2/br70L1/*

for arquivo in $PASTA
do
	saida=$(./main "$arquivo")
	echo $saida >> resultadoArt_d2B70L1.txt
done

PASTA=/home/marcelo/TCC/tcc/InstanciasSinteticas/dimension2/br70L5/*

for arquivo in $PASTA
do
	saida=$(./main "$arquivo")
	echo $saida >> resultadoArt_d2B70L5.txt
done

PASTA=/home/marcelo/TCC/tcc/InstanciasSinteticas/dimension2/br70L10/*

for arquivo in $PASTA
do
	saida=$(./main "$arquivo")
	echo $saida >> resultadoArt_d2B70L10.txt
done

PASTA=/home/marcelo/TCC/tcc/InstanciasSinteticas/dimension2/br70L20/*

for arquivo in $PASTA
do
	saida=$(./main "$arquivo")
	echo $saida >> resultadoArt_d2B70L20.txt
done

PASTA=/home/marcelo/TCC/tcc/InstanciasSinteticas/dimension2/br70L30/*

for arquivo in $PASTA
do
	saida=$(./main "$arquivo")
	echo $saida >> resultadoArt_d2B70L30.txt
done

PASTA=/home/marcelo/TCC/tcc/InstanciasSinteticas/dimension2/br70L35/*

for arquivo in $PASTA
do
	saida=$(./main "$arquivo")
	echo $saida >> resultadoArt_d2B70L35.txt
done

#acabou dimensão 2 agora começa dimensão 3

PASTA=/home/marcelo/TCC/tcc/InstanciasSinteticas/dimension3/br70L1/*

for arquivo in $PASTA
do
	saida=$(./main "$arquivo")
	echo $saida >> resultadoArt_d3B70L1.txt
done

PASTA=/home/marcelo/TCC/tcc/InstanciasSinteticas/dimension3/br70L5/*

for arquivo in $PASTA
do
	saida=$(./main "$arquivo")
	echo $saida >> resultadoArt_d3B70L5.txt
done

PASTA=/home/marcelo/TCC/tcc/InstanciasSinteticas/dimension3/br70L10/*

for arquivo in $PASTA
do
	saida=$(./main "$arquivo")
	echo $saida >> resultadoArt_d3B70L10.txt
done

PASTA=/home/marcelo/TCC/tcc/InstanciasSinteticas/dimension3/br70L20/*

for arquivo in $PASTA
do
	saida=$(./main "$arquivo")
	echo $saida >> resultadoArt_d3B70L20.txt
done

PASTA=/home/marcelo/TCC/tcc/InstanciasSinteticas/dimension3/br70L30/*

for arquivo in $PASTA
do
	saida=$(./main "$arquivo")
	echo $saida >> resultadoArt_d3B70L30.txt
done

PASTA=/home/marcelo/TCC/tcc/InstanciasSinteticas/dimension3/br70L35/*

for arquivo in $PASTA
do
	saida=$(./main "$arquivo")
	echo $saida >> resultadoArt_d3B70L35.txt
done
