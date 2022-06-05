`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/27 16:22:46
// Design Name: 
// Module Name: week4_20191578_three_input_nor_gate_b
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


module week4_20191578_three_input_nor_gate_b(
    input A,
    input B,
    input C,
    output D,
    output E
    );
    assign D = ~(A|B);
    assign E = ~(D|C);
endmodule
