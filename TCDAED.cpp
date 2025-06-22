#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <iomanip>
using namespace std::chrono;
using namespace std;

class estrutura_dados {
    private:
        int comprimento;
    
    public:
        virtual int get_comprimento() const {
            return comprimento;
        }

        virtual bool esta_vazia() const = 0;
        virtual bool esta_cheia() const = 0;
};



class array: public estrutura_dados{
    private:
        int* elementos;
        int comprimento_total;
    public:
        array(int tamanho) {
            comprimento_total = tamanho;
            elementos = new int[comprimento_total];
        }
        ~array() {
            delete[] elementos;
        }
        int& operator [] (int indice) const {
            if (indice < 0 || indice >= comprimento_total) {
                throw out_of_range("Índice fora do intervalo!");
            }
            return elementos[indice];
        }

        
        int get_comprimento() const {
            return comprimento_total;
        }


};

class lista_encadeada: public estrutura_dados {
private:
    struct Node {
        int data;
        Node* next;
    };
    Node* head;
    int comprimento_total;
public:
    lista_encadeada() : head(nullptr), comprimento_total(0) {}

    void inserir(int valor) {
        Node* novo = new Node{valor, head};
        head = novo;
        comprimento_total++;
    }

    int remover() {
        if (head == nullptr) {
            cout << "Lista vazia!" << endl;
            throw out_of_range("Lista vazia!");
        }
        Node* temp = head;
        int valor = head->data;
        head = head->next;
        delete temp;
        comprimento_total--;
        return valor;
    }

    int operator [](int indice) const {
        if (indice < 0 || indice >= comprimento_total) {
            cout << "Índice fora do intervalo!" << endl;
            throw out_of_range("Índice fora do intervalo!");
        }
        Node* atual = head;
        for (int i = 0; i < indice; i++) {
            atual = atual->next;
        }
        return atual->data;
    }
    bool esta_vazia() const {
        return head == nullptr;
    }

    bool esta_cheia() const {
        return false; // Lista encadeada nunca está cheia, a menos que haja falta de memória
    }
    int get_comprimento() const {
        return comprimento_total;
    }
    ~lista_encadeada() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void imprimir() const {
        Node* atual = head;
        while (atual) {
            cout << atual->data << " ";
            atual = atual->next;
        }
        cout << endl;
    }
};

class lista_duplamente_encadeada: public estrutura_dados {
    private:
        struct Node {
            int data;
            Node* next;
            Node* prev;
        };
        Node* head;
        Node* tail;
        int comprimento_total;
    public:
        lista_duplamente_encadeada() : head(nullptr), tail(nullptr), comprimento_total(0) {}
        void push_back(int valor) {
            Node* novo = new Node{valor, nullptr, tail};
            if (tail) {
                tail->next = novo;
            } else {
                head = novo; // Se a lista estava vazia, head aponta para o novo nó
            }
            tail = novo;
            comprimento_total++;
        }
        void push(int valor) {
            Node* novo = new Node{valor, head, nullptr};
            if (head) {
                head->prev = novo;
            } else {
                tail = novo; // Se a lista estava vazia, tail aponta para o novo nó
            }
            head = novo;
            comprimento_total++;
        }

        int pop_back() {
            if (tail == nullptr) {
                cout << "Lista vazia!" << endl;
                throw out_of_range("Lista vazia!");
            }
            Node* temp = tail;
            int valor = tail->data;
            tail = tail->prev;
            if (tail) {
                tail->next = nullptr;
            } else {
                head = nullptr; // Se a lista ficou vazia, head também deve ser nulo
            }
            delete temp;
            comprimento_total--;
            return valor;
        }
        int pop() {
            if (head == nullptr) {
                cout << "Lista vazia!" << endl;
                throw out_of_range("Lista vazia!");
            }
            Node* temp = head;
            int valor = head->data;
            head = head->next;
            if (head) {
                head->prev = nullptr;
            } else {
                tail = nullptr; // Se a lista ficou vazia, tail também deve ser nulo
            }
            delete temp;
            comprimento_total--;
            return valor;
        }

        int operator [](int indice) const {
            if (indice < 0 || indice >= comprimento_total) {
                cout << "Índice fora do intervalo!" << endl;
                throw out_of_range("Índice fora do intervalo!");
            }
            Node* atual = head;
            for (int i = 0; i < indice; i++) {
                atual = atual->next;
            }
            return atual->data;
        }
        bool esta_vazia() const {
            return head == nullptr;
        }
        bool esta_cheia() const {
            return false; // Lista duplamente encadeada nunca está cheia, a menos que haja falta de memória
        }

        void swap(int indice) {
           // Troca [indice] com o seguinte
            if (indice < 0 || indice >= comprimento_total - 1) {
                cout << "Índice fora do intervalo para troca!" << endl;
                throw out_of_range("Índice fora do intervalo para troca!");
            }
            Node* atual = head;
            for (int i = 0; i < indice; i++) {
                atual = atual->next;
            }
            Node* proximo = atual->next;
            if (proximo) {
                int temp = atual->data;
                atual->data = proximo->data;
                proximo->data = temp;
            }
        }

        void ordenar() {
            if (comprimento_total < 2) return; // Não há nada para ordenar
            for (int i = 0; i < comprimento_total - 1; i++) {
                Node* atual = head;
                for (int j = 0; j < comprimento_total - i - 1; j++) {
                    if (atual->data > atual->next->data) {
                        swap(j);
                    }
                    atual = atual->next;
                }
            }
        }
        void imprimir() const {
            Node* atual = head;
            while (atual) {
                cout << atual->data << " ";
                atual = atual->next;
            }
            cout << endl;
        }
        ~lista_duplamente_encadeada() {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }

};

class fila: public estrutura_dados{
    private:
        lista_duplamente_encadeada elementos;
    public:
        void enqueue(int valor) {
            elementos.push_back(valor);
        }

        int dequeue() {
            return elementos.pop();
        }

        bool esta_vazia() const {
            return elementos.get_comprimento() == 0;
        }

        int get_comprimento() const {
            return elementos.get_comprimento();
        }

        void imprimir() const {
            elementos.imprimir();
        }
        bool esta_cheia() const {
            return false; // Fila nunca está cheia, a menos que haja falta de memória
        }
        
};

class pilha: public estrutura_dados {
private:
    lista_encadeada elementos;

public:
    pilha() {}
    void empilha(int valor) {
        elementos.inserir(valor);
    }

    int desempilha() {
        if (esta_vazia()) {
            cout << "Pilha vazia!" << endl;
            throw out_of_range("Pilha vazia!");
        }
        int valor = elementos.remover();
        return valor;
    }
    bool esta_vazia() const {
        return elementos.esta_vazia();
    }

    bool esta_cheia() const {
        return false; // Pilha nunca está cheia, a menos que haja falta de memória
    }
    int get_comprimento() const {
        return elementos.get_comprimento();
    }
    void imprimir() const {
        elementos.imprimir();
    }
    void troca() {
        // Troca o topo da pilha com o segundo elemento
        if (elementos.get_comprimento() < 2) {
            cout << "Não há elementos suficientes para trocar!" << endl;
            throw out_of_range("Não há elementos suficientes para trocar!");
        }
        int primeiro = elementos.remover();
        int segundo = elementos.remover();
        elementos.inserir(primeiro);
        elementos.inserir(segundo);
    }
    
};

class Usuario {
public:
    string nome;
    int tempo_medio_atendimento; // em minutos
    system_clock::time_point hora_entrada;
    system_clock::time_point hora_estimada;

    Usuario(string nome, int tempo_medio)
        : nome(nome), tempo_medio_atendimento(tempo_medio) {
        hora_entrada = system_clock::now();
    }
};

class FilaBandejao {
private:
    vector<Usuario> fila;
    int tempo_medio_global;

public:
    FilaBandejao(int tempo_medio_global = 5) : tempo_medio_global(tempo_medio_global) {}

    void entrar_na_fila(string nome, int tempo_atendimento) {
        Usuario novo(nome, tempo_atendimento);
        novo.hora_estimada = calcular_horario_estimado();
        fila.push_back(novo);
        cout << nome << " entrou na fila. Estimativa: "
             << formatar_horario(novo.hora_estimada) << endl;
    }

    void sair_da_fila(string nome) {
        for (auto it = fila.begin(); it != fila.end(); ++it) {
            if (it->nome == nome) {
                fila.erase(it);
                cout << nome << " saiu da fila.\n";
                atualizar_estimativas();
                return;
            }
        }
        cout << "Usuário não encontrado na fila.\n";
    }

    void mostrar_fila() const {
        cout << "\nFila atual:\n";
        for (size_t i = 0; i < fila.size(); i++) {
            cout << setw(2) << i + 1 << ". " << fila[i].nome
                 << " - Estimativa: " << formatar_horario(fila[i].hora_estimada) << endl;
        }
    }

private:
    system_clock::time_point calcular_horario_estimado() const {
        if (fila.empty())
            return system_clock::now() + minutes(tempo_medio_global);
        else {
            auto ultimo = fila.back().hora_estimada;
            return ultimo + minutes(tempo_medio_global);
        }
    }

    void atualizar_estimativas() {
        auto tempo = system_clock::now();
        for (auto& usuario : fila) {
            tempo += minutes(tempo_medio_global);
            usuario.hora_estimada = tempo;
        }
    }

    string formatar_horario(system_clock::time_point tp) const {
        time_t t = system_clock::to_time_t(tp);
        tm* tm_ptr = localtime(&t);
        char buffer[9];
        strftime(buffer, sizeof(buffer), "%H:%M:%S", tm_ptr);
        return string(buffer);
    }
};

// int main() {
//     FilaBandejao bandejao;

//     bandejao.entrar_na_fila("Ana", 5);
//     bandejao.entrar_na_fila("João", 4);
//     bandejao.entrar_na_fila("Carlos", 6);

//     bandejao.mostrar_fila();

//     cout << "\nCarlos desistiu...\n";
//     bandejao.sair_da_fila("Carlos");

//     bandejao.mostrar_fila();

//     return 0;
// }


int main() {
    pilha minha_pilha;
    minha_pilha.empilha(10);
    minha_pilha.empilha(20);
    minha_pilha.empilha(30);
    cout << "Conteúdo da pilha: ";
    minha_pilha.imprimir();

    minha_pilha.troca();
    cout << "Conteúdo da pilha após troca: ";
    minha_pilha.imprimir();

    return 0;
}