-- Copyright (C) 2022  Intel Corporation. All rights reserved.
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

-- *****************************************************************************
-- This file contains a Vhdl test bench with test vectors .The test vectors     
-- are exported from a vector file in the Quartus Waveform Editor and apply to  
-- the top level entity of the current Quartus project .The user can use this   
-- testbench to simulate his design using a third-party simulation tool .       
-- *****************************************************************************
-- Generated on "03/05/2024 15:48:52"
                                                             
-- Vhdl Test Bench(with test vectors) for design  :          rip_c_adder
-- 
-- Simulation tool : 3rd Party
-- 

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;                                

ENTITY rip_c_adder_vhd_vec_tst IS
END rip_c_adder_vhd_vec_tst;
ARCHITECTURE rip_c_adder_arch OF rip_c_adder_vhd_vec_tst IS
-- constants                                                 
-- signals                                                   
SIGNAL a : STD_LOGIC;
SIGNAL b : STD_LOGIC;
SIGNAL c : STD_LOGIC;
SIGNAL d : STD_LOGIC;
SIGNAL e : STD_LOGIC;
SIGNAL f : STD_LOGIC;
SIGNAL g : STD_LOGIC;
SIGNAL h : STD_LOGIC;
SIGNAL ovf : STD_LOGIC;
SIGNAL Y1 : STD_LOGIC;
SIGNAL y2 : STD_LOGIC;
SIGNAL y3 : STD_LOGIC;
SIGNAL y4 : STD_LOGIC;
COMPONENT rip_c_adder
	PORT (
	a : IN STD_LOGIC;
	b : IN STD_LOGIC;
	c : IN STD_LOGIC;
	d : IN STD_LOGIC;
	e : IN STD_LOGIC;
	f : IN STD_LOGIC;
	g : IN STD_LOGIC;
	h : IN STD_LOGIC;
	ovf : OUT STD_LOGIC;
	Y1 : OUT STD_LOGIC;
	y2 : OUT STD_LOGIC;
	y3 : OUT STD_LOGIC;
	y4 : OUT STD_LOGIC
	);
END COMPONENT;
BEGIN
	i1 : rip_c_adder
	PORT MAP (
-- list connections between master ports and signals
	a => a,
	b => b,
	c => c,
	d => d,
	e => e,
	f => f,
	g => g,
	h => h,
	ovf => ovf,
	Y1 => Y1,
	y2 => y2,
	y3 => y3,
	y4 => y4
	);

-- a
t_prcs_a: PROCESS
BEGIN
	a <= '0';
	WAIT FOR 400000 ps;
	a <= '1';
	WAIT FOR 400000 ps;
	a <= '0';
WAIT;
END PROCESS t_prcs_a;

-- b
t_prcs_b: PROCESS
BEGIN
	b <= '0';
	WAIT FOR 350000 ps;
	b <= '1';
	WAIT FOR 350000 ps;
	b <= '0';
WAIT;
END PROCESS t_prcs_b;

-- c
t_prcs_c: PROCESS
BEGIN
	c <= '0';
	WAIT FOR 300000 ps;
	c <= '1';
	WAIT FOR 300000 ps;
	c <= '0';
	WAIT FOR 300000 ps;
	c <= '1';
WAIT;
END PROCESS t_prcs_c;

-- d
t_prcs_d: PROCESS
BEGIN
LOOP
	d <= '0';
	WAIT FOR 250000 ps;
	d <= '1';
	WAIT FOR 250000 ps;
	IF (NOW >= 1000000 ps) THEN WAIT; END IF;
END LOOP;
END PROCESS t_prcs_d;

-- e
t_prcs_e: PROCESS
BEGIN
	FOR i IN 1 TO 2
	LOOP
		e <= '0';
		WAIT FOR 200000 ps;
		e <= '1';
		WAIT FOR 200000 ps;
	END LOOP;
	e <= '0';
WAIT;
END PROCESS t_prcs_e;

-- f
t_prcs_f: PROCESS
BEGIN
	FOR i IN 1 TO 3
	LOOP
		f <= '0';
		WAIT FOR 150000 ps;
		f <= '1';
		WAIT FOR 150000 ps;
	END LOOP;
	f <= '0';
WAIT;
END PROCESS t_prcs_f;

-- g
t_prcs_g: PROCESS
BEGIN
LOOP
	g <= '0';
	WAIT FOR 100000 ps;
	g <= '1';
	WAIT FOR 100000 ps;
	IF (NOW >= 1000000 ps) THEN WAIT; END IF;
END LOOP;
END PROCESS t_prcs_g;

-- h
t_prcs_h: PROCESS
BEGIN
LOOP
	h <= '0';
	WAIT FOR 50000 ps;
	h <= '1';
	WAIT FOR 50000 ps;
	IF (NOW >= 1000000 ps) THEN WAIT; END IF;
END LOOP;
END PROCESS t_prcs_h;
END rip_c_adder_arch;
