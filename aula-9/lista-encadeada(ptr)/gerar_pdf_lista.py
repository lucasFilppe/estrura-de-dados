from fpdf import FPDF

class PDF(FPDF):
    def header(self):
        # Fonte do título: Arial bold 14
        self.set_font('Arial', 'B', 14)
        # Título centralizado
        self.cell(0, 10, 'Resumo: Lista Encadeada (Com Ponteiros)', ln=True, align='C')
        self.ln(5)

    def footer(self):
        # Posição a 1.5 cm do fim
        self.set_y(-15)
        # Fonte do rodapé: Arial italic 8
        self.set_font('Arial', 'I', 8)
        # Número da página
        self.cell(0, 10, f'Pagina {self.page_no()}', 0, 0, 'C')

    def chapter_title(self, title):
        # Fonte para os títulos das seções
        self.set_font('Arial', 'B', 12)
        # Cor de fundo (cinza claro)
        self.set_fill_color(230, 230, 230)
        self.cell(0, 8, title, 0, 1, 'L', fill=True)
        self.ln(2)

    def chapter_body(self, text):
        # Fonte para o corpo do texto
        self.set_font('Arial', '', 11)
        # Texto com quebra de linha automática
        self.multi_cell(0, 6, text)
        self.ln(5)

# Criando o objeto PDF
pdf = PDF()
pdf.add_page()
pdf.set_auto_page_break(auto=True, margin=15)

# Introdução
pdf.set_font('Arial', 'I', 11)
intro = "Este documento resume a complexidade e logica das funcoes implementadas para uma Lista Simplesmente Encadeada (baseada em nos/celulas alocados dinamicamente na Heap)."
pdf.multi_cell(0, 6, intro)
pdf.ln(5)

# Seção 1
pdf.chapter_title('1. Gestao da Lista')
pdf.chapter_body(
    "ListaCria: O(1)\n"
    "Aloca a struct de controle (prancheta) e a Celula Cabeca (Sentinela).\n\n"
    "ListaDestroi: O(n)\n"
    "Diferente do vetor, exige percorrer TODOS os nos dando 'free' um por um antes de liberar a struct.\n\n"
    "ListaTamanho: O(1)\n"
    "Acesso direto a variavel 'quantidadeElementos' na struct.\n\n"
    "ListaEhVazia: O(1)\n"
    "Comparacao simples (quantidade == 0 ou cabeca->proximo == NULL)."
)

# Seção 2
pdf.chapter_title('2. Insercao (A Danca dos Ponteiros)')
pdf.chapter_body(
    "Obs: Em listas encadeadas nao ha deslocamento fisico (shift). Apenas mudamos para onde as setas apontam.\n\n"
    "InsereInicio: O(1)\n"
    "Melhor Caso. A Celula Cabeca facilita. O novo no aponta pro primeiro, a Cabeca aponta pro novo.\n\n"
    "InsereMeio: O(n)\n"
    "Pior Caso. O 'cursor' precisa caminhar (for) ate achar a celula *anterior* ao ponto de insercao.\n\n"
    "InsereFim: O(1)\n"
    "Melhor Caso. Vai direto ao final usando o ponteiro 'celulaUltima' da struct e engata o novo no."
)

# Seção 3
pdf.chapter_title('3. Remocao')
pdf.chapter_body(
    "RemoveInicio: O(1)\n"
    "Melhor Caso. A Celula Cabeca faz o bypass (desvio), pulando o primeiro elemento, que recebe free.\n\n"
    "RemoveMeio: O(n)\n"
    "Precisa caminhar (for) para achar a celula *anterior* a vitima para fazer o bypass.\n\n"
    "RemoveFim: O(n)\n"
    "Pior Caso (O Gargalo!). A lista so vai pra frente. Para remover o ultimo, e preciso varrer TODA a lista desde o inicio para encontrar o *penultimo* e faze-lo apontar para NULL."
)

# Seção 4
pdf.chapter_title('4. Acesso e Busca')
pdf.chapter_body(
    "ListaGet: O(n)\n"
    "Nao ha acesso direto por indice (como no vetor [i]). Precisa pular de no em no seguindo o '->proximo' ate a posicao desejada.\n\n"
    "ListaPesquisa: O(n)\n"
    "Busca Linear. Percorre os nos um a um ate achar o valor correspondente.\n\n"
    "ListaPrint: O(n)\n"
    "Percorre toda a corrente de ponteiros do inicio ao fim para imprimir."
)

# Regra de Ouro (Destaque)
pdf.set_font('Arial', 'B', 11)
pdf.cell(0, 8, 'Regra de Ouro para a Prova:', 0, 1)
pdf.set_font('Arial', '', 11)
pdf.chapter_body(
    "- Inseriu no Inicio ou Fim? Rapido O(1) (Garantido pela Sentinela e pelo ponteiro Ultimo).\n"
    "- Removeu no Inicio? Rapido O(1).\n"
    "- Removeu no Fim? Lento O(n) (Precisa achar o penultimo caminhando tudo).\n"
    "- Quer acessar um Indice (ListaGet)? Lento O(n) (Nao tem colchetes, tem que andar a pe)."
)

# Gerar o arquivo
pdf.output('Resumo_Lista_Encadeada.pdf')
print("PDF 'Resumo_Lista_Encadeada.pdf' gerado com sucesso!")