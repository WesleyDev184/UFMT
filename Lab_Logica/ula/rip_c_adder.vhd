ture synth of rip_c_adder is
    component fulladder is
        port (
            a, b, cin: in STD_LOGIC;
            s, cout: out STD_LOGIC
        );
    end component;
library ieee;
use ieee.std_logic_1164.all;

-- Definição da entidade
entity rip_c_adder is
    port (
        a, b: in STD_LOGIC_VECTOR(3 downto 0);
        y: out STD_LOGIC_VECTOR(3 downto 0);
        f: in std_logic;
        cout: out std_logic
    );
end rip_c_adder;

architec
    signal cin1, cin2, cin3: std_logic;
begin
    Porta1: fulladder port map (
        a => a(0),
        b => b(0),
        cin => f,
        s => y(0),
        cout => cin1
    );

    Porta2: fulladder port map (
        a => a(1),
        b => b(1),
        cin => cin1,
        s => y(1),
        cout => cin2
    );

    Porta3: fulladder port map (
        a => a(2),
        b => b(2),
        cin => cin2,
        s => y(2),
        cout => cin3
    );

    Porta4: fulladder port map (
        a => a(3),
        b => b(3),
        cin => cin3,
        s => y(3),
        cout => cout
    );
end synth;