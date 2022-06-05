`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/27 17:21:45
// Design Name: 
// Module Name: week4_20191578_four_input_aoi_gate
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


module week4_20191578_four_input_aoi_gate(
    input A,
    input B,
    input C,
    input D,
    output E,
    output F,
    output G
    );
    assign E = A&B;
    assign F = C&D;
    assign G = ~(E|F);
endmodule
