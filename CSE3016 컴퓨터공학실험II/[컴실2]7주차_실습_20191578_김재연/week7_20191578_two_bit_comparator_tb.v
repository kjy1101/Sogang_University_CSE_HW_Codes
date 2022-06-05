`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/19 01:07:51
// Design Name: 
// Module Name: week7_20191578_two_bit_comparator_tb
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


module week7_20191578_two_bit_comparator_tb;
reg a, b, c, d;
wire f1, f2, f3;
week7_20191578_two_bit_comparator u1(
    .A(a), .B(b), .C(c), .D(d), .F1(f1), .F2(f2), .F3(f3)
);
initial begin
    a=1'b0;
    b=1'b0;
    c=1'b0;
    d=1'b0;
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
