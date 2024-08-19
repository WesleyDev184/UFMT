#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;  

class Card {
protected:
    string name;
    string type;

public:
    Card(string name, string type) : name(name), type(type) {}

    virtual ~Card() {}

    string getName() const {
        return name;
    }

    string getType() const {
        return type;
    }

    friend Card operator+(const Card& c1, const Card& c2);
};

class MonsterCard : public Card {
public:
    MonsterCard(string name) : Card(name, "Monstro") {}
};

class SpellCard : public Card {
public:
    SpellCard(string name) : Card(name, "Magia") {}
};

class EquipCard : public Card {
public:
    EquipCard(string name) : Card(name, "Equipamento") {}
};

struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& pair) const {
        return hash<T1>()(pair.first) ^ hash<T2>()(pair.second);
    }
};

unordered_map<pair<string, string>, pair<string, string>, pair_hash> fusoes = {
    {{"Koumori Dragon", "Saggi the Dark Clown"}, {"Reaper of the Cards", "Monstro"}},
    {{"Beast Fangs", "Beast Fangs"}, {"Eatgaboon", "Armadilha"}},
    {{"Dark Magic", "Dragon"}, {"Blackland Fire Dragon", "Monstro"}},
    {{"Dragon", "Machine"}, {"Metal Dragon", "Monstro"}},
    {{"Dark Spellcaster", "Ryu-Kishin"}, {"Ryu-Kishin Powered", "Monstro"}},
    {{"Dragon Capture Jar", "Mooyan Curry"}, {"Dragon Capture Jar", "Magia"}},
    {{"Hinotama", "Hinotama"}, {"Final Flame", "Magia"}},
    {{"Dark Energy", "Acid Trap Hole"}, {"Dark Hole", "Magia"}},
    {{"Electro-whip", "Metalmorph"}, {"Raigeki", "Magia"}},
    {{"Goblin’s Secret Remedy", "Goblin’s Secret Remedy"}, {"Soul of the Pure", "Armadilha"}},
    {{"Legendary Sword", "Sword of Dark Destruction"}, {"Kunai with Chain", "Equipamento"}},
    {{"Legendary Sword", "Sparks"}, {"Salamandra", "Equipamento"}},
    {{"Machine Conversion Factory", "Silver Bow & Arrow"}, {"Winged Trumpeter", "Equipamento"}},
    {{"Castle of Dark Illusions", "Dark-Piercing Light"}, {"Bright Castle", "Equipamento"}},
    {{"Elegant Egotist", "Horn of the Unicorn"}, {"Curse of Tri-Horned Dragon", "Monstro"}}
};

Card operator+(const Card& c1, const Card& c2) {
    auto key = make_pair(c1.getName(), c2.getName());
    if (fusoes.find(key) != fusoes.end()) {
        return Card(fusoes[key].first, fusoes[key].second);
    }
    return Card("Fusão Inválida", "Desconhecido");
}

int main() {
    // Exemplo de fusões
    MonsterCard monstro1("Koumori Dragon");
    MonsterCard monstro2("Saggi the Dark Clown");
    SpellCard magia1("Dragon Capture Jar");
    SpellCard magia2("Mooyan Curry");
    EquipCard equip1("Legendary Sword");
    EquipCard equip2("Sword of Dark Destruction");

    Card fusao1 = monstro1 + monstro2;
    Card fusao2 = magia1 + magia2;
    Card fusao3 = equip1 + equip2;

    cout << "Resultado da Fusão 1: " << fusao1.getName() << " (" << fusao1.getType() << ")\n";
    cout << "Resultado da Fusão 2: " << fusao2.getName() << " (" << fusao2.getType() << ")\n";
    cout << "Resultado da Fusão 3: " << fusao3.getName() << " (" << fusao3.getType() << ")\n";

    return 0;
}
