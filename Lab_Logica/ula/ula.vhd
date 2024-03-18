library ieee;
use ieee.std_logic_1164.all;

-- Definição da entidade
entity ula is
	port(
		a,b: in STD_LOGIC_VECTOR(3 downto 0);
		f: in STD_LOGIC_VECTOR(1 downto 0);
		Y: out STD_LOGIC_VECTOR(3 downto 0);
		z,cout: out std_logic
	);
end ula;

architecture synth of ula is
	component mult_2 is
		port(
			d0,d1: in STD_LOGIC_VECTOR(3 downto 0);
			s: in std_logic;
			y: out STD_LOGIC_VECTOR(3 downto 0)
		);
	end component;
	
	component mult_4 is
		port(
			d0, d1, d2, d3: in STD_LOGIC_VECTOR(3 downto 0);
			s: in STD_LOGIC_VECTOR(1 downto 0);
			y: out STD_LOGIC_VECTOR(3 downto 0));
	 
	end component;
	
	component rip_c_adder is
		port(
			a,b:in STD_LOGIC_VECTOR(3 downto 0);
			y: out STD_LOGIC_VECTOR(3 downto 0);
			f: in std_logic;
			cout: out std_logic
		 );
	end component;
	
	component z_logic is
		port(
			y: in STD_LOGIC_VECTOR(3 downto 0);
			z: out std_logic
		);
	end component;

	signal mult2out, adderout, ab, notb, yin: STD_LOGIC_VECTOR(3 downto 0);
	signal addercout: std_logic;
begin
		
		ab <= (a and b);
		notb <= (not b);
		Y <= yin;
		cout <= addercout;

	   mult2: mult_2 port map(
			d0 => b,
			d1 => notb,
			s => f(0),
			y => mult2out
		);

		adder: rip_c_adder port map(
			a => a,
			b => mult2out,
			y => adderout,
			f => f(0),
			cout => addercout
		);
		
		mult4: mult_4 port map(
			d0 => ab,
			d1 => mult2out,
			d2 => adderout,
			d3 => adderout,
			s => f,
			y => yin
		);
		
		outz: z_logic port map(
			y => yin,
			z => z
		);

end synth;