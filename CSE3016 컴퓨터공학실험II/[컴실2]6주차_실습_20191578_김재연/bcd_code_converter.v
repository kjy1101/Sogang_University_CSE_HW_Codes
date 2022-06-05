`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/12 02:25:15
// Design Name: 
// Module Name: bcd_code_converter
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


module bcd_code_converter(
    input A,
    input B,
    input C,
    input D,
    output F0,
    output F1,
    output F2,
    output F3
    );

    assign F0 = ~((~A)&(~(B&C))&(~(B&D)));
    assign F1 = ~((~A)&(~(B&C))&(~(B&(~D))));
    assign F2 = ~((~A)&(~((~B)&C))&(~(B&(~C)&D)));
    assign F3 = D;
endmodule
