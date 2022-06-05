`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/21 01:11:50
// Design Name: 
// Module Name: week3_20191578_four_input_or_gate_a_tb
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


module week3_20191578_four_input_or_gate_a_tb;

reg a, b, c, d;
wire e;

week3_20191578_four_input_or_gate_a u_OR(
    .A(a), .B(b), .C(c), .D(d), .E(e)
);

initial begin
    a = 1'b0;
    b = 1'b0;
    c = 1'b0;
    d = 1'b0;
end

always a = #400 ~a;
always b = #200 ~b;
always c = #100 ~c;
always d = #50 ~d;

initial begin
    #800
    $finish;
end

endmodule
