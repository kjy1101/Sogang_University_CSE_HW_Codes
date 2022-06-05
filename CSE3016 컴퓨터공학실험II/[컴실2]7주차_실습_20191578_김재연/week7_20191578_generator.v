`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/19 00:20:58
// Design Name: 
// Module Name: week7_20191578_generator
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


module week7_20191578_generator(
    input A,
    input B,
    input C,
    input D,
    output P
    );
    assign P = A^B^C^D;
endmodule
