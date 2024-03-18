onerror {exit -code 1}
vlib work
vcom -work work Multi4_1.vho
vcom -work work Multi4_1.vwf.vht
vsim -c -t 1ps -L fiftyfivenm -L altera -L altera_mf -L 220model -L sgate -L altera_lnsim work.Multi4_1_vhd_vec_tst
vcd file -direction Multi4_1.msim.vcd
vcd add -internal Multi4_1_vhd_vec_tst/*
vcd add -internal Multi4_1_vhd_vec_tst/i1/*
proc simTimestamp {} {
    echo "Simulation time: $::now ps"
    if { [string equal running [runStatus]] } {
        after 2500 simTimestamp
    }
}
after 2500 simTimestamp
run -all
quit -f
