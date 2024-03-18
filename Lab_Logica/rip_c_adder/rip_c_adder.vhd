-- Implementação comportamentao or_and
library ieee;
use ieee.std_logic_1164.all;

-- Definição da entidade
entity rip_c_adder is
	port(
			a,b,c,d,e,f,g,h: in std_logic;
			Y1,y2,y3,y4,ovf: out std_logic
		 );
end rip_c_adder;

architecture synth of rip_c_adder is
	component fulladder is
		port(
			a, b, cin: in  STD_LOGIC;
			s, cout:   out STD_LOGIC
			);
	end component;
	
	signal cin1,cin2,cin3: std_logic;
begin
	
	Porta1: fulladder port map(
		a => a,
		b => b,
		cin => '0',
		s => Y1,
		cout => cin1
	);
	
	Porta2: fulladder port map(
		a => c,
		b => d,
		cin => cin1,
		s => Y2,
		cout => cin2
	);
	
	Porta3: fulladder port map(
		a => e,
		b => f,
		cin => cin2,
		s => Y3,
		cout => cin3
	);
	
	Porta4: fulladder port map(
		a => g,
		b => h,
		cin => cin3,
		s => Y4,
		cout => ovf
	);
	
end synth;