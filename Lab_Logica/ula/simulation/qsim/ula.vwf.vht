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

-- *****************************************************************************
-- This file contains a Vhdl test bench with test vectors .The test vectors     
-- are exported from a vector file in the Quartus Waveform Editor and apply to  
-- the top level entity of the current Quartus project .The user can use this   
-- testbench to simulate his design using a third-party simulation tool .       
-- *****************************************************************************
-- Generated on "03/15/2024 13:25:02"
                                                             
-- Vhdl Test Bench(with test vectors) for design  :          ula
-- 
-- Simulation tool : 3rd Party
-- 

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;                                

ENTITY ula_vhd_vec_tst IS
END ula_vhd_vec_tst;
ARCHITECTURE ula_arch OF ula_vhd_vec_tst IS
-- constants                                                 
-- signals                                                   
SIGNAL a : STD_LOGIC_VECTOR(3 DOWNTO 0);
SIGNAL b : STD_LOGIC_VECTOR(3 DOWNTO 0);
SIGNAL f : STD_LOGIC_VECTOR(1 DOWNTO 0);
SIGNAL Y : STD_LOGIC_VECTOR(3 DOWNTO 0);
SIGNAL z : STD_LOGIC;
COMPONENT ula
	PORT (
	a : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
	b : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
	f : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
	Y : BUFFER STD_LOGIC_VECTOR(3 DOWNTO 0);
	z : BUFFER STD_LOGIC
	);
END COMPONENT;
BEGIN
	i1 : ula
	PORT MAP (
-- list connections between master ports and signals
	a => a,
	b => b,
	f => f,
	Y => Y,
	z => z
	);
-- a[3]
t_prcs_a_3: PROCESS
BEGIN
LOOP
	a(3) <= '0';
	WAIT FOR 500000 ps;
	a(3) <= '1';
	WAIT FOR 500000 ps;
	IF (NOW >= 1000000 ps) THEN WAIT; END IF;
END LOOP;
END PROCESS t_prcs_a_3;
-- a[2]
t_prcs_a_2: PROCESS
BEGIN
	a(2) <= '0';
	WAIT FOR 450000 ps;
	a(2) <= '1';
	WAIT FOR 450000 ps;
	a(2) <= '0';
WAIT;
END PROCESS t_prcs_a_2;
-- a[1]
t_prcs_a_1: PROCESS
BEGIN
	a(1) <= '0';
	WAIT FOR 400000 ps;
	a(1) <= '1';
	WAIT FOR 400000 ps;
	a(1) <= '0';
WAIT;
END PROCESS t_prcs_a_1;
-- a[0]
t_prcs_a_0: PROCESS
BEGIN
	a(0) <= '0';
	WAIT FOR 350000 ps;
	a(0) <= '1';
	WAIT FOR 350000 ps;
	a(0) <= '0';
WAIT;
END PROCESS t_prcs_a_0;
-- b[3]
t_prcs_b_3: PROCESS
BEGIN
	b(3) <= '0';
	WAIT FOR 300000 ps;
	b(3) <= '1';
	WAIT FOR 300000 ps;
	b(3) <= '0';
	WAIT FOR 300000 ps;
	b(3) <= '1';
WAIT;
END PROCESS t_prcs_b_3;
-- b[2]
t_prcs_b_2: PROCESS
BEGIN
LOOP
	b(2) <= '0';
	WAIT FOR 250000 ps;
	b(2) <= '1';
	WAIT FOR 250000 ps;
	IF (NOW >= 1000000 ps) THEN WAIT; END IF;
END LOOP;
END PROCESS t_prcs_b_2;
-- b[1]
t_prcs_b_1: PROCESS
BEGIN
	FOR i IN 1 TO 2
	LOOP
		b(1) <= '0';
		WAIT FOR 200000 ps;
		b(1) <= '1';
		WAIT FOR 200000 ps;
	END LOOP;
	b(1) <= '0';
WAIT;
END PROCESS t_prcs_b_1;
-- b[0]
t_prcs_b_0: PROCESS
BEGIN
	FOR i IN 1 TO 3
	LOOP
		b(0) <= '0';
		WAIT FOR 150000 ps;
		b(0) <= '1';
		WAIT FOR 150000 ps;
	END LOOP;
	b(0) <= '0';
WAIT;
END PROCESS t_prcs_b_0;
-- f[1]
t_prcs_f_1: PROCESS
BEGIN
LOOP
	f(1) <= '0';
	WAIT FOR 100000 ps;
	f(1) <= '1';
	WAIT FOR 100000 ps;
	IF (NOW >= 1000000 ps) THEN WAIT; END IF;
END LOOP;
END PROCESS t_prcs_f_1;
-- f[0]
t_prcs_f_0: PROCESS
BEGIN
LOOP
	f(0) <= '0';
	WAIT FOR 50000 ps;
	f(0) <= '1';
	WAIT FOR 50000 ps;
	IF (NOW >= 1000000 ps) THEN WAIT; END IF;
END LOOP;
END PROCESS t_prcs_f_0;
END ula_arch;
