library ieee;
use ieee.std_logic_1164.all;

-- Definição da entidade
entity mult_2 is
	port(
			d0,d1: in STD_LOGIC_VECTOR(3 downto 0);
			s: in std_logic;
			y: out STD_LOGIC_VECTOR(3 downto 0)
	);
end mult_2;

architecture synth of mult_2 is
begin

	y <= d0 when s = '0' else d1;      

end synth;