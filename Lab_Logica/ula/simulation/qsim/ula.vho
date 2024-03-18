-- Copyright (C) 2021  Intel Corporation. All rights reserved.
-- Your use of Intel Corporation's design tools, logic functions 
-- and other software and tools, and any partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Intel Program License 
-- Subscription Agreement, the Intel Quartus Prime License Agreement,
-- the Intel FPGA IP License Agreement, or other applicable license
-- agreement, including, without limitation, that your use is for
-- the sole purpose of programming logic devices manufactured by
-- Intel and sold by Intel or its authorized distributors.  Please
-- refer to the applicable agreement for further details, at
-- https://fpgasoftware.intel.com/eula.

-- VENDOR "Altera"
-- PROGRAM "Quartus Prime"
-- VERSION "Version 21.1.0 Build 842 10/21/2021 SJ Lite Edition"

-- DATE "03/15/2024 13:25:03"

-- 
-- Device: Altera 10M50DAF484C7G Package FBGA484
-- 

-- 
-- This VHDL file should be used for Questa Intel FPGA (VHDL) only
-- 

LIBRARY FIFTYFIVENM;
LIBRARY IEEE;
USE FIFTYFIVENM.FIFTYFIVENM_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	hard_block IS
    PORT (
	devoe : IN std_logic;
	devclrn : IN std_logic;
	devpor : IN std_logic
	);
END hard_block;

-- Design Ports Information
-- ~ALTERA_TMS~	=>  Location: PIN_H2,	 I/O Standard: 2.5 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_TCK~	=>  Location: PIN_G2,	 I/O Standard: 2.5 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_TDI~	=>  Location: PIN_L4,	 I/O Standard: 2.5 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_TDO~	=>  Location: PIN_M5,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- ~ALTERA_CONFIG_SEL~	=>  Location: PIN_H10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- ~ALTERA_nCONFIG~	=>  Location: PIN_H9,	 I/O Standard: 2.5 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_nSTATUS~	=>  Location: PIN_G9,	 I/O Standard: 2.5 V Schmitt Trigger,	 Current Strength: Default
-- ~ALTERA_CONF_DONE~	=>  Location: PIN_F8,	 I/O Standard: 2.5 V Schmitt Trigger,	 Current Strength: Default


ARCHITECTURE structure OF hard_block IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL \~ALTERA_TMS~~padout\ : std_logic;
SIGNAL \~ALTERA_TCK~~padout\ : std_logic;
SIGNAL \~ALTERA_TDI~~padout\ : std_logic;
SIGNAL \~ALTERA_CONFIG_SEL~~padout\ : std_logic;
SIGNAL \~ALTERA_nCONFIG~~padout\ : std_logic;
SIGNAL \~ALTERA_nSTATUS~~padout\ : std_logic;
SIGNAL \~ALTERA_CONF_DONE~~padout\ : std_logic;
SIGNAL \~ALTERA_TMS~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_TCK~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_TDI~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_CONFIG_SEL~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_nCONFIG~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_nSTATUS~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_CONF_DONE~~ibuf_o\ : std_logic;

BEGIN

ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;
END structure;


LIBRARY FIFTYFIVENM;
LIBRARY IEEE;
USE FIFTYFIVENM.FIFTYFIVENM_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	ula IS
    PORT (
	a : IN std_logic_vector(3 DOWNTO 0);
	b : IN std_logic_vector(3 DOWNTO 0);
	f : IN std_logic_vector(1 DOWNTO 0);
	Y : BUFFER std_logic_vector(3 DOWNTO 0);
	z : BUFFER std_logic
	);
END ula;

-- Design Ports Information
-- Y[0]	=>  Location: PIN_A8,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- Y[1]	=>  Location: PIN_A9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- Y[2]	=>  Location: PIN_A10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- Y[3]	=>  Location: PIN_B10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- z	=>  Location: PIN_C13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- f[1]	=>  Location: PIN_C11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- f[0]	=>  Location: PIN_C10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- a[0]	=>  Location: PIN_A13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b[0]	=>  Location: PIN_D12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- a[1]	=>  Location: PIN_A14,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b[1]	=>  Location: PIN_C12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- a[2]	=>  Location: PIN_B14,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b[2]	=>  Location: PIN_A12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- a[3]	=>  Location: PIN_F15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b[3]	=>  Location: PIN_B12,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF ula IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_a : std_logic_vector(3 DOWNTO 0);
SIGNAL ww_b : std_logic_vector(3 DOWNTO 0);
SIGNAL ww_f : std_logic_vector(1 DOWNTO 0);
SIGNAL ww_Y : std_logic_vector(3 DOWNTO 0);
SIGNAL ww_z : std_logic;
SIGNAL \~QUARTUS_CREATED_ADC1~_CHSEL_bus\ : std_logic_vector(4 DOWNTO 0);
SIGNAL \~QUARTUS_CREATED_ADC2~_CHSEL_bus\ : std_logic_vector(4 DOWNTO 0);
SIGNAL \~QUARTUS_CREATED_GND~I_combout\ : std_logic;
SIGNAL \~QUARTUS_CREATED_UNVM~~busy\ : std_logic;
SIGNAL \~QUARTUS_CREATED_ADC1~~eoc\ : std_logic;
SIGNAL \~QUARTUS_CREATED_ADC2~~eoc\ : std_logic;
SIGNAL \Y[0]~output_o\ : std_logic;
SIGNAL \Y[1]~output_o\ : std_logic;
SIGNAL \Y[2]~output_o\ : std_logic;
SIGNAL \Y[3]~output_o\ : std_logic;
SIGNAL \z~output_o\ : std_logic;
SIGNAL \f[1]~input_o\ : std_logic;
SIGNAL \b[0]~input_o\ : std_logic;
SIGNAL \f[0]~input_o\ : std_logic;
SIGNAL \a[0]~input_o\ : std_logic;
SIGNAL \mult4|y[0]~0_combout\ : std_logic;
SIGNAL \b[1]~input_o\ : std_logic;
SIGNAL \mult4|y[1]~1_combout\ : std_logic;
SIGNAL \a[1]~input_o\ : std_logic;
SIGNAL \mult4|y[1]~2_combout\ : std_logic;
SIGNAL \adder|Porta1|cout~0_combout\ : std_logic;
SIGNAL \adder|Porta2|cout~0_combout\ : std_logic;
SIGNAL \b[2]~input_o\ : std_logic;
SIGNAL \mult4|y[2]~3_combout\ : std_logic;
SIGNAL \a[2]~input_o\ : std_logic;
SIGNAL \mult4|y[2]~4_combout\ : std_logic;
SIGNAL \b[3]~input_o\ : std_logic;
SIGNAL \mult4|y[3]~5_combout\ : std_logic;
SIGNAL \mult4|y[3]~6_combout\ : std_logic;
SIGNAL \a[3]~input_o\ : std_logic;
SIGNAL \mult4|y[3]~7_combout\ : std_logic;
SIGNAL \outz|z~combout\ : std_logic;
SIGNAL \outz|ALT_INV_z~combout\ : std_logic;

COMPONENT hard_block
    PORT (
	devoe : IN std_logic;
	devclrn : IN std_logic;
	devpor : IN std_logic);
END COMPONENT;

BEGIN

ww_a <= a;
ww_b <= b;
ww_f <= f;
Y <= ww_Y;
z <= ww_z;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\~QUARTUS_CREATED_ADC1~_CHSEL_bus\ <= (\~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\);

\~QUARTUS_CREATED_ADC2~_CHSEL_bus\ <= (\~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\ & \~QUARTUS_CREATED_GND~I_combout\);
\outz|ALT_INV_z~combout\ <= NOT \outz|z~combout\;
auto_generated_inst : hard_block
PORT MAP (
	devoe => ww_devoe,
	devclrn => ww_devclrn,
	devpor => ww_devpor);

-- Location: LCCOMB_X44_Y41_N8
\~QUARTUS_CREATED_GND~I\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \~QUARTUS_CREATED_GND~I_combout\ = GND

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	combout => \~QUARTUS_CREATED_GND~I_combout\);

-- Location: IOOBUF_X46_Y54_N2
\Y[0]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \mult4|y[0]~0_combout\,
	devoe => ww_devoe,
	o => \Y[0]~output_o\);

-- Location: IOOBUF_X46_Y54_N23
\Y[1]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \mult4|y[1]~2_combout\,
	devoe => ww_devoe,
	o => \Y[1]~output_o\);

-- Location: IOOBUF_X51_Y54_N16
\Y[2]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \mult4|y[2]~4_combout\,
	devoe => ww_devoe,
	o => \Y[2]~output_o\);

-- Location: IOOBUF_X46_Y54_N9
\Y[3]~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \mult4|y[3]~7_combout\,
	devoe => ww_devoe,
	o => \Y[3]~output_o\);

-- Location: IOOBUF_X58_Y54_N23
\z~output\ : fiftyfivenm_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \outz|ALT_INV_z~combout\,
	devoe => ww_devoe,
	o => \z~output_o\);

-- Location: IOIBUF_X51_Y54_N22
\f[1]~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_f(1),
	o => \f[1]~input_o\);

-- Location: IOIBUF_X51_Y54_N1
\b[0]~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b(0),
	o => \b[0]~input_o\);

-- Location: IOIBUF_X51_Y54_N29
\f[0]~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_f(0),
	o => \f[0]~input_o\);

-- Location: IOIBUF_X54_Y54_N15
\a[0]~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_a(0),
	o => \a[0]~input_o\);

-- Location: LCCOMB_X54_Y53_N24
\mult4|y[0]~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \mult4|y[0]~0_combout\ = (\f[1]~input_o\ & (\b[0]~input_o\ $ (((\a[0]~input_o\))))) # (!\f[1]~input_o\ & ((\b[0]~input_o\ & (!\f[0]~input_o\ & \a[0]~input_o\)) # (!\b[0]~input_o\ & (\f[0]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011011010011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \f[1]~input_o\,
	datab => \b[0]~input_o\,
	datac => \f[0]~input_o\,
	datad => \a[0]~input_o\,
	combout => \mult4|y[0]~0_combout\);

-- Location: IOIBUF_X54_Y54_N29
\b[1]~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b(1),
	o => \b[1]~input_o\);

-- Location: LCCOMB_X54_Y53_N26
\mult4|y[1]~1\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \mult4|y[1]~1_combout\ = (\f[1]~input_o\ & (\b[0]~input_o\ & (\f[0]~input_o\ $ (\a[0]~input_o\)))) # (!\f[1]~input_o\ & (((\f[0]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101100011010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \f[1]~input_o\,
	datab => \b[0]~input_o\,
	datac => \f[0]~input_o\,
	datad => \a[0]~input_o\,
	combout => \mult4|y[1]~1_combout\);

-- Location: IOIBUF_X58_Y54_N29
\a[1]~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_a(1),
	o => \a[1]~input_o\);

-- Location: LCCOMB_X54_Y53_N4
\mult4|y[1]~2\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \mult4|y[1]~2_combout\ = (\f[1]~input_o\ & (\b[1]~input_o\ $ (\mult4|y[1]~1_combout\ $ (\a[1]~input_o\)))) # (!\f[1]~input_o\ & ((\b[1]~input_o\ & (!\mult4|y[1]~1_combout\ & \a[1]~input_o\)) # (!\b[1]~input_o\ & (\mult4|y[1]~1_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011000111000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \f[1]~input_o\,
	datab => \b[1]~input_o\,
	datac => \mult4|y[1]~1_combout\,
	datad => \a[1]~input_o\,
	combout => \mult4|y[1]~2_combout\);

-- Location: LCCOMB_X54_Y53_N6
\adder|Porta1|cout~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \adder|Porta1|cout~0_combout\ = (\b[0]~input_o\ & ((\a[0]~input_o\))) # (!\b[0]~input_o\ & (\f[0]~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111101000001010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \f[0]~input_o\,
	datac => \b[0]~input_o\,
	datad => \a[0]~input_o\,
	combout => \adder|Porta1|cout~0_combout\);

-- Location: LCCOMB_X54_Y53_N16
\adder|Porta2|cout~0\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \adder|Porta2|cout~0_combout\ = (\adder|Porta1|cout~0_combout\ & ((\a[1]~input_o\) # (\b[1]~input_o\ $ (\f[0]~input_o\)))) # (!\adder|Porta1|cout~0_combout\ & (\a[1]~input_o\ & (\b[1]~input_o\ $ (\f[0]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011111000101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \adder|Porta1|cout~0_combout\,
	datab => \b[1]~input_o\,
	datac => \f[0]~input_o\,
	datad => \a[1]~input_o\,
	combout => \adder|Porta2|cout~0_combout\);

-- Location: IOIBUF_X54_Y54_N22
\b[2]~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b(2),
	o => \b[2]~input_o\);

-- Location: LCCOMB_X54_Y53_N18
\mult4|y[2]~3\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \mult4|y[2]~3_combout\ = \b[2]~input_o\ $ (((\f[1]~input_o\ & \adder|Porta2|cout~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111011110001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \f[1]~input_o\,
	datab => \adder|Porta2|cout~0_combout\,
	datad => \b[2]~input_o\,
	combout => \mult4|y[2]~3_combout\);

-- Location: IOIBUF_X56_Y54_N1
\a[2]~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_a(2),
	o => \a[2]~input_o\);

-- Location: LCCOMB_X54_Y53_N12
\mult4|y[2]~4\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \mult4|y[2]~4_combout\ = (\f[1]~input_o\ & (\mult4|y[2]~3_combout\ $ (\f[0]~input_o\ $ (\a[2]~input_o\)))) # (!\f[1]~input_o\ & ((\mult4|y[2]~3_combout\ & (!\f[0]~input_o\ & \a[2]~input_o\)) # (!\mult4|y[2]~3_combout\ & (\f[0]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011000111000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \f[1]~input_o\,
	datab => \mult4|y[2]~3_combout\,
	datac => \f[0]~input_o\,
	datad => \a[2]~input_o\,
	combout => \mult4|y[2]~4_combout\);

-- Location: IOIBUF_X49_Y54_N1
\b[3]~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b(3),
	o => \b[3]~input_o\);

-- Location: LCCOMB_X54_Y53_N22
\mult4|y[3]~5\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \mult4|y[3]~5_combout\ = (\adder|Porta2|cout~0_combout\ & ((\a[2]~input_o\) # (\b[2]~input_o\ $ (\f[0]~input_o\)))) # (!\adder|Porta2|cout~0_combout\ & (\a[2]~input_o\ & (\b[2]~input_o\ $ (\f[0]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1101111001001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \b[2]~input_o\,
	datab => \adder|Porta2|cout~0_combout\,
	datac => \f[0]~input_o\,
	datad => \a[2]~input_o\,
	combout => \mult4|y[3]~5_combout\);

-- Location: LCCOMB_X54_Y53_N0
\mult4|y[3]~6\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \mult4|y[3]~6_combout\ = \b[3]~input_o\ $ (((\f[1]~input_o\ & \mult4|y[3]~5_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110110001101100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \f[1]~input_o\,
	datab => \b[3]~input_o\,
	datac => \mult4|y[3]~5_combout\,
	combout => \mult4|y[3]~6_combout\);

-- Location: IOIBUF_X69_Y54_N1
\a[3]~input\ : fiftyfivenm_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	listen_to_nsleep_signal => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_a(3),
	o => \a[3]~input_o\);

-- Location: LCCOMB_X54_Y53_N10
\mult4|y[3]~7\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \mult4|y[3]~7_combout\ = (\a[3]~input_o\ & (\f[0]~input_o\ $ (\mult4|y[3]~6_combout\ $ (\f[1]~input_o\)))) # (!\a[3]~input_o\ & ((\f[0]~input_o\ & (!\mult4|y[3]~6_combout\)) # (!\f[0]~input_o\ & (\mult4|y[3]~6_combout\ & \f[1]~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011001100010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \f[0]~input_o\,
	datab => \mult4|y[3]~6_combout\,
	datac => \a[3]~input_o\,
	datad => \f[1]~input_o\,
	combout => \mult4|y[3]~7_combout\);

-- Location: LCCOMB_X54_Y53_N20
\outz|z\ : fiftyfivenm_lcell_comb
-- Equation(s):
-- \outz|z~combout\ = (\mult4|y[2]~4_combout\) # ((\mult4|y[0]~0_combout\) # ((\mult4|y[1]~2_combout\) # (\mult4|y[3]~7_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111111110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \mult4|y[2]~4_combout\,
	datab => \mult4|y[0]~0_combout\,
	datac => \mult4|y[1]~2_combout\,
	datad => \mult4|y[3]~7_combout\,
	combout => \outz|z~combout\);

-- Location: UNVM_X0_Y40_N40
\~QUARTUS_CREATED_UNVM~\ : fiftyfivenm_unvm
-- pragma translate_off
GENERIC MAP (
	addr_range1_end_addr => -1,
	addr_range1_offset => -1,
	addr_range2_end_addr => -1,
	addr_range2_offset => -1,
	addr_range3_offset => -1,
	is_compressed_image => "false",
	is_dual_boot => "false",
	is_eram_skip => "false",
	max_ufm_valid_addr => -1,
	max_valid_addr => -1,
	min_ufm_valid_addr => -1,
	min_valid_addr => -1,
	part_name => "quartus_created_unvm",
	reserve_block => "true")
-- pragma translate_on
PORT MAP (
	nosc_ena => \~QUARTUS_CREATED_GND~I_combout\,
	xe_ye => \~QUARTUS_CREATED_GND~I_combout\,
	se => \~QUARTUS_CREATED_GND~I_combout\,
	busy => \~QUARTUS_CREATED_UNVM~~busy\);

-- Location: ADCBLOCK_X43_Y52_N0
\~QUARTUS_CREATED_ADC1~\ : fiftyfivenm_adcblock
-- pragma translate_off
GENERIC MAP (
	analog_input_pin_mask => 0,
	clkdiv => 1,
	device_partname_fivechar_prefix => "none",
	is_this_first_or_second_adc => 1,
	prescalar => 0,
	pwd => 1,
	refsel => 0,
	reserve_block => "true",
	testbits => 66,
	tsclkdiv => 1,
	tsclksel => 0)
-- pragma translate_on
PORT MAP (
	soc => \~QUARTUS_CREATED_GND~I_combout\,
	usr_pwd => VCC,
	tsen => \~QUARTUS_CREATED_GND~I_combout\,
	chsel => \~QUARTUS_CREATED_ADC1~_CHSEL_bus\,
	eoc => \~QUARTUS_CREATED_ADC1~~eoc\);

-- Location: ADCBLOCK_X43_Y51_N0
\~QUARTUS_CREATED_ADC2~\ : fiftyfivenm_adcblock
-- pragma translate_off
GENERIC MAP (
	analog_input_pin_mask => 0,
	clkdiv => 1,
	device_partname_fivechar_prefix => "none",
	is_this_first_or_second_adc => 2,
	prescalar => 0,
	pwd => 1,
	refsel => 0,
	reserve_block => "true",
	testbits => 66,
	tsclkdiv => 1,
	tsclksel => 0)
-- pragma translate_on
PORT MAP (
	soc => \~QUARTUS_CREATED_GND~I_combout\,
	usr_pwd => VCC,
	tsen => \~QUARTUS_CREATED_GND~I_combout\,
	chsel => \~QUARTUS_CREATED_ADC2~_CHSEL_bus\,
	eoc => \~QUARTUS_CREATED_ADC2~~eoc\);

ww_Y(0) <= \Y[0]~output_o\;

ww_Y(1) <= \Y[1]~output_o\;

ww_Y(2) <= \Y[2]~output_o\;

ww_Y(3) <= \Y[3]~output_o\;

ww_z <= \z~output_o\;
END structure;


