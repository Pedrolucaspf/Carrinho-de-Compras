#include <iostream>
#include <string>
#include <vector>

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
    void AdicionaProduto(ProdutoEstoque p){
      this->produtos.push_back(p);
    }
    vetProd retProdutos(){
      return this->produtos;
    }
    ~EstoqueProdutos(){}
};

class CarrinhoCompra{
    EstoqueProdutos est;
    vector<Item> itens;
  public:
    CarrinhoCompra(EstoqueProdutos e){
      this->est = e;
    }
    ~CarrinhoCompra(){}
    void adicionaItem(Item it){
      this->itens.push_back(it);
    }
    void finalizaCompra(){
      int i, j;
      vetProd vp = this->est.retProdutos();
      for(i=0;i<this->itens.size();i++){
        for(j=0;j<vp.size();j++){
          if(vp[i].nome==this->itens[j].nome){
            vp[i].quantidade -= this->itens[j].quantidade;
          }
        }
      }
    }
    float calculaTotal(){
      int i, j;
      float total = 0;
      vetProd vp = this->est.retProdutos();  
      for(i=0;i<this->itens.size();i++){
        for(j=0;j<vp.size();j++){
          if(vp[i].nome==this->itens[j].nome){
            total += vp[i].valor * this->itens[j].quantidade;
          }
        }
      }
      return total;
    }
};

int main() {
  EstoqueProdutos estoque;
  estoque.AdicionaProduto(ProdutoEstoque("monitor", 500, 100));
  estoque.AdicionaProduto(ProdutoEstoque("telefone", 150, 300));
  estoque.AdicionaProduto(ProdutoEstoque("teclado", 70, 50));
  estoque.AdicionaProduto(ProdutoEstoque("mouse", 50, 50));
  CarrinhoCompra carrinho(estoque);
  carrinho.adicionaItem(Item("monitor",2));
  carrinho.adicionaItem(Item("telefone",5));
  carrinho.adicionaItem(Item("teclado",5));
  carrinho.finalizaCompra();
  cout << "A soma dos produtos: " << carrinho.calculaTotal();
  return 0;
}
