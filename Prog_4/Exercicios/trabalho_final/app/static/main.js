let ul = document.getElementById('lista');
let busca = document.getElementById('search');
let select = document.getElementById('category')
let form = document.getElementById('form')

const options = {
  method: "GET",
  headers: {
    "X-RapidAPI-Key": "fd45454c6fmsha235a8c03553e25p1aa449jsn595fe0a73ab0",
    "X-RapidAPI-Host": "free-to-play-games-database.p.rapidapi.com",
  },
};

const games_url =
  "https://free-to-play-games-database.p.rapidapi.com/api/games?sort-by=alphabetical";
const searchCategoryUrl =
  "https://free-to-play-games-database.p.rapidapi.com/api/games?category=";

const getGames = async (url) => {
  await fetch(url, options)
    .then((response) => response.json())
    .then((data) => {
      showGames(data);
    })
    .catch((err) => console.error(err));
};

getGames(games_url);

const showGames = (data) => {
  const lista = document.getElementById("lista");

  data.map((item) => {
    const li = document.createElement("li");

    li.setAttribute("id", item.title);
    li.innerHTML = `
  
            <div
            class="border rounded-lg shadow-md bg-gray-800 border-gray-700 h-96 w-72 transition hover:-translate-y-1 hover:scale-110 hover:bg-indigo-600 duration-300"
            >
            <div class="flex justify-center mt-2">
                <img class="rounded-t-lg w-64 mt-2" src="${item.thumbnail}" alt="${item.title}" />
            </div>
            <div class="p-5 h-56 grid grid-rows-4">
              <div class="row-span-1 w-64">
                <h5
                class="mb-2 text-xl font-bold tracking-tight text-white truncate"
                id="title"
                >
                ${item.title}
                </h5>
              </div>
              <div class="row-span-2 overflow-y-hidden overflow-y-scroll">
                <p class="mb-3 font-normal text-gray-300">
                ${item.short_description}
                </p>
              </div>
              <div class="row-span-1 flex items-end justify-between">
                <span class="bg-gray-200 rounded-full px-3 py-1 text-sm font-semibold text-gray-700 cursor-pointer">#${item.genre}</span>
                <button type="button" class="text-white font-medium rounded-lg text-sm px-5 py-1 text-center inline-flex items-center mr-2 bg-emerald-500 hover:bg-emerald-800 focus:bg-emerald-400">
                  <svg aria-hidden="true" class="mr-2 -ml-1 w-4 h-4" fill="currentColor" viewBox="0 0 20 20" xmlns="http://www.w3.org/2000/svg">
                  <path d="M3 1a1 1 0 000 2h1.22l.305 1.222a.997.997 0 00.01.042l1.358 5.43-.893.892C3.74 11.846 4.632 14 6.414 14H15a1 1 0 000-2H6.414l1-1H14a1 1 0 00.894-.553l3-6A1 1 0 0017 3H6.28l-.31-1.243A1 1 0 005 1H3zM16 16.5a1.5 1.5 0 11-3 0 1.5 1.5 0 013 0zM6.5 18a1.5 1.5 0 100-3 1.5 1.5 0 000 3z"></path></svg>
                  Buy now
                </button>
              </div>
            </div>
            </div>
            
        `;

    lista.appendChild(li);
  });
};

const searchCategory = () => {
  let category = select.value.toLowerCase();
  if (category == "todos") {
    ul.innerText = "";
    getGames(games_url);
  } else {
    ul.innerText = "";
    getGames(searchCategoryUrl + category);
  }
};

form.addEventListener("submit", (e) => {
  e.preventDefault();
  Buscar();
});

const Buscar = () => {
  let expressao = busca.value.toLowerCase();

  let li = ul.getElementsByTagName("li");

  for (let posicao in li) {
    if (true === isNaN(posicao)) {
      continue;
    }
    let conteudpDalinha = li[posicao].id.toLocaleLowerCase();
    if (true === conteudpDalinha.includes(expressao)) {
      li[posicao].style.display = "";
    } else {
      li[posicao].style.display = "none";
    }
  }
};
