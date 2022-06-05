`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/21 00:47:18
// Design Name: 
// Module Name: week3_20191578_three_input_or_gate_a
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


module week3_20191578_three_input_or_gate_a(
    input A,
    input B,
    input C,
    output D
    );
    
    assign D = A | B | C;
    
endmodule
