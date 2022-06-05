`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/08 00:41:25
// Design Name: 
// Module Name: week5_20191578_de_morgan_2_b
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


module week5_20191578_de_morgan_2_b(
    input A,
    input B,
    output C
    );
    assign C = (~A) | (~B);
endmodule
