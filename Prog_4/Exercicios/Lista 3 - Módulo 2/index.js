const produtos = [
    {
      id: 1,
      nome: 'Leite',
      categoria: 'alimento',
      quantidade: 0,
      preco: 4,
    },
    {
      id: 2,
      nome: 'Monitor',
      categoria: 'informatica',
      quantidade: 0,
      preco: 999,
    },
    {
      id: 3,
      nome: 'Desinfetante',
      categoria: 'casa',
      quantidade: 0,
      preco: 7,
    },
    {
      id: 4,
      nome: 'Sabonete',
      categoria: 'higiene',
      quantidade: 0,
      preco: 2,
    },
    {
      id: 5,
      nome: 'Refrigerante',
      categoria: 'bebida',
      quantidade: 0,
      preco: 4,
    },
    {
      id: 6,
      nome: 'Fralda',
      categoria: 'higiene',
      quantidade: 0,
      preco: 22,
    },
    {
      id: 7,
      nome: 'Mouse',
      categoria: 'informatica',
      quantidade: 0,
      preco: 50,
    },
    {
      id: 8,
      nome: 'Cloro',
      categoria: 'casa',
      quantidade: 0,
      preco: 3,
    },
    {
        id: 9,
        nome: 'Pipoca',
        categoria: 'alimento',
        quantidade: 0,
        preco: 2,
      },
      {
        id: 10,
        nome: 'Sal',
        categoria: 'alimento',
        quantidade: 0,
        preco: 1,
      },
      {
        id: 11,
        nome: 'Batata',
        categoria: 'alimento',
        quantidade: 0,
        preco: 5,
      },
      {
        id: 12,
        nome: 'Prego',
        categoria: 'ferragen',
        quantidade: 0,
        preco: 10,
      },
      {
        id: 13,
        nome: 'Martelo',
        categoria: 'ferragen',
        quantidade: 0,
        preco: 15,
      },
      {
        id: 14,
        nome: 'Serra',
        categoria: 'ferragen',
        quantidade: 0,
        preco: 20,
      },
  ]

let tbody = document.getElementById('tbody')
let busca = document.getElementById("buscatxt")

// Povoando a tabela 
for (const element of produtos) {
    let tr = `
    <tr>
        <td>${element.nome}</td>
        <td>${element.categoria}</td>
        <td>${element.preco}</td>
        <td><a name="btn-add" href="#" class="btn btn-success" key="${element.id}">Adicionar</a></td>
    </tr>
    `
    tbody.innerHTML += tr;
}

// Buscas dos produtos na tabela 
busca.addEventListener("keyup", () => {
    let expressao = busca.value.toLowerCase();

    let linhas = tbody.getElementsByTagName('tr');

    for (let posicao in linhas){
        if (true === isNaN(posicao)) {
            continue;
        }
        let conteudpDalinha = linhas[posicao].innerHTML.toLocaleLowerCase();
        if (true === conteudpDalinha.includes(expressao)) {
            linhas[posicao].style.display = '';
        } else {
            linhas[posicao].style.display = 'none';
        }
    }
})

// Atulaiza o carrinho sempre que adciona um novo elemento
let atualizarCarrinho = () =>{
    let containerCarrinho = document.getElementById('carrinho')
    containerCarrinho.innerHTML = "";
    produtos.map((val)=>{
        if(val.quantidade > 0){
          let preco_final = val.preco * val.quantidade
            containerCarrinho.innerHTML+=`
            <div class="row mb-3" id="item${val.id}">
                <div class="col d-flex align-items-center">
                    <span>${val.nome}</span>
                    <span class="ms-auto valor_prod" key="${val.id}">${preco_final}</span>
                    <span>$</span>
                </div>
                <div class="col d-flex justify-content-end">
                  <span class="input-group-text">Quantidade =<span class="quant_valor ms-2" key="${val.id}">${val.quantidade}</span></span> 
            </div>
            `
        }
    })
}

let links = document.getElementsByName('btn-add')

for(const element of links){
    element.addEventListener("click",function(){
        let key = this.getAttribute('key') - 1;
            produtos[key].quantidade++;
            atualizarCarrinho();
            return false
    })
}

let btn = document.getElementById('car')
let valor_total = document.getElementById('valor_total')

//calcula o valor totala dos produtos
btn.addEventListener('click', ()=>{
  let total = produtos.reduce(getTotal, 0)
  function getTotal(total, item){
    return total + (item.preco * item.quantidade)
  }
  valor_total.innerHTML = total.toFixed(2) + '$'
})

//limpa o carrinho assim que vc paga ou nao quer mais comparar
function limpar() {
  let alvo = document.getElementById("carrinho");

  for(let i in produtos){
    produtos[i].quantidade = 0
  }
  // Remove todos os descendentes da div
  alvo.innerText = "";
}