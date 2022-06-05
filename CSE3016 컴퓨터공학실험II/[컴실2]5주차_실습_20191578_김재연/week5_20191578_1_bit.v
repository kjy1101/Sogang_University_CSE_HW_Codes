`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/08 14:03:52
// Design Name: 
// Module Name: week5_20191578_1_bit
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


module week5_20191578_1_bit(
    input A,
    input B,
    output C,
    output D,
    output E,
    output F
    );
    assign C = ((~A)&(~B)) | (A&B);
    assign D = ~(((~A)&(~B)) | (A&B));
    assign E = A & (~B);
    assign F = (~A) & B;
endmodule
