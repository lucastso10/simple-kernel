# simple-kernel
Um kernel simples feito em c++.

Esse programa utiliza a biblioteca `filesystem` que é uma biblioteca experimental do c++, para compilar esse programa corretamente utlize esses argumentos no g++:

`$ g++ -std=c++17 main.cpp -lstdc++fs`

## O que ele faz?

Quando você executar esse programa pelo terminal o primeiro argumento será o diretorio root desse kernel, da ai vocẽ pode criar arquivos pastas, criar pastas, deletar arquivos, navegar por pastas e listar os diretorios.

Os comando para isso são:

`m - criar diretório/arquivo`

`c - mudar diretório atual`

`d - remover um arquivo`

`l - listar diretorio`

o comando `m` precisa de 2 argumentos, o primeiro seria o que vocẽ deseja criar, digite `d` para criar um diretório e `a` para criar um arquivo, o segundo argumento seria o nome do diretório/arquivo. Exemplo:

`>> m d pasta`


