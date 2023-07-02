#!/bin/bash
gen=gen-rangetree-1d
sol=rangetree-1d
brute=rangetree-1d-brute
for ((i=1; ; i++)) do
    ./$gen $i > in
    ./$sol < in > out
    ./$brute < in > out2
    if (! cmp -s out out2) then
        echo "--> entrada:"; cat in
        echo "--> saida obtida:"; cat out
        echo "--> saida esperada:";cat out2
        break;
    fi
    echo $i
done
