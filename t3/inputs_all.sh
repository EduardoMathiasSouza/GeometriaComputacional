#!/bin/bash


teste="Testes/"

pushd $teste

for file in entrada*.txt
do
    # monta resultado.txt
    echo -e "--------" > ${file:0:9}resultado.txt
    cat $file >> ${file:0:9}resultado.txt
    echo -e "\n--------" >> ${file:0:9}resultado.txt
    ./t3 < $file >> ${file:0:9}resultado.txt
    echo -e "--------" >> ${file:0:9}resultado.txt

    # monta o grafico
    python3 drawinput.py < $file

    # Atualiza nome do grafico
    mv  graph.png ${file:0:9}"_graph.png"

done

# Cria diretorio dos resultado
if [ ! -d "Resultados" ]; then
    mkdir "Resultados"
fi

# Move para pasta resultado
mv *graph* Resultados
mv *resultado.txt Resultados


popd