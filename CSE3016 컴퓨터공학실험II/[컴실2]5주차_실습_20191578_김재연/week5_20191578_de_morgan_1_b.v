`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/08 00:23:23
// Design Name: 
// Module Name: week5_20191578_de_morgan_1_b
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


module week5_20191578_de_morgan_1_b(
    input A,
    input B,
    output C
    );
    assign C = (~A) & (~B);
endmodule
