`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/08 01:11:13
// Design Name: 
// Module Name: week5_20191578_boolean_function_2_a_tb
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


module week5_20191578_boolean_function_2_a_tb;
reg a, b, c;
wire d;

week5_20191578_boolean_function_2_a u1(
    .A(a), .B(b), .C(c), .D(d)
);

initial begin
    a = 1'b0;
    b = 1'b0;
    c = 1'b0;
end

always a = #200 ~a;
always b = #100 ~b;
always c = #50 ~c;

initial begin
    #400
    $finish;
end

endmodule
