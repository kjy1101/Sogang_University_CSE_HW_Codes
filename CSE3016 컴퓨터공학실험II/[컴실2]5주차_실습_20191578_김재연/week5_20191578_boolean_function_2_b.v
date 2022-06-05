`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/08 01:17:53
// Design Name: 
// Module Name: week5_20191578_boolean_function_2_b
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


module week5_20191578_boolean_function_2_b(
    input A,
    input B,
    input C,
    output D
    );
    assign D = ~((A | B) & C);
endmodule
