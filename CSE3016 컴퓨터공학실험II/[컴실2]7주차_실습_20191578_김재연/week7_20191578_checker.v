`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/19 00:42:23
// Design Name: 
// Module Name: week7_20191578_checker
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


module week7_20191578_checker(
    input A,
    input B,
    input C,
    input D,
    input P,
    output PEC
    );
    assign PEC = A^B^C^D^P;
//    assign PEC = A^~(B^C^D^P);
endmodule
