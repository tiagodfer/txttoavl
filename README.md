# txttoavl

## changelog

### 1.2.3
- destroi AVL do relatório a cada operação requisitada, para evitar que o programa fique sem memória.

### 1.2.2
- variáveis renomeadas para melhor legibilidade do código;
- usa uma AVL, e não uma ABP como a versão anterior, para a função CONTADOR_AVL.

### 1.2.1
- documentação mais detalhada do código.

### 1.2.0
- otimização na função CONTADOR_AVL evita que se percorra a árvore em vão quando se busca uma frequência a qual nenhuma palavra na AVL tem.

### 1.1.0
- não cria mais arquivo temporário, dispensando algumas etapas na criação do relatório e corrige bugs.

### 1.0.0
- passa as palavras do texto para uma AVL de strings, efetua as operações passadas e emite um relatório com o resultado das operações.
