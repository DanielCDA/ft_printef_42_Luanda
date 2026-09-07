*This project has been created as part of the 42 curriculum by danagost.*

# ft_printf

## Description

`ft_printf` é uma reimplementação da função `printf()` da libc, empacotada como uma
biblioteca estática (`libftprintf.a`). O objetivo do projeto é entender e recriar o
comportamento de uma função variádica clássica sem depender do `printf` original nem
do seu gerenciamento interno de buffer.

A função implementada segue exatamente o protótipo pedido pelo enunciado:

```c
int ft_printf(const char *format, ...);
```

e suporta as seguintes conversões obrigatórias:

| Conversão | Descrição |
|---|---|
| `%c` | Caractere único |
| `%s` | String (trata `NULL` como `(null)`) |
| `%p` | Ponteiro `void *` em hexadecimal (`0x...`, trata `NULL` como `(nil)`) |
| `%d` / `%i` | Número inteiro em base 10, incluindo `INT_MIN` |
| `%u` | Número inteiro sem sinal em base 10 |
| `%x` | Hexadecimal minúsculo |
| `%X` | Hexadecimal maiúsculo |
| `%%` | Sinal de percentagem literal |

O valor de retorno é o número de caracteres efetivamente escritos, igual ao `printf`
original.

## Instructions

### Compilar a biblioteca

```bash
make
```

Isso gera `libftprintf.a` na raiz do repositório.

Outras regras disponíveis:

```bash
make clean   # remove os .o
make fclean  # remove os .o e a lib
make re      # fclean + all
```

### Usar a biblioteca no seu projeto

```bash
cc seu_programa.c -L. -lftprintf -o seu_programa
```

Certifique-se de incluir o header:

```c
#include "ft_printf.h"
```

## Resources

- [man 3 printf](https://man7.org/linux/man-pages/man3/printf.3.html) — especificação oficial das conversões e do valor de retorno.
- [cppreference — Variadic functions](https://en.cppreference.com/w/c/variadic) — referência sobre `va_list`, `va_start`, `va_arg` e `va_end`.
- Documentação da 42 (`printf.pdf`, versão 12.1) — enunciado oficial do projeto.

### Uso de IA

A IA (Claude, da Anthropic) foi usada como ferramenta de **revisão e depuração**
depois que a implementação inicial já estava escrita, nunca para gerar a solução do
zero. Uso concreto, por etapa:

- **Revisão de conformidade com o enunciado**: conferência do nome do header
  (`ft_printf.h`), da lista de conversões exigidas e das regras do Makefile
  (`$(NAME)`, `all`, `clean`, `fclean`, `re`, uso do `ar`).
- **Detecção de bugs por meio de testes e ferramentas de análise**: comparação
  automatizada da saída e do valor de retorno de `ft_printf` contra o `printf` real
  da libc em casos de borda (`NULL`, `INT_MIN`, `%` no fim da string, string vazia),
  e uso do AddressSanitizer para confirmar uma leitura fora dos limites do buffer
  que existia na função principal.
- **Explicação de conceitos**: entendimento de por que passar `va_list` por valor
  entre funções é comportamento indefinido pelo padrão C (mesmo funcionando na
  ABI x86-64 do Linux), e por que usar `va_list *` é a forma portável e correta.
- **Revisão de Norma**: identificação de espaços indevidos antes de parênteses em
  chamadas de função.

Todas as correções foram entendidas e aplicadas manualmente no código antes de
seguir para a próxima etapa.

## Technical choices

**Estrutura do código**: a lógica foi dividida em uma função de laço principal
(`ft_printf`), uma função de despacho que identifica o especificador de conversão
(`ft_check_specifier`) e um arquivo `.c` por conversão (`ft_putchar_fd`,
`ft_putstrn_fd`, `ft_putptr_fd`, `ft_putnbrint_fd`, `ft_putnbr_unsigned_fd`,
`ft_puthex_fd`). Essa separação mantém cada função pequena e dentro do limite de
linhas da Norma, além de deixar o código extensível: adicionar uma nova conversão
significa criar um novo arquivo e uma nova linha no despacho, sem tocar no resto.

**Estrutura de dados**: não há estrutura de dados dinâmica — o projeto não aloca
memória em nenhum momento (`malloc`/`free` não são usados), já que todas as
conversões exigidas podem ser escritas caractere a caractere diretamente com
`write` (via `ft_putchar_fd`), sem precisar montar a string completa em um buffer
intermediário. Números (`%d`, `%u`, `%x`, `%X`, `%p`) são convertidos com recursão:
a função escreve primeiro os dígitos mais significativos (chamando a si mesma com
`n / base`) e só depois escreve o dígito atual (`n % base`), o que resolve a ordem
correta dos dígitos sem precisar de um array auxiliar.

**Ponteiro para `va_list`**: `va_list` é repassado por ponteiro (`va_list *args`)
entre `ft_printf` e `ft_check_specifier`, em vez de por valor. Isso garante que o
avanço do cursor de argumentos variádicos feito dentro de `ft_check_specifier` seja
visível de volta em `ft_printf`, independentemente de como o compilador implementa
`va_list` internamente (passar por valor funciona por acaso em algumas ABIs, mas é
comportamento indefinido pelo padrão C).