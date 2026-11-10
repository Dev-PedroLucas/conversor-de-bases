 Conversor de Bases Numéricas
 
Trabalho da disciplina de **Arquitetura e Organização de Computadores**.

## Sobre o projeto
 
Computadores armazenam e processam toda a informação em binário, mas as pessoas trabalham em decimal e, em contextos como endereços de memória e depuração de programas, em hexadecimal. Este projeto é um conversor de bases numéricas em C++ que mostra, na prática, como um mesmo valor pode ser escrito em diferentes sistemas de numeração posicionais.
 
As conversões são implementadas manualmente, sem funções prontas da biblioteca padrão, para deixar visíveis os algoritmos usados: multiplicações sucessivas na leitura do número e divisões sucessivas na escrita do resultado. O programa roda no terminal: você escolhe a base de origem, a base de destino (ou todas de uma vez) e digita o número.
 
### Objetivos
 
- Compreender os sistemas de numeração posicionais e o peso de cada dígito de acordo com a sua posição.
- Praticar a conversão entre binário, octal, decimal, hexadecimal e base 36.
- Relacionar a representação numérica aos limites do hardware, como a largura da palavra e o overflow.
## Bases suportadas
 
| Opção | Base | Dígitos aceitos |
|-------|------|-----------------|
| 1 | Binário (2) | `0-1` |
| 2 | Octal (8) | `0-7` |
| 3 | Decimal (10) | `0-9` |
| 4 | Hexadecimal (16) | `0-9` e `A-F` |
| 5 | Base 36 | `0-9` e `A-Z` |
 
## Relação com Arquitetura e Organização de Computadores
 
- **Binário é a representação nativa do hardware.** Cada dígito é um bit, que corresponde ao estado de um circuito digital (0 ou 1).
- **Octal e hexadecimal são atalhos para o binário.** Como 8 = 2³ e 16 = 2⁴, cada dígito octal equivale a 3 bits e cada dígito hexadecimal a 4 bits. Um byte cabe em exatamente 2 dígitos hexadecimais, e por isso o hexadecimal é usado em endereços de memória e em dumps. Exemplo: `FF` (hex) = `1111 1111` (binário) = `255` (decimal).
- **Largura de palavra e overflow.** O programa trabalha com 64 bits sem sinal. Ultrapassar esse limite é análogo ao overflow em registradores de tamanho fixo, e por isso o programa detecta o problema antes de gerar um resultado errado.
- **Representação de sinal.** Números negativos são tratados como sinal e módulo (o `-` é guardado à parte). Os processadores atuais costumam usar complemento de dois, uma representação diferente, que fica como possível extensão do trabalho.
- **Base 36.** Não tem uso direto em hardware. Foi incluída para mostrar que os algoritmos funcionam para qualquer base, não só para as de uso comum.
## Funcionalidades
 
- Conversão entre qualquer par das 5 bases, ou para todas ao mesmo tempo.
- Aceita números negativos (`-FF`) e o sinal `+`.
- Aceita letras maiúsculas ou minúsculas (`ff` e `FF` são o mesmo número).
- Valida a entrada e informa qual dígito é inválido para a base escolhida.
- Detecta números grandes demais antes de gerar um resultado errado.
- Permite converter vários números sem reiniciar o programa.
## Requisitos
 
- Um compilador C++ com suporte ao padrão C++11 ou superior (por exemplo, `g++` ou `clang++`).
## Como compilar e executar
 
Abra o terminal na pasta do projeto e rode:
 
```bash
g++ -std=c++11 -o conversor conversor_bases.cpp
./conversor
```
 
No Windows, com MinGW/g++:
 
```bash
g++ -std=c++11 -o conversor.exe conversor_bases.cpp
conversor
```
 
## Exemplo de uso
 
```text
=== CONVERSOR DE BASES ===
 
Base de ORIGEM:
  1 - Binario (base 2)
  2 - Octal (base 8)
  3 - Decimal (base 10)
  4 - Hexadecimal (base 16)
  5 - Base 36 (0-9 e A-Z)
Escolha (1-5): 3
 
Base de DESTINO:
  1 - Binario (base 2)
  2 - Octal (base 8)
  3 - Decimal (base 10)
  4 - Hexadecimal (base 16)
  5 - Base 36 (0-9 e A-Z)
  0 - Todas as bases
Escolha (0-5): 0
 
Digite o numero em Decimal (base 10): 255
 
Resultado:
  Binario (base 2): 11111111
  Octal (base 8): 377
  Decimal (base 10): 255
  Hexadecimal (base 16): FF
  Base 36 (0-9 e A-Z): 73
 
Converter outro numero? (1 = sim, 0 = sair)
Escolha: 0
Ate mais!
```

Feito por: Pedro Lucas Ferreira Marques.
