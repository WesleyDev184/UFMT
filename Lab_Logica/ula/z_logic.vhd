library ieee;
use ieee.std_logic_1164.all;

-- Definição da entidade
entity z_logic is
    port(
        y: in std_logic_vector(3 downto 0);
        z: out std_logic
    );
end z_logic;

architecture synth of z_logic is
    signal comp: std_logic_vector(3 downto 0);
begin
    comp <= not y;
    z <= comp(0) and comp(1) and comp(2) and comp(3);
end synth;