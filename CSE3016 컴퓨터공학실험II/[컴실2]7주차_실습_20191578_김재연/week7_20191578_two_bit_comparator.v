`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/19 01:05:03
// Design Name: 
// Module Name: week7_20191578_two_bit_comparator
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


module week7_20191578_two_bit_comparator(
    input A,
    input B,
    input C,
    input D,
    output F1,
    output F2,
    output F3
    );
    assign F1=A&(~C)|B&(~D)&(A|(~C));
    assign F2=(A^~C)&(B^~D);
    assign F3=(~A)&C|(~B)&D&((~A)|C);
endmodule
