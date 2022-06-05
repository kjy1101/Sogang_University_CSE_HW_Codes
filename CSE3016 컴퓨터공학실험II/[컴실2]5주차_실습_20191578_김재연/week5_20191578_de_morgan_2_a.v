`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/08 00:33:05
// Design Name: 
// Module Name: week5_20191578_de_morgan_2_a
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


module week5_20191578_de_morgan_2_a(
    input A,
    input B,
    output C
    );
    assign C = ~(A & B);
endmodule
