from fpdf import FPDF

class PDF(FPDF):
    def header(self):
        self.set_font('Arial', 'B', 16)
        self.cell(0, 10, 'Resumo: Lista Sequencial (Vetor)', 0, 1, 'C')
        self.ln(10)

    def footer(self):
        self.set_y(-15)
        self.set_font('Arial', 'I', 8)
        self.cell(0, 10, f'Pagina {self.page_no()}', 0, 0, 'C')

    def chapter_title(self, title):
        self.set_font('Arial', 'B', 12)
        self.set_fill_color(200, 220, 255)
        self.cell(0, 6, title, 0, 1, 'L', 1)
        self.ln(4)

    def function_row(self, func_name, cost, description):
        self.set_font('Arial', 'B', 10)
        self.cell(40, 6, func_name, 0, 0)
        self.set_font('Arial', 'B', 10)
        # Colorir o custo: Vermelho para O(n), Verde para O(1)
        if 'O(n)' in cost:
            self.set_text_color(200, 0, 0)
        else:
            self.set_text_color(0, 150, 0)
        self.cell(20, 6, cost, 0, 0)
        self.set_text_color(0, 0, 0)
        self.set_font('Arial', '', 10)
        self.multi_cell(0, 6, description)
        self.ln(2)

pdf = PDF()
pdf.add_page()
pdf.set_font('Arial', '', 12)

# Introdução
pdf.multi_cell(0, 10, 'Este documento resume a complexidade e logica das funcoes implementadas para uma Lista Sequencial (baseada em Vetor Estatico).')
pdf.ln(5)

# Seção 1
pdf.chapter_title('1. Gestao da Lista')
pdf.function_row('ListaCria', 'O(1)', 'Aloca a struct e o vetor (malloc). Independe do tamanho N.')
pdf.function_row('ListaDestroi', 'O(1)', 'Libera memoria (free) do vetor e da struct. Nao percorre elementos.')
pdf.function_row('ListaTamanho', 'O(1)', 'Acesso direto a variavel "n".')
pdf.function_row('ListaEhVazia', 'O(1)', 'Comparacao simples (n == 0).')
pdf.ln(5)

# Seção 2
pdf.chapter_title('2. Insercao (O Gargalo)')
pdf.set_font('Arial', 'I', 10)
pdf.multi_cell(0, 5, 'Obs: Em vetores, inserir fora do final custa caro pois exige deslocamento (shift).')
pdf.ln(2)
pdf.function_row('InsereInicio', 'O(n)', 'Pior Caso. Desloca TODOS os elementos para a direita.')
pdf.function_row('InsereMeio', 'O(n)', 'Desloca elementos da posicao P ate o final.')
pdf.function_row('InsereFim', 'O(1)', 'Melhor Caso. Apenas grava no indice "n" e incrementa.')
pdf.ln(5)

# Seção 3
pdf.chapter_title('3. Remocao')
pdf.function_row('RemoveInicio', 'O(n)', 'Pior Caso. O item 1 vira 0, o 2 vira 1... Desloca tudo para a esquerda.')
pdf.function_row('RemoveMeio', 'O(n)', 'Tapa o buraco deslocando os elementos da frente para tras.')
pdf.function_row('RemoveFim', 'O(1)', 'Melhor Caso. Apenas decrementa "n". O dado vira lixo de memoria.')
pdf.ln(5)

# Seção 4
pdf.chapter_title('4. Acesso e Busca')
pdf.function_row('ListaGet', 'O(1)', 'Acesso direto pelo indice (vantagem do vetor).')
pdf.function_row('ListaPesquisa', 'O(n)', 'Busca Linear. Percorre um a um ate achar (lista nao ordenada).')
pdf.function_row('ListaPrint', 'O(n)', 'Percorre todo o vetor para imprimir.')
pdf.ln(5)

# Resumo Final
pdf.line(10, pdf.get_y(), 200, pdf.get_y())
pdf.ln(5)
pdf.set_font('Arial', 'B', 12)
pdf.cell(0, 10, 'Regra de Ouro para a Prova:', 0, 1)
pdf.set_font('Arial', '', 11)
pdf.multi_cell(0, 6, '- Mexeu no Fim? Rapido O(1).\n- Mexeu no Inicio/Meio? Lento O(n) (Shift).\n- Sabe o Indice? Rapido O(1).\n- Sabe o Valor? Lento O(n).')

pdf.output('Resumo_Lista_Sequencial.pdf')
print("PDF gerado com sucesso: Resumo_Lista_Sequencial.pdf")
