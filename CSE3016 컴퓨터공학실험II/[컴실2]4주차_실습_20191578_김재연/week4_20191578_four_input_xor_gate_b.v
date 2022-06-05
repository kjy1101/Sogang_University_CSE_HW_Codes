`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/27 17:09:09
// Design Name: 
// Module Name: week4_20191578_four_input_xor_gate_b
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module week4_20191578_four_input_xor_gate_b(
    input A,
    input B,
    input C,
    input D,
    output E,
    output F,
    output G
    );
    assign E = A ^ B;
    assign F = E ^ C;
    assign G = F ^ D;
endmodule
