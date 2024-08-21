#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class Item{
  	public:
    	string nome;
    	int quantidade;
    	Item(string s, int q){
      		this->nome = s;
      		this->quantidade = q;
    	}
    	~Item(){}
};

class ProdutoEstoque: public Item{
  public:
    float valor;
    ProdutoEstoque(string n, float val, int quant): Item(n,quant){
      this->valor = val;
    }
    ~ProdutoEstoque(){}
};

typedef vector<ProdutoEstoque> vetProd;

class EstoqueProdutos{
		vetProd produtos;
  	public:
    	EstoqueProdutos(){}
    	void AdicionaProduto(string n, int v, int q){
      		ProdutoEstoque p(n, v, q);
      		this->produtos.push_back(p);
    	}
    	vetProd retProdutos(){
      		return this->produtos;
    	}
    	void removeProduto(string n){
      		for(int i=0; i<this->produtos.size(); i++){
        		if (this->produtos[i].nome == n){
          			this->produtos.erase(produtos.begin()+i);
          			cout << "Produto removido." << endl;
          			return;
        		}
      		}
      		cout << "Produto não encontrado." << endl;
    	}
    	void subtraiProduto(string n, int q){
      		for(int i=0; i<this->produtos.size(); i++){
        		if (this->produtos[i].nome == n){
          			this->produtos[i].quantidade -= q;
          			if (this->produtos[i].quantidade < 0){
            			this->produtos[i].quantidade = 0;
          			}
        		}
      		}
    	}
    	void imprime(){
			cout << endl; 
      		for (int i=0; i<this->produtos.size(); i++){
        		cout << this->produtos[i].nome << " | " << this->produtos[i].valor << " | " << this->produtos[i].quantidade << endl;
      		}
      		cout << endl;
    	}
    	~EstoqueProdutos(){}
};

class CarrinhoCompra{
		EstoqueProdutos& est;
		vector<Item> itens;
	public:
	    CarrinhoCompra(EstoqueProdutos& e) : est(e) {}
	    ~CarrinhoCompra(){}
	    void adicionaItem(string n, int q){
	    	vetProd vp = this->est.retProdutos();
	      	for(int i=0; i<vp.size(); i++){
	        	if(vp[i].nome == n){
	          		if(vp[i].quantidade == 0){
	            		break;
	          		} 
					else if(vp[i].quantidade < q){
	            		q = vp[i].quantidade;
	          		}
	          		Item it(n, q);
	          		this->itens.push_back(it);
	        	}
	    	}
	    }
	    void removeItem(string n, int q){
	    	for(int i=0; i<this->itens.size(); i++){
	        	if (this->itens[i].nome == n){
	          		this->itens[i].quantidade -= q;
	          		if (this->itens[i].quantidade <= 0){
	            		this->itens.erase(itens.begin()+i);
	          		}
	        	}
	      	}
	    }
	    void imprime(){
			cout << endl; 
	    	for(int i=0; i<this->itens.size(); i++){
	        	cout << this->itens[i].nome << " | " << this->itens[i].quantidade << endl;
	      	}
	      	cout << endl;
	    }
	    void finalizaCompra(float s, float t){
	    	if(s >= t){
	    		for(int i=0; i<itens.size(); i++){
	          		this->est.subtraiProduto(itens[i].nome, itens[i].quantidade);
	        	}
	        	this->itens.clear();
	      	} 
			else{
	      		cout << "Saldo insuficiente." << endl;
			}
	    }
	    float calculaTotal(){
	    	int i, j;
	      	float total = 0;
	      	cout << endl;
	      	vetProd vp = this->est.retProdutos();  
	      	for(i=0;i<this->itens.size();i++){
	        	for(j=0;j<vp.size();j++){
	          		if(vp[j].nome == this->itens[i].nome){
	            		total += vp[j].valor * this->itens[i].quantidade;
	          		}
	        	}
	      	}
	      	return total;
	    }
};

class Cliente{
		CarrinhoCompra carrinho;
    	float saldo;
	public:    
    	Cliente(EstoqueProdutos& est, float saldo) : carrinho(est) {
      		this->saldo = saldo;
   	 	}
    	~Cliente(){}
	    void adicionarNoCarrinho(string n, int q){
	      	this->carrinho.adicionaItem(n, q);
	    }
	    void removeDoCarrinho(string n, int q){
	      	this->carrinho.removeItem(n, q);
	    }
	    void finalizarCompra(){
	      	float t = this->carrinho.calculaTotal();
	      	this->carrinho.finalizaCompra(this->saldo, t);
	      	if(this->saldo>=t){
	      		this->saldo -= t;
			}
	    }
	    void SaldoEprecoTotal(){
	    	cout << endl;
	    	cout << "Saldo:" << this->saldo << endl;
	      	cout << "Valor total dos itens no carrinho:" << this->carrinho.calculaTotal() << endl;
	    }
	    void mostraCarrinho(){
	      	this->carrinho.imprime();
	    }
		void adicionaSaldo(float val){
			this->saldo += val;
		}
};

class Admin{
		string senha;
	public:
  	Admin(string s){
  		this->senha = s;
	}
	int verificaSenha(string s){
		if(this->senha==s){
			return 1;
		}
		else{
			return 0;
		}
	}
	void adicionarAoEstoque(EstoqueProdutos& est, string n, int v, int q){
    	est.AdicionaProduto(n, v, q);
    }
    void removerDoEstoque(EstoqueProdutos& est, string n){
    	est.removeProduto(n);
    }
    void mostraEstoque(EstoqueProdutos& est){
    	est.imprime();
    }
    ~Admin(){}
};

int main(){
	setlocale(LC_ALL, "");
	EstoqueProdutos estoque;
  	Admin adm("abcde");
  	Cliente c(estoque, 0);
  	int op, usertype, quant, verSenha;
  	string nomeCliente, nomeProduto, senha, nomeRegistrado;
  	float val;
  	while(1){
	    cout << "Olá!" << endl;
	    cout << "Iniciar sessão como cliente(1), administrador(2) ou sair(3)?" << endl;
	    cout << "Informe:";
	    cin >> usertype;
	    if(usertype==2){
	    	cout << "Insira senha:";
	      	cin >> senha;
	      	verSenha = adm.verificaSenha(senha);
	      	if(verSenha==0){
	      		usertype = 0;
		  	}
	    }
	    else if(usertype==3){
	    	break;
	    }
	    while(usertype==1){
	    	cout << "1 - Adicionar valor ao saldo" << endl;
	    	cout << "2 - Adicionar item ao carrinho" << endl;
	      	cout << "3 - Remover item do carrinho" << endl;
	      	cout << "4 - Ver carrinho" << endl;
	      	cout << "5 - Ver saldo atual (e o valor dos itens no carrinho)" << endl;
	      	cout << "6 - Finalizar compra atual" << endl;
	      	cout << "7 - Finalizar sessão" << endl;
	      	cout << "Informe a operação:";
	    	cin >> op;
		    if(op==7){
		      usertype = 0;
		      break;
		    }
		    switch(op){
		    	case (1):
		    		cout << "Informe o valor:";
		    		cin >> val;
		        	c.adicionaSaldo(val);
		        	break;
		    	case (2):
		        	cout << "Informe o nome do produto:";
		        	cin >> nomeProduto;
		        	cout << "Informe a quantidade:";
		        	cin >> quant;
		        	c.adicionarNoCarrinho(nomeProduto, quant);
		        	break;
		    	case (3):
		        	cout << "Informe o nome do produto:";
		        	cin >> nomeProduto;
		        	cout << "Informe a quantidade a ser removida:";
		        	cin >> quant;
		        	c.removeDoCarrinho(nomeProduto, quant);
		        	break;
		    	case (4):
		        	c.mostraCarrinho();
		        	break;
		        case (5):
		        	c.SaldoEprecoTotal();
		        	break;
		    	case (6):
		        	c.finalizarCompra();
		        	break;
		      	default:
		        	cout << endl;
					cout << "Operação inválida." << endl;
		        	break;
		    }
		    cout << endl;
		}
	    while(usertype==2){
		    cout<< "1 - Adicionar novo produto ao estoque" << endl;
		    cout<< "2 - Remover produto do estoque" << endl;
	    	cout<< "3 - Verificar o estoque" << endl;
	    	cout<< "4 - Finalizar sessão" << endl;
	    	cout << "Informe a operação:";
	    	cin >> op;
		    if(op==4){
		    	usertype = 0;
		    	break;
		    }
		    switch(op){
		    	case (1):
		        	cout << "Informe o nome do produto:";
		        	cin >> nomeProduto;
		        	cout << "Informe o valor unitário:";
					cin >> val;
		        	printf("Informe a quantidade:");
		        	cin >> quant;
		        	adm.adicionarAoEstoque(estoque, nomeProduto, val, quant);
		        	break;
		    	case (2):
		        	cout << "Informe o nome do produto:";
		        	cin >> nomeProduto;
		        	adm.removerDoEstoque(estoque, nomeProduto);
		        	break;
		    	case (3):
		        	adm.mostraEstoque(estoque);
		        	break;
		      	default:
		        	cout << endl;
					cout <<"Operação inválida.";
		        	break;
		    }
		    cout << endl;
		}
		system("cls");
    }
  	return 0;	
}
