`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/27 15:44:25
// Design Name: 
// Module Name: week4_20191578_three_input_nand_gate_b_tb
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


module week4_20191578_three_input_nand_gate_b_tb;
reg a, b, c;
wire d, e;
week4_20191578_three_input_nand_gate_b u1(
    .A(a), .B(b), .C(c), .D(d), .E(e)
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
